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
    enum POSTURE 
    {
        FALL,
        STAND,
        SITDOWN,
        LAYDOWN
    };

    void start_Read();
    void stop_Read();
    void restart_Read();
    void start_posEstimation();
    void stop_posEstimation();
    void restart_posEstimation();
    void Read();
    void posEstimation();
    std::thread thread;
    std::string previous_pose;
    std::string poseChange;
    POSTURE POS;
    
    float accelX_g = 0, accelY_g = 0, accelZ_g = 0;
    float gyroX_degPerSec = 0, gyroY_degPerSec = 0, gyroZ_degPerSec = 0;
    float pressure1 = 0;

    float pressure_threshold = 0.5;
    float acc_threshold = 0.1;
    float gyro_threshold = 0.1;
};

#endif
