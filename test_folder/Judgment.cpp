#include <condition_variable>
#include <mutex>
#include "Judgment.h"
#include "MPU6050_test.h"
#include "ADS1115.h"
#include "IPC.h"

// Thread Mark
std::condition_variable cv_j_ready;
std::mutex mtx_j_ready;
bool j_ready = false;

// Message Mark
std::condition_variable cv_MPU6050_C25A;
std::condition_variable cv_J_ready;
std::mutex mtx_MPU6050_C25A;

Judgment::Judgment(){};

void Judgment::start_RS() 
{
    thread_RS = std::thread(&Judgment::Receive_Send, this);
}

void Judgment::stop_RS() 
{
    thread_RS.join();
}

void Judgment::restart_RS() 
{
    stop_RS();
    start_RS();
}

void Judgment::Receive_Send() 
{
    IPC ipc_A("/tmp", 'A');
    IPC ipc_B("/tmp", 'B');
    IPC ipc_C("/tmp", 'C');

    while (true) 
    {
        // Wait A and B
        {
            std::unique_lock<std::mutex> lock(mtx_MPU6050_C25A);
            cv_MPU6050_C25A.wait(lock);
        }
        
        // Receive A
        Message message_A(6);
        if (!ipc_A.receive(message_A)) 
        {
            std::cerr << "Failed to receive message from A." << std::endl;
            continue;
        }
        accelX_g = message_A.DataResult[0]; 
        accelY_g = message_A.DataResult[1];
        accelZ_g = message_A.DataResult[2];
        gyroX_degPerSec = message_A.DataResult[3];
        gyroY_degPerSec = message_A.DataResult[4];
        gyroZ_degPerSec = message_A.DataResult[5];
        // Receive B
        Message message_B(2);
        if (!ipc_B.receive(message_B)) 
        {
            std::cerr << "Failed to receive message from B." << std::endl;
            continue;
        }
        pressure1 = message_B.DataResult[1]; 

        float posChange = posEstimation();
        std::cout << posChange << std::endl;

        // Perpare Message
        std::vector<float> DataResult = {posChange};
        Message message_C = createMessage(DataResult);

        // Send C
        if (!ipc_C.send(message_C)) 
        {
            std::cerr << "Failed to send message C." << std::endl;
            continue;
        }

        // Finish Mark
        {
            std::lock_guard<std::mutex> lock(mtx_j_ready);
            j_ready = true;
            cv_j_ready.notify_one();
        }
    }    
}

// Wait Thread
void Judgment::wait_RS_ready() 
{
    std::unique_lock<std::mutex> lock(mtx_j_ready);
    cv_j_ready.wait(lock, []{ return j_ready; });
    j_ready = false;
}

void Judgment::start_posEstimation() 
{
    thread_posEstimation = std::thread(&Judgment::posEstimation, this);
}

void Judgment::stop_posEstimation() 
{
    thread_posEstimation.join();
}

void Judgment::restart_posEstimation() 
{
    stop_posEstimation();
    start_posEstimation();
}

float Judgment::posEstimation()
{   
    POS_CHANGE previousPose = STAND; 
    POS_CHANGE currentPose = STAND;
    float posChange = 1.0;

    while(true)
    {
        previousPose = currentPose;
        
        if (pressure1 > pressure_threshold)
        {
            if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
            {
                currentPose = FALL;
            }
        }
        
        if (pressure1 > pressure_threshold)
        {
            if((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold) || (gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold) || (gyroX_degPerSec> 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold))
            {
                currentPose = FALL;
            }
        }
        
        if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
        {
            if((gyroX_degPerSec > gyro_threshold && gyroY_degPerSec > gyro_threshold) || (gyroY_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold) || (gyroX_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold))
            {
                currentPose = FALL;
            }
        }
        
        if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 > pressure_threshold)
        {
            currentPose = STAND;
        }

        if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 < 0.5 * pressure_threshold)
        {
            currentPose = SIT;
        }

        if((pressure1 < 0.2 * pressure_threshold) && ((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)) && (accelX_g < acc_threshold && accelY_g < acc_threshold && accelZ_g < acc_threshold))
        {
            currentPose = LAY;
        }

        if (previousPose != currentPose) 
        {
            if (previousPose == SIT && currentPose == STAND) 
            {
                posChange = static_cast<float>(4); // RISE
            }
            if (previousPose == STAND && currentPose == SIT) 
            {
                posChange = static_cast<float>(6); // STAND2SIT
            }
            if (previousPose == SIT && currentPose == LAY) 
            {
                posChange = static_cast<float>(7); // SIT2LAY
            }
            if (previousPose == STAND && currentPose == LAY) 
            {
                posChange = static_cast<float>(7); // SIT2LAY
            }
            if (previousPose == FALL && currentPose == STAND) 
            {
                posChange = static_cast<float>(4); // RISE
            }
            if (previousPose == FALL && currentPose == SIT) 
            {
                posChange = static_cast<float>(0); // FALL
            }
            if (previousPose == FALL && currentPose == LAY) 
            {
                posChange = static_cast<float>(0); // FALL
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return posChange;
}