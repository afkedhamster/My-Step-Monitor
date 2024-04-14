#include <iostream>
#include <thread>
#include <chrono>
#include <pigpio.h>
#include <cstring>
#include "MPU6050_test.h"
#include "IPC.h"

int main() 
{
    MPU6050 MPU;
    MPU.MPU6050_Init();
    
    // Mark 1234
    IPC mark("/tmp", 1234);
    
    while (true) 
    {
        MPU.Data_Process();

        // Prepare Message
        std::vector<float> data = {MPU.accelX_g, MPU.accelY_g, MPU.accelZ_g, MPU.gyroX_degPerSec, MPU.gyroY_degPerSec, MPU.gyroZ_degPerSec};
        Message message = createFloatMessage('1234', data); // Type 1234

        // Send
        if (!mark.send(message)) 
        {
            std::cerr << "Failed to send message to message queue." << std::endl;
            return -1;
        }
        
        // Display
        std::cout << "Message sent to message queue." << std::endl;
        std::cout << "Acceleration (g): X = " << MPU.accelX_g << ", Y = " << MPU.accelY_g << ", Z = " << MPU.accelZ_g << std::endl;
        std::cout << "Angular Rate (deg/s): X = " << MPU.gyroX_degPerSec << ", Y = " << MPU.gyroY_degPerSec << ", Z = " << MPU.gyroZ_degPerSec << std::endl;

        // Delay
        gpioDelay(100000);
    }

    return 0;
}
