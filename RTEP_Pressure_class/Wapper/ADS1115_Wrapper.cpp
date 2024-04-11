#include "ADS1115_Wrapper.h"
#include <iostream>


// ADS1115_Wrapper_h
ADS1115_Wrapper::ADS1115_Wrapper() : i2c_handle(-1) {} // Constructor
ADS1115_Wrapper::~ADS1115_Wrapper() // Deconstructor
{
    stop();
}

// ADS On/Off
bool ADS1115_Wrapper::init(int i2c_bus) 
{
    // Initialize Pigpio
    if (gpioInitialise() < 0) 
    {
        std::cerr << "Failed to initialize pigpio." << std::endl;
        return false;
    }
    // Initialize I2C
    i2c_handle = i2cOpen(i2c_bus, ADS1115_ADDRESS, 0);
    if (i2c_handle < 0) {
        std::cerr << "Failed to initialize I2C communication." << std::endl;
        gpioTerminate();
        return false;
    }
    return true;
}

void ADS1115_Wrapper::stop() 
{
    gpioTerminate();
    i2cClose(i2c_handle);
}

// ADS Read/Write
int ADS1115_Wrapper::readReg(unsigned char reg) 
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

int ADS1115_Wrapper::writeReg(unsigned char reg, unsigned int value) 
{
    char buf[3] = {reg, value >> 8, value & 0xFF};
    return i2cWriteDevice(i2c_handle, buf, 3);
}

// Parameters
int ADS1115_Wrapper::measure(uint16_t mux, uint16_t pga, uint16_t dr, std::chrono::milliseconds wait_time) 
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
