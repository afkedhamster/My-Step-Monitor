#include "Judgment.h"
#include "MPU6050_test.h"
#include "C25A_ADS1115_Pressure_test.cpp"

void Judgment::start_RS() 
{
    thread = std::thread(&Judgment::RS, this);
}

void Judgment::stop_RS() 
{
    thread.join();
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

    while (true) 
    {
        Message message_A;
        message_A.type = 'A';
        if (!ipc_A.receive(message_A)) {
            std::cerr << "Failed to receive message from A." << std::endl;
            continue;
        }
        
        if (message_A.type == 'A') 
        {
            accelX_g = message_A.values[0];
            accelY_g = message_A.values[1];
            accelZ_g = message_A.values[2];
            gyroX_degPerSec = message_A.values[3];
            gyroY_degPerSec = message_A.values[4];
            gyroZ_degPerSec = message_A.values[5];
        }

        Message message_B;
        message_B.type = 'B';
        if (!ipc_B.receive(message_B)) 
        {
            std::cerr << "Failed to receive message from B." << std::endl;
            continue;
        }
        
        if (message_B.type == 'B') 
        {
            pressure1 = message_B.values[1]; // ret_v0
        }

        posEstimation();

        IPC ipc_C("/tmp", 'C');
        std::vector<float> message_C = {static_cast<float>(POS)};
        Message msg_C = createMessage('C', message_C);
        if (!ipc_C.send(msg_C)) 
        {
            std::cerr << "Failed to send message C." << std::endl;
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

void Judgment::posEstimation()
{   
    while(1)
    {
        previous_pose = POS;
        
        if (pressure1 > pressure_threshold)
        {
            if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
            {
                POS = FALL;
            }
        }
        
        if (pressure1 > pressure_threshold)
        {
            if((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold) || (gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold) || (gyroX_degPerSec> 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold))
            {
                POS = FALL;
            }
        }
        
        if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
        {
            if((gyroX_degPerSec > gyro_threshold && gyroY_degPerSec > gyro_threshold) || (gyroY_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold) || (gyroX_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold))
            {
                POS = FALL;
            }
        }
        
        if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 > pressure_threshold)
        {
            POS = STAND;
        }

        if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 < 0.5 * pressure_threshold)
        {
            POS = SITDOWN;
        }

        if((pressure1 < 0.2 * pressure_threshold) && ((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)) && (accelX_g < acc_threshold && accelY_g < acc_threshold && accelZ_g < acc_threshold))
        {
            POS = LAYDOWN;
        }

        std::string posChange = "NO_CHANGE";
        if (previous_pose != POS) {
            if (previous_pose == SITDOWN && POS == STAND) {
                posChange = "SIT2STAND";
            }
            if (previous_pose == STAND && POS == SITDOWN) {
                posChange = "STAND2SIT";
            }
            if (previous_pose == SITDOWN && POS == LAYDOWN) {
                posChange = "SIT2LAY";
            }
            if (previous_pose == STAND && POS == LAYDOWN) {
                posChange = "STAND2LAY";
            }
            if (previous_pose == FALL && POS == STAND) {
                posChange = "RISE";
            }
            if (previous_pose == FALL && POS == SITDOWN) {
                posChange = "FALL";
            }
            if (previous_pose == FALL && POS == LAYDOWN) {
                posChange = "FALL";
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}