#include <iostream>
#include <thread>
#include <chrono>
#include <pigpio.h>
#include <cstring>
#include "MPU6050_test.h"
#include "IPC.h"

// Define Message
struct Message 
{
    int16_t accelX_g;
    int16_t accelY_g;
    int16_t accelZ_g;
    int16_t gyroX_degPerSec;
    int16_t gyroY_degPerSec;
    int16_t gyroZ_degPerSec;
};


int main() 
{
    MPU6050 MPU;
    MPU.MPU6050_Init();

    // Access Queue
    int msgid = getOrCreateMessageQueue("/tmp", 'A'); // Mark A
    if (msgid == -1) 
    {
        std::cerr << "Failed to create or access message queue." << std::endl;
        return -1;
    }

    while (true) 
    {
        MPU.Data_Process();

        // Perpare Message
        Message message;
        message.accelX_g = accelX_g;
        message.accelY_g = accelY_g;
        message.accelZ_g = accelZ_g;
        message.gyroX_degPerSec = gyroX_degPerSec;
        message.gyroY_degPerSec = gyroY_degPerSec;
        message.gyroZ_degPerSec = gyroZ_degPerSec;

        // Send
        if (msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0) == -1) 
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
