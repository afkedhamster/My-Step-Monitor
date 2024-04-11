#include <iostream>
#include <thread>
#include <chrono>
#include "MPU6050.h"
#include "MPU6050_Wrapper.h"

int main() 
{
    MPU6050_Wrapper MPU;

    while (true) 
    {
            double accelX_g, accelY_g, accelZ_g;
            double gyroX_degPerSec, gyroY_degPerSec, gyroZ_degPerSec;

            MPU.Process(accelX_g, accelY_g, accelZ_g, gyroX_degPerSec, gyroY_degPerSec, gyroZ_degPerSec);

            // Display
            std::cout << "Acceleration (g): X=" << data.accelX_g << ", Y=" << data.accelY_g << ", Z=" << data.accelZ_g << std::endl;
            std::cout << "Angular Rate (deg/s): X=" << data.gyroX_degPerSec << ", Y=" << data.gyroY_degPerSec << ", Z=" << data.gyroZ_degPerSec << std::endl;

            // Delay for a short period
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
