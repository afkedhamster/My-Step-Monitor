#include <iostream>
#include <thread>
#include <chrono>
#include <pigpio.h>
#include <cstring>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include "MPU6050_test.h"
#include "ADS1115.h"
#include "IPC.h"
#include "Judgment.h"
#include "Response.h"

// Thread Mark
std::mutex mtx_t1;
std::condition_variable cv_t1;
bool t1_ready = false;

std::mutex mtx_t2;
std::condition_variable cv_t2;
bool t2_ready = false;

// Message Mark
std::condition_variable cv_MPU6050;
std::condition_variable cv_C25A;
std::mutex mtx_MPU6050;
std::mutex mtx_C25A;

int main_MPU6050()
{
    MPU6050 MPU;
    
    // Mark A
    IPC mark("/tmp", 'A'); 
    
    std::cout << "Main MPU6050 thread started." << std::endl;
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
        
        // Finish Send
        {
            std::unique_lock<std::mutex> lock(mtx_MPU6050);
            cv_MPU6050.notify_one();
        }

        // Display
        std::cout << "Message sent to message queue." << std::endl;
        std::cout << "Acceleration (g): X = " << MPU.accelX_g << ", Y = " << MPU.accelY_g << ", Z = " << MPU.accelZ_g << std::endl;
        std::cout << "Angular Rate (deg/s): X = " << MPU.gyroX_degPerSec << ", Y = " << MPU.gyroY_degPerSec << ", Z = " << MPU.gyroZ_degPerSec << std::endl;

        // Delay
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
        // Finish Thread
        {
            std::lock_guard<std::mutex> lock(mtx_t1);
            t1_ready = true;
            cv_t1.notify_all();
        }
    }

    MPU.MPU6050_Stop();

    return 0;
}

int main_C25A()
{
    ADS1115 ADS;

    // Mark B
    IPC ipc("/tmp", 'B'); 
    
    std::cout << "Main C25A thread started." << std::endl;
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

        // Finish Send
        {
            std::unique_lock<std::mutex> lock(mtx_C25A);
            cv_C25A.notify_one();
        }

        // Display
        std::cout << "ret0 = " << ret0 << std::endl;
        std::cout << "ret_v0 = " << ret_v0 << std::endl;
        /* std::cout << "ret1 = " << ret1 << std::endl;
        std::cout << "ret_v1 = " << ret_v1 << std::endl; */
        
        // Delay
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
        // Finish Thread
        {
            std::lock_guard<std::mutex> lock(mtx_t2);
            t2_ready = true;
            cv_t2.notify_all();
        }    
    }

    ADS.ADS_stop();

    return 0;
}

int main()
{
    if (gpioInitialise() < 0) 
    {
        std::cerr << "Failed to initialize pigpio." << std::endl;
        return -1;
    }

    std::thread t1(main_MPU6050);
    std::thread t2(main_C25A);

    Judgment J;
    Response R;
    Buzzer buzzer;
    LCD lcd('l',0,true);

    // Start
    J.start_RS();
    R.start(&buzzer, &lcd, nullptr);

    while (true) 
    {
        // Wait t1 and t2
        {
            std::unique_lock<std::mutex> lock1(mtx_t1);
            cv_t1.wait(lock1, []{ return t1_ready; });
            t1_ready = false;
        }
        {
            std::unique_lock<std::mutex> lock2(mtx_t2);
            cv_t2.wait(lock2, []{ return t2_ready; });
            t2_ready = false;
        }

        // Wait Send
        {
            std::unique_lock<std::mutex> lock_MPU6050(mtx_MPU6050);
            std::unique_lock<std::mutex> lock_C25A(mtx_C25A);
            cv_MPU6050.wait(lock_MPU6050);
            cv_C25A.wait(lock_C25A);
        }

        // Judge and Send
        J.Receive_Send();
        // Finish
        J.wait_RS_ready();
        
        //Read and Response
        R.Read();
        // Finish
        R.wait_R_ready();
    }

    t1.join();
    t2.join();

    gpioTerminate();

    return 0;
}
