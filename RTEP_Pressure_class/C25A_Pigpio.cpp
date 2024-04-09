#include <iostream>
#include <pigpio.h>
#include <chrono>
#include <thread>

// Define Address and Registers
#define ADS_ADDR 0x48 
#define ADS_REG_POINTER_CONVERT 0x00
#define ADS_REG_POINTER_CONFIG  0x01
// Parameters
#define ADS_REG_CONFIG_DEFAULT \
    (ADS_REG_CONFIG_CQUE_NONE | \
     ADS_REG_CONFIG_CLAT_NONLAT | \
     ADS_REG_CONFIG_CPOL_ACTVLOW | \
     ADS_REG_CONFIG_CMODE_TRAD | \
     ADS_REG_CONFIG_DR_128SPS | \
     ADS_REG_CONFIG_MODE_SINGLE)
#define ADS_REG_CONFIG_PGA_RANGE ADS1015_REG_CONFIG_PGA_4_096V


// Variables 
    int i2c_handle;
// Pins
    const int SDA_PIN = 2; 
    const int SCL_PIN = 3;

// ADS On/Off
int ADS_init() 
{
    // Initialize Pigpio
    if (gpioInitialise() < 0)
    {
        std::cerr << "Failed to initialize pigpio." << std::endl;
        return 1;
    }
    // Input
    gpioSetMode(SDA_PIN, PI_INPUT);
    gpioSetMode(SCL_PIN, PI_INPUT);
    // Initialize I2C
    i2c_handle = i2cOpen(1, ADS_ADDR, 0);
    if (i2c_handle < 0) 
    {
        std::cerr << "Failed to initialize I2C communication." << std::endl;
        gpioTerminate();
        return -1;
    }
    return 0;
}

void ADS_stop() 
{
    gpioTerminate();
    i2cClose(i2c_handle);
}

// ADS Read/Write
int ADS_readReg(unsigned char reg) 
{
    char buf[1] = {reg};
    char data[2];
    if (i2cWriteDevice(i2c_handle, buf, 1) != 1) 
    {
        return -1;
    }
    if (i2cReadDevice(i2c_handle, data, 2) != 2) 
    {
        return -1;
    }
    return (data[0] << 8) | data[1];
}

int ADS_writeReg(unsigned char reg, unsigned int value) 
{
    char buf[3] = {reg, value >> 8, value & 0xFF};
    return i2cWriteDevice(i2c_handle, buf, 3);
}

// Parameters
int ADS_measure() 
{
    // Set
    uint16_t mux = 0b0101000000000000; // "1+GND":5
    uint16_t pga = 0b0000100000000000; // "8":0.25mV
    uint16_t dr = 0b0000000010000000; // "128SPS"

    uint16_t config = (mux | pga | dr);
    // Write
    if (ADS_writeReg(0x01, config) == -1) 
    {
        return -1; // Error
    }
    // Return
    return ADS_readReg(0x00);
}

int main() 
{
    if (ADS_init() != 0) 
    {
       std::cerr << "Initialization failed" << std::endl;
        return -1;
    }

    while (true) 
    {
        // Read
        int ret0 = ADS_measure();
        int ret1 = ADS_measure();
        ret0 = ret0 > 32768 ? 0 : ret0;
        double ret_v0 = ret0 / 32768.0 * 6.144;
        ret1 = ret1 > 32768 ? 0 : ret1;
        double ret_v1 = ret1 / 32768.0 * 6.144;
        // Display
        std::cout << "ret0 = " << ret0 << std::endl;
        std::cout << "ret_v0 = " << ret_v0 << std::endl;
        std::cout << "ret1 = " << ret1 << std::endl;
        std::cout << "ret_v1 = " << ret_v1 << std::endl;
        // Delay
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ADS_stop();

    return 0;
}
