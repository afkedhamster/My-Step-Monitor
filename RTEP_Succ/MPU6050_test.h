#ifndef MPU6050_H
#define MPU6050_H

#include <cstdint>

#define MPU6050_ADDR 0x68
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x45
#define GYRO_ZOUT_H 0x47

class MPU6050 
{
public:
    double accelX_g, accelY_g, accelZ_g;
    double gyroX_degPerSec, gyroY_degPerSec, gyroZ_degPerSec;
public:
    MPU6050(); // Constructor
    ~MPU6050(); // Destructor

    int MPU6050_Init(); // On
    int MPU6050_Stop(); // Off
    // void readMPU6050(uint8_t reg, uint8_t *data, int len); // Read
    void Data_Process(); // Process
    double convertAccel(int16_t raw); // Convert
    double convertGyro(int16_t raw); 

private:
    int fd;
};

#endif