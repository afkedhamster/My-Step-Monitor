#include "Judgment.h"
#include "MPU6050_test.h"
#include "C25A_ADS1115_Pressure_test.cpp"

void Judgment::start_RS() 
{
    thread_RS = std::thread(&Judgment::RS, this);
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
        Message message_A;
        if (!ipc_A.receive(message_A)) 
        {
            std::cerr << "Failed to receive message from A." << std::endl;
            continue;
        }
        if (message_A.type == 'A') 
        {
            accelX_g = message_A.DataResult[0]; 
            accelY_g = message_A.DataResult[1];
            accelZ_g = message_A.DataResult[2];
            gyroX_degPerSec = message_A.DataResult[3];
            gyroY_degPerSec = message_A.DataResult[4];
            gyroZ_degPerSec = message_A.DataResult[5];
        }

        Message message_B;
        if (!ipc_B.receive(message_B)) 
        {
            std::cerr << "Failed to receive message from B." << std::endl;
            continue;
        }
        if (message_B.type == 'B') 
        {
            pressure1 = message_B.DataResult[1]; 
        }

        float posChange = posEstimation();
        std::cout << posChange << std::endl;

        Message message = createMessage(posChange);

        // Send C
        Message msg_C('C', posChange);
        if (!ipc_C.send(msg_C)) 
        {
            std::cerr << "Failed to send message C." << std::endl;
            continue;
        }
    }    
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

int Judgment::posEstimation()
{   
    POS_CHANGE previousPose = 1;
    POS_CHANGE currentPose = 1;
    float posChange = 1.0;

    while(true)
    {
        previousPose = currentPose;
        
        if (pressure1 > pressure_threshold)
        {
            if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
            {
                currentPose = 0; // FALL
            }
        }
        
        if (pressure1 > pressure_threshold)
        {
            if((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold) || (gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold) || (gyroX_degPerSec> 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold))
            {
                currentPose = 0; // FALL
            }
        }
        
        if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
        {
            if((gyroX_degPerSec > gyro_threshold && gyroY_degPerSec > gyro_threshold) || (gyroY_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold) || (gyroX_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold))
            {
                currentPose = 0; // FALL
            }
        }
        
        if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 > pressure_threshold)
        {
            currentPose = 1; // STAND
        }

        if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 < 0.5 * pressure_threshold)
        {
            currentPose = 2; // SIT
        }

        if((pressure1 < 0.2 * pressure_threshold) && ((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)) && (accelX_g < acc_threshold && accelY_g < acc_threshold && accelZ_g < acc_threshold))
        {
            currentPose = 3; // LAY
        }

        if (previousPose != currentPose) 
        {
            if (previousPose == 2 && currentPose == 1) 
            {
                posChange = 4; // RISE
            }
            if (previousPose == 1 && currentPose == 2) 
            {
                posChange = 6; // STAND2SIT
            }
            if (previousPose == 2 && currentPose == 3) 
            {
                posChange = 5; // SIT2LAY
            }
            if (previousPose == 1 && currentPose == 3) 
            {
                posChange = 5; // SIT2LAY
            }
            if (previousPose == 0 && currentPose == 1) 
            
            {
                posChange = 4; // RISE
            }
            if (previousPose == 0 && currentPose == 2) 
            {
                posChange = 0; // FALL
            }
            if (previousPose == 0 && currentPose == 3) 
            {
                posChange = 0; // FALL
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return posChange;
}