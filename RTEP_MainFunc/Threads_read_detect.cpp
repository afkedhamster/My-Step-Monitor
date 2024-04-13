#ifndef Threads_h
#define Threads_h

#include <iostream>
#include <thread>
#include <chrono>

enum POSTURE{
    FALL,
    STAND,
    WALKING,
    SITDOWN,
    LAYDOWN
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
            
            // if the acceleration is less than the threshold and the pressure is greater than the threshold
            if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 > pressure_threshold)
            {
                POS = STAND; // if the acceleration is less than the threshold and the pressure is greater than the threshold, then the pos is STAND
            }

            // if the acceleration is greater than the threshold and the pressure is greater than the threshold
            if((accelX_g > acc_threshold || accelY_g > acc_threshold || accelZ_g > acc_threshold) && (pressure1 > 0.4 * pressure_threshold))
            {
                usleep(1000000); // sleep for 1s
                if((pressure1 > 0.4 * pressure_threshold))
                {
                    POS = WALKING;  // if the acceleration is greater than the threshold and the pressure is greater than the threshold, then the pos is WALKING
                }
            }

            // if the acceleration is less than the threshold and the pressure is less than the threshold
            if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 < 0.5 * pressure_threshold && pressure2 < 0.5 * pressure_threshold)
            {
                POS = SITDOWN; // if the acceleration is less than the threshold and the pressure is less than the threshold, then the pos is SITDOWN
            }

            // if the acceleration is less than the threshold and the pressure is less than the threshold
            if((pressure1 < 0.2 * pressure_threshold) && ((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)) && (accelX_g < acc_threshold && accelY_g < acc_threshold && accelZ_g < acc_threshold))
            {
                POS = LAYDOWN; // if the acceleration is less than the threshold and the pressure is less than the threshold, then the pos is LAYDOWN
            }

            // Check for pose change
            std::string current_pose = getCurrentPose(); // You need to implement this method
            if (previous_pose == "SITDOWN" && current_pose == "STAND") {
                posChange = "SIT2STAND";
            }
            if (previous_pose == "STAND" && current_pose == "SITDOWN") {
                posChange = "STAND2SIT";
            }
            if (previous_pose == "SITDOWN" && current_pose == "LAYDOWN") {
                posChange = "SIT2LAY";
            }
            if (previous_pose == "LAYDOWN" && current_pose == "SITDOWN") {
                posChange = "LAY2SIT";
            }
            if (previous_pose == "LAYDOWN" && current_pose == "STAND") {
                posChange = "LAY2STAND";
            }
            if (previous_pose == "STAND" && current_pose == "LAYDOWN") {
                posChange = "STAND2LAY";
            }
            if (previous_pose == "FALL" && current_pose == "STAND") {
                posChange = "RISE";
            }
            if (previous_pose == "FALL" && current_pose == "SITDOWN") {
                posChange = "FALL";
            }
            if (previous_pose == "FALL" && current_pose == "LAYDOWN") {
                posChange = "FALL";
            }
            // Update the previous pose at the end of the method
            updatePose(current_pose);

            // sleep for 100ms
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };
    std::thread thread;  // the thread
public:
    enum POSTURE POS;                     // the pos
    float accelX_g = 0, accelY_g = 0, accelZ_g = 0;         // acceleration
    float gyroX_degPerSec = 0, gyroY_degPerSec = 0, gyroZ_degPerSec = 0;      // angular velocity
    float pressure1 = 0;            // pressure
    float pressure_threshold = 0.5;                // the pressure threshold
    float acc_threshold = 0.1;                     // the acceleration threshold
    float gyro_threshold = 0.1;                    // the angular velocity threshold
};
#endif

