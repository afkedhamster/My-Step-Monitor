#include <iostream>
#include <thread>
#include <chrono>
#include <pigpio.h>
#include "Mpu6050.h"

int main() 
{
    Mpu6050 MPU;

    while (true) 
    {
        //MPU.Mpu6050_Init();构造函数直接初始化了
        MPU.Data_Process();

        // Display
        std::cout << "Acceleration (g): X = " << MPU.accelX_g << ", Y = " << MPU.accelY_g << ", Z = " << MPU.accelZ_g << std::endl;
        std::cout << "Angular Rate (deg/s): X = " << MPU.gyroX_degPerSec << ", Y = " << MPU.gyroY_degPerSec << ", Z = " << MPU.gyroZ_degPerSec << std::endl;

        // Delay for a short period
        gpioDelay(100000);
    }

    return 0;
}