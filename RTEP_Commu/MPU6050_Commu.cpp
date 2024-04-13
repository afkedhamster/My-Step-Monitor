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
    //std::cout << "finish mpu init" << std::endl;
    // Mark A
    IPC mark("/tmp", 'A'); 
    /*
     * if (!mark.MsgID("/tmp", 'A')) 
    {
        std::cout <<"enter the first if sentence" <<std::endl;
        std::cerr << "Failed to set message queue identifier." << std::endl;
        return -1;
    }
     * */
    
    while (true) 
    {
        MPU.Data_Process();
        //std::cout << "enter the loop" << std::endl;
        // Perpare Message
        std::vector<float> data = {MPU.accelX_g, MPU.accelY_g, MPU.accelZ_g, MPU.gyroX_degPerSec, MPU.gyroY_degPerSec, MPU.gyroZ_degPerSec};
        //std::cout <<"11111111" << std::endl;
        Message message = createMessage(data);
        //std::cout << "22222222" << std::endl;
        
        // Send
        if (!mark.send(message)) 
        {
            //std::cout << "enter the second if sentence" << std::endl;
            std::cerr << "Failed to send message to message queue." << std::endl;
            return -1;
        }
        //std::cout << "jump out the if sentence" << std::endl;
        
        // Display
        std::cout << "Message sent to message queue." << std::endl;
        std::cout << "Acceleration (g): X = " << MPU.accelX_g << ", Y = " << MPU.accelY_g << ", Z = " << MPU.accelZ_g << std::endl;
        std::cout << "Angular Rate (deg/s): X = " << MPU.gyroX_degPerSec << ", Y = " << MPU.gyroY_degPerSec << ", Z = " << MPU.gyroZ_degPerSec << std::endl;

        // Delay
        gpioDelay(100000);
    }

    return 0;
}
