#ifndef Threads_h
#define Threads_h

#include <iostream>
#include <thread>
#include <chrono>

enum POS_CHANGE{
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

class Threads_Read{
public:
    // start the thread
    void start(){
        thread = std::thread(&Threads_Read::doSomething, this);
    };
    // stop the thread
    void stop(){
        thread.join();};
    // restart the thread
    void restart(){
        thread = std::thread(&Threads_Read::doSomething, this);
    };
    // the function that the thread will run
    void doSomething(){
        // initialize the sensors MPU6050
        MPU6050 mpu6050(1, 0x68);
        if (!mpu6050.initialize())
        {
            std::cout << "MPU6050 initialize failed" << std::endl;
            return NULL;
        }
        // initialize the sensors Pressure
        Pressure pressure1_sensor(1, 0x48);
        if (!pressure1_sensor.initialize())
        {
            std::cout << "Pressure initialize failed" << std::endl;
            return NULL;
        }
        // read the data from the sensors
        while (1)
        {
            mpu6050.readAcceleration(accelX_g, accelY_g, accelZ_g);  // read the acceleration
            mpu6050.readGyroscope(gyroX_degPerSec, gyroY_degPerSec, gyroZ_degPerSec);  // read the angular velocity
            pressure1_sensor.readPressure(pressure1);    // read the pressure
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // sleep for 100ms
        }
    };
    std::thread thread;  // the thread
private:
    float accelX_g = 0, accelY_g = 0, accelZ_g = 0;     // acceleration
    float gyroX_degPerSec = 0, gyroY_degPerSec = 0, gyroZ_degPerSec = 0;  // angular velocity
    float pressure1 = 0, pressure2 = 0;        // pressure
};

class Threads_posEstimation{
public:
    // start the thread
    void start(){
        thread = std::thread(&Threads_posEstimation::doSomething, this);
    };
    // stop the thread
    void stop(){
        thread.join();};
    // restart the thread
    void restart(){
        thread = std::thread(&Threads_posEstimation::doSomething, this);
    };
    
    // Add a string to store the previous pose
    std::string previous_pose;

    // Add a method to update the previous pose
    void updatePose(std::string new_pose) {
        previous_pose = new_pose;
    }

    // the function that the thread will run
    void doSomething()
    {   
         enum POS_CHANGE previous_pos = STAND; // the previous pos
        
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
            }

            // sleep for 100ms
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };
    std::thread thread;  // the thread
public:
    enum POS_CHANGE posChange; 
    float accelX_g = 0, accelY_g = 0, accelZ_g = 0;         // acceleration
    float gyroX_degPerSec = 0, gyroY_degPerSec = 0, gyroZ_degPerSec = 0;      // angular velocity
    float pressure1 = 0;            // pressure
    float pressure_threshold = 0.5;                // the pressure threshold
    float acc_threshold = 0.1;                     // the acceleration threshold
    float gyro_threshold = 0.1;                    // the angular velocity threshold
};
#endif

