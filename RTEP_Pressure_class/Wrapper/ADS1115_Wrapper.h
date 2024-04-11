#ifndef ADS1115_WRAPPER_H
#define ADS1115_WRAPPER_H

#include <pigpio.h>
#include <chrono>
#include <thread>
#include "ADS1115.h"

class ADS1115_Wrapper 
{
public:
    ADS1115_Wrapper(); // Constructor
    ~ADS1115_Wrapper(); // Destructor

    bool init(int i2c_bus); // On
    void stop(); // Off
    int readReg(unsigned char reg); // Read
    int writeReg(unsigned char reg, unsigned int value); // Write
    int measure(uint16_t mux, uint16_t pga, uint16_t dr); // Parameters

private:
    int i2c_handle; // Communication Handle
};

#endif
