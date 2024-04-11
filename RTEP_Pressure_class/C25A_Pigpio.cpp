#include <iostream>
#include <pigpio.h>
#include <chrono>
#include <thread>
#include <ads1115.h>

// Define Address and Registers in ads1115.h
// Communication handle
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
    // Initialize I2C
    i2c_handle = i2cOpen(1, ADS1115_ADDRESS, 0);
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
int ADS_measure(uint16_t mux, uint16_t pga, uint16_t dr) 
{
    // Default
    int config = ADS1115_REG_CONFIG_CQUE_NONE    |
                 ADS1115_REG_CONFIG_CLAT_NONLAT  |
                 ADS1115_REG_CONFIG_CPOL_ACTVLOW |
                 ADS1115_REG_CONFIG_CMODE_TRAD   |
                 ADS1115_REG_CONFIG_MODE_SINGLE  |
                 mux                             |
                 dr                              |
                 pga;
    // Bit
    config |= ADS1115_REG_CONFIG_OS_SINGLE;
    // Send
    ADS_writeReg(ADS1115_REG_POINTER_CONFIG, config);
    // Wait
    std::this_thread::sleep_for(std::chrono::milliseconds(8));
    // Read
    ADS_writeReg(ADS1115_REG_POINTER_CONVERT, 0); // Convert
    char data[2];
    if (i2cReadDevice(i2c_handle, data, 2) != 2) 
    {
        return -1; // Error
    }
    int value = ((data[0] << 8) & 0xFF00) | data[1];
    // Check
    if (value > 0x7FFF) 
    {
        return (value - 0xFFFF);
    } 
    else 
    {
        return value;
    }
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
        // Set (Different Channels)
        int ret0 = ADS_measure(ADS1115_REG_CONFIG_MUX_SINGLE_0, 
                                ADS1115_REG_CONFIG_PGA_4_096V, 
                                ADS1115_REG_CONFIG_DR_128SPS);
        int ret1 = ADS_measure(ADS1115_REG_CONFIG_MUX_SINGLE_1, 
                                ADS1115_REG_CONFIG_PGA_4_096V, 
                                ADS1115_REG_CONFIG_DR_128SPS);
        ret0 = ret0 > 32768 ? 0 : ret0;
        double ret_v0 = ret0 / * (4.096 / 32768); // Change
        ret1 = ret1 > 32768 ? 0 : ret1;
        double ret_v1 = ret1 / * (4.096 / 32768);
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
