#include "Judgment.h"
#include "MPU6050_test.h"
#include "C25A_ADS1115_Pressure_test.cpp"

void Judgment::start_Read() 
{
    thread = std::thread(&Judgment::Read, this);
}

void Judgment::stop_Read() 
{
    thread.join();
}

void Judgment::restart_Read() 
{
    stop_Read();
    start_Read();
}

void Judgment::Read() 
{
    // Mark A for Receive
    IPC ipc_A("/tmp", 'A');
    if (!ipc_A.MsgID("/tmp", 'A')) 
    {
        std::cerr << "Failed to set message queue identifier for A." << std::endl;
        return;
    }
    // Mark B for Receive
    IPC ipc_B("/tmp", 'B');
    if (!ipc_B.MsgID("/tmp", 'B')) 
    {
        std::cerr << "Failed to set message queue identifier for B." << std::endl;
        return;
    }
    // Mark C for Send
    IPC ipc_C("/tmp", 'C');
    if (!ipc_C.MsgID("/tmp", 'C')) 
    {
        std::cerr << "Failed to set message queue identifier for C." << std::endl;
        return;
    }
    // Read A
    while (true) 
    {
        Message message;
        if (!ipc_A.receive(message)) 
        {
            std::cerr << "Failed to receive message from A." << std::endl;
            continue;
        }
        // Send A
        if (!ipc_C.send(message)) 
        {
            std::cerr << "Failed to send message from A to C." << std::endl;
            continue;
        }
    }
    // Read B
    while (true) 
    {
        Message message;
        if (!ipc_B.receive(message)) 
        {
            std::cerr << "Failed to receive message from B." << std::endl;
            continue;
        }
        // Send B
        if (!ipc_C.send(message)) 
        {
            std::cerr << "Failed to send message from B to C." << std::endl;
            continue;
        }
    }
}

void Judgment::start_posEstimation() 
{
    thread = std::thread(&Judgment::posEstimation, this);
}

void Judgment::stop_posEstimation() 
{
    thread.join();
}

void Judgment::restart_posEstimation() 
{
    stop_posEstimation();
    start_posEstimation();
}

void updatePose(std::string new_pose) {
        previous_pose = new_pose;
    }

void Judgment::posEstimation()
{   
        // the loop that will run forever
    while(1)
        {
            // FALL
            if (pressure1 > pressure_threshold)
            {
                if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
                {
                    if(previous_pos == STAND)
                    {
                        posChange = FALL;
                        previous_pos = FALL;
                    }
                }
            }
            if (pressure1 > pressure_threshold)
            {
                if((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold) || (gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold) || (gyroX_degPerSec> 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold))
                {
                    if(previous_pos == STAND)
                    {
                        posChange = FALL;
                        previous_pos = FALL;
                    }
                }
            }
            if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
            {
                if((gyroX_degPerSec > gyro_threshold && gyroY_degPerSec > gyro_threshold) || (gyroY_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold) || (gyroX_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold))
                {
                    if(previous_pos == STAND)
                    {
                        posChange = FALL;
                        previous_pos = FALL;
                    }
                }
            }
            
            // STAND
            if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 > pressure_threshold)
            {
                if(previous_pos == FALL)
                {
                    posChange = RISE;
                    previous_pos = STAND;
                }
            }

            // WALKING
            // if((accelX_g > acc_threshold || accelY_g > acc_threshold || accelZ_g > acc_threshold) && (pressure1 > 0.4 * pressure_threshold))
            // {
            //     usleep(1000000); // sleep for 1s
            //     if((pressure1 > 0.4 * pressure_threshold))
            //     {
            //         POS = WALKING;  
            //     }
            // }

            // SIT
            if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 < 0.5 * pressure_threshold && pressure2 < 0.5 * pressure_threshold)
            {
                if(previous_pos == STAND)
                {
                    posChange = STAND2SIT;
                    previous_pos = SIT;
                }
            }

            // LAY
            if((pressure1 < 0.2 * pressure_threshold) && ((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)) && (accelX_g < acc_threshold && accelY_g < acc_threshold && accelZ_g < acc_threshold))
            {
                if(previous_pos == STAND)  
                {
                    posChange = STAND2LAY;  
                    previous_pos = LAY;
                }
                else if(previous_pos == SIT)
                {
                    posChange = SIT2LAY;
                    previous_pos = LAY;
            }
            };

            // sleep for 100ms
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
};
