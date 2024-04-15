#ifndef JUDGMENT_H
#define JUDGMENT_H

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "IPC.h"

class Judgment 
{
public:
    enum POS_CHANGE
    {
        FALL = 0,
        STAND = 1,
        // WALKING
        SIT = 2,
        LAY = 3,
        RISE = 4,
        SIT2LAY = 5,
        STAND2SIT = 6,
        STAND2LAY = 7,
    };

    Judgment();

    void start_RS();
    void stop_RS();
    void restart_RS();
    void start_posEstimation();
    void stop_posEstimation();
    void restart_posEstimation();
    float posEstimation();
    void Receive_Send();

    void wait_RS_ready() 
    

private:
    std::thread thread_RS; 
    std::thread thread_posEstimation;

    POS_CHANGE previous_pose;
    POS_CHANGE POSE;
    
    float accelX_g, accelY_g, accelZ_g;
    float gyroX_degPerSec, gyroY_degPerSec, gyroZ_degPerSec;
    float pressure1;

    float pressure_threshold;
    float acc_threshold;
    float gyro_threshold;

    IPC ipc_A; 
    IPC ipc_B;
    IPC ipc_C;
};

#endif
