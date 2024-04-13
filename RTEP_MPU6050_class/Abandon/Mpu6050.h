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

class Mpu6050 
{
public:
    double accelX_g, accelY_g, accelZ_g;
    double gyroX_degPerSec, gyroY_degPerSec, gyroZ_degPerSec;
public:
    Mpu6050(); // Constructor
    ~Mpu6050(); // Destructor

    int Mpu6050_Init(); // On
    int Mpu6050_Stop(); // Off
    void readMPU6050(uint8_t reg, uint8_t *data, int len); // Read
    void Data_Process(); // Store
    double convertAccel(int16_t raw); // Convert
    double convertGyro(int16_t raw); 

private:
    int fd;
};

#endif
