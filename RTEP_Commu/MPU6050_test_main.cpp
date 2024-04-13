#include <iostream>
#include <thread>
#include <chrono>
#include <pigpio.h>
#include "MPU6050_test.h"

int main() 
{
    MPU6050 MPU;
    MPU.MPU6050_Init();

    while (true) 
    {
        MPU.Data_Process();

        // Display
        std::cout << "Acceleration (g): X = " << MPU.accelX_g << ", Y = " << MPU.accelY_g << ", Z = " << MPU.accelZ_g << std::endl;
        std::cout << "Angular Rate (deg/s): X = " << MPU.gyroX_degPerSec << ", Y = " << MPU.gyroY_degPerSec << ", Z = " << MPU.gyroZ_degPerSec << std::endl;

        // Delay
        gpioDelay(100000);
    }

    return 0;
}