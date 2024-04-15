#include <iostream>
#include <thread>
#include <chrono>
#include <pigpio.h>
#include <cstring>
#include "MPU6050_test.h"
#include "ADS1115.h"
#include "IPC.h"
#include "Judgment.h"
#include "Response.h"


int main_MPU6050()
{
    MPU6050 MPU;
    MPU.MPU6050_Init();
    
    // Mark A
    IPC mark("/tmp", 'A'); 
    
    while (true) 
    {
        MPU.Data_Process();

        // Perpare Message
        std::vector<float> DataResult = {MPU.accelX_g, MPU.accelY_g, MPU.accelZ_g, MPU.gyroX_degPerSec, MPU.gyroY_degPerSec, MPU.gyroZ_degPerSec};
        Message message = createMessage(DataResult);
        
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

int main_C25A()
{
    ADS1115 ADS;
    ADS.ADS_init();

    // Mark B
    IPC ipc("/tmp", 'B'); 

    while (true) 
    {
        // Set (Different Channels)
        float ret0 = ADS.ADS_measure(ADS1115_REG_CONFIG_MUX_SINGLE_0, 
                                ADS1115_REG_CONFIG_PGA_2_048V, 
                                ADS1115_REG_CONFIG_DR_860SPS);
        /* float ret1 = ADS_measure(ADS1115_REG_CONFIG_MUX_SINGLE_1, 
                                ADS1115_REG_CONFIG_PGA_2_048V, 
                                ADS1115_REG_CONFIG_DR_860SPS); */
        ret0 = ret0 > 32768 ? 0 : ret0;
        float ret_v0 = (ret0*2.048)/32768;
        /* ret1 = ret1 > 32768 ? 0 : ret1;
        float ret_v1 = (ret1*2.048)/32768; */

        // Perpare Message
        std::vector<float> DataResult = {ret0, ret_v0};
        Message message = createMessage(DataResult);

        // Send
        if (!ipc.send(message)) 
        {
            std::cerr << "Failed to send message to message queue." << std::endl;
            return -1;
        }

        // Display
        std::cout << "ret0 = " << ret0 << std::endl;
        std::cout << "ret_v0 = " << ret_v0 << std::endl;
        /* std::cout << "ret1 = " << ret1 << std::endl;
        std::cout << "ret_v1 = " << ret_v1 << std::endl; */
        
        // Delay
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    ADS.ADS_stop();

    return 0;
}

int main()
{
    std::thread t1(main_MPU6050);
    std::thread t2(main_C25A);

    Judgment J;
    Response R;
        Buzzer buzzer;
        LCD lcd('l',0,true);

    J.start_RS();
    R.start(&buzzer, &lcd, nullptr);

    std::thread t3([&](){ J.Receive_Send(); });
    std::thread t4([&](){ R.Read(); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;

}