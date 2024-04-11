#ifndef MPU6050_H
#define MPU6050_H

#include <cstdint>
#include "MPU6050.h"

class MPU6050_Wrapper 
{
public:
    MPU6050_Wrapper(); // Constructor
    ~MPU6050_Wrapper(); // Destructor

    int init(); // On
    int stop(); // Off
    void readMPU6050(uint8_t reg, uint8_t *data, int len); // Read
    void Process(double& accelX_g,           |
                    double& accelY_g,        |
                    double& accelZ_g,        |
                    double& gyroX_degPerSec, |
                    double& gyroY_degPerSec, |
                    double& gyroZ_degPerSec); // Store
    double convertAccel(int16_t raw); // Convert
    double convertGyro(int16_t raw); 

private:
    int fd;
};

#endif
