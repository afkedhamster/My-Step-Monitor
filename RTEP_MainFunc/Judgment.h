// Judgment.h
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
        FALL,
        STAND,
        // WALKING,
        SIT,
        LAY,
        RISE,
        SIT2LAY,
        STAND2SIT,
        STAND2LAY,
    };

    void start_RS();
    void stop_RS();
    void restart_RS();
    void start_posEstimation();
    void stop_posEstimation();
    void restart_posEstimation();
    void Receive_Send();
    void posEstimation();
    void updatePose(std::string new_pose);
    std::thread thread;
    POS_CHANGE previous_pose;
    POS_CHANGE POS;
    
    float accelX_g = 0, accelY_g = 0, accelZ_g = 0;
    float gyroX_degPerSec = 0, gyroY_degPerSec = 0, gyroZ_degPerSec = 0;
    float pressure1 = 0;

    float pressure_threshold = 0.5;
    float acc_threshold = 0.1;
    float gyro_threshold = 0.1;
};

#endif
