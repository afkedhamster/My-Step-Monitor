#include <iostream>
#include <pigpio.h>
#include <chrono>
#include <thread>

// Define Address and Registers
#define ADS_ADDR 0x48 
#define ADS_REG_POINTER_CONVERT 0x00
#define ADS_REG_POINTER_CONFIG  0x01
// Book
#define ADS1015_REG_CONFIG_CQUE_NONE    (0x0003)
#define ADS1015_REG_CONFIG_CLAT_NONLAT  (0x0000)
#define ADS1015_REG_CONFIG_CPOL_ACTVLOW (0x0000)
#define ADS1015_REG_CONFIG_CMODE_TRAD   (0x0000)
#define ADS1015_REG_CONFIG_DR_860SPS    (0x0080)
#define ADS1015_REG_CONFIG_MODE_SINGLE  (0x0100)
#define ADS1015_REG_CONFIG_PGA_4_096V   (0x0200)
#define ADS1015_REG_CONFIG_MUX_SINGLE_0 (0x4000)
#define ADS1015_REG_CONFIG_MUX_SINGLE_1 (0x5000)
#define ADS1015_REG_CONFIG_MUX_SINGLE_2 (0x6000)
#define ADS1015_REG_CONFIG_MUX_SINGLE_3 (0x7000)
#define ADS1015_REG_CONFIG_OS_SINGLE    (0x8000)

// Variable
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
    // Prepare
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
int ADS_measure(int chan) 
{
    // Default
    int config = ADS1015_REG_CONFIG_CQUE_NONE    |
                 ADS1015_REG_CONFIG_CLAT_NONLAT  |
                 ADS1015_REG_CONFIG_CPOL_ACTVLOW |
                 ADS1015_REG_CONFIG_CMODE_TRAD   |
                 ADS1015_REG_CONFIG_DR_860SPS   |
                 ADS1015_REG_CONFIG_MODE_SINGLE |
                 ADS1015_REG_CONFIG_PGA_4_096V;
    // Input Channel
    switch (chan) 
    {
        case (0):
            config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
            break;
        case (1):
            config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
            break;
        case (2):
            config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
            break;
        case (3):
            config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
            break;
    }
    // Bit
    config |= ADS1015_REG_CONFIG_OS_SINGLE;
    // Send Config
    config = ((config >> 8) & 0x00FF) | ((config << 8) & 0xFF00);
    ADS_writeReg(ADS1015_REG_POINTER_CONFIG, config);
    // Wait
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    // Read
    ADS_writeReg(ADS_REG_POINTER_CONVERT, 0); // Start conversion
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
    } else {
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
        // Read
        int ret0 = ADS_measure(0);
        int ret1 = ADS_measure(1);
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
