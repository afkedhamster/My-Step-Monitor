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

void updatePose(std::string new_pose) 
{
    previous_pose = new_pose;
}

void Judgment::posEstimation()
{   
        // the loop that will run forever
    while(1)
    {
        // the conditions that will trigger the pos
        // if the acceleration is greater than the threshold and the pressure is greater than the threshold
        if (pressure1 > pressure_threshold)
        {
            if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
            {
                POS = FALL;  // if the acceleration is greater than the threshold and the pressure is greater than the threshold, then the pos is FALL
            }
        }
        if (pressure1 > pressure_threshold)
        {
            if ((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold) || (gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold) || (gyroX_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold))
            {
                POS = FALL;
            }
        }
        if ((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
        {
            if ((gyroX_degPerSec > gyro_threshold && gyroY_degPerSec > gyro_threshold) || (gyroY_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold) || (gyroX_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold))
            {
                POS = FALL;
            }
        }

        // if the acceleration is less than the threshold and the pressure is greater than the threshold
        if (accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 > pressure_threshold)
        {
            POS = STAND; // if the acceleration is less than the threshold and the pressure is greater than the threshold, then the pos is STAND
        }

        // if the acceleration is greater than the threshold and the pressure is greater than the threshold
        if ((accelX_g > acc_threshold || accelY_g > acc_threshold || accelZ_g > acc_threshold) && (pressure1 > 0.4 * pressure_threshold))
        {
            usleep(1000000); // sleep for 1s
            if ((pressure1 > 0.4 * pressure_threshold))
            {
                POS = WALKING; // if the acceleration is greater than the threshold and the pressure is greater than the threshold, then the pos is WALKING
            }
        }

        // if the acceleration is less than the threshold and the pressure is less than the threshold
        if (accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 < 0.5 * pressure_threshold && pressure2 < 0.5 * pressure_threshold)
        {
            POS = SITDOWN; // if the acceleration is less than the threshold and the pressure is less than the threshold, then the pos is SITDOWN
        }

        // if the acceleration is less than the threshold and the pressure is less than the threshold
        if ((pressure1 < 0.2 * pressure_threshold) && ((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold) || (gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold) || (gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)) && (accelX_g < acc_threshold && accelY_g < acc_threshold && accelZ_g < acc_threshold))
        {
            POS = LAYDOWN; // if the acceleration is less than the threshold and the pressure is less than the threshold, then the pos is LAYDOWN
        }

        // Check for pose change
        std::string current_pose = getCurrentPose(); // You need to implement this method
        if (previous_pose == "SITDOWN" && current_pose == "STAND")
        {
            posChange = "SIT2STAND";
        }
        if (previous_pose == "STAND" && current_pose == "SITDOWN")
        {
            posChange = "STAND2SIT";
        }
        if (previous_pose == "SITDOWN" && current_pose == "LAYDOWN")
        {
            posChange = "SIT2LAY";
        }
        if (previous_pose == "LAYDOWN" && current_pose == "SITDOWN")
        {
            posChange = "LAY2SIT";
        }
        if (previous_pose == "LAYDOWN" && current_pose == "STAND")
        {
            posChange = "LAY2STAND";
        }
        if (previous_pose == "STAND" && current_pose == "LAYDOWN")
        {
            posChange = "STAND2LAY";
        }
        if (previous_pose == "FALL" && current_pose == "STAND")
        {
            posChange = "RISE";
        }
        if (previous_pose == "FALL" && current_pose == "SITDOWN")
        {
            posChange = "FALL";
        }
        if (previous_pose == "FALL" && current_pose == "LAYDOWN")
        {
            posChange = "FALL";
        }
        // Update the previous pose at the end of the method
        updatePose(current_pose);

        // sleep for 100ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
};

void Judgment::updatePose(std::string new_pose) 
{
    previous_pose = new_pose;
}
