#include <iostream>
#include <pigpio.h>
#include <thread>
#include <chrono>
#include "MPU6050_test.h"


MPU6050::MPU6050()
{
   // Initialize Pigpio
    if (gpioInitialise() < 0)
    {
        std::cerr << "Failed to initialize pigpio." << std::endl;
        throw std::runtime_error("Failed to initialize pigpio.");
    }

    // Initialize I2C
    fd = i2cOpen(1, MPU6050_ADDR, 0);
    if (fd < 0)
    {
        std::cerr << "Failed to initialize I2C communication." << std::endl;
        gpioTerminate();
        throw std::runtime_error("Failed to initialize I2C communication.");
    }
}

MPU6050::~MPU6050()
{
    MPU6050_Stop();
}

// MPU On/Off
int MPU6050::MPU6050 _Init()
{
    // Enable MPU6050
    i2cWriteByteData(fd, 0x68, 0x00);
}

int MPU6050::MPU6050 _Stop()
{
    i2cClose(fd);
    gpioTerminate();
    return 0;
}

// Read
//void MPU6050 ::readMPU6050(uint8_t reg, uint8_t *data, int len){
//    i2cWriteByteData(fd, reg, 0);
//    i2cReadI2CBlockData(fd, reg, reinterpret_cast<char *>(data), len);
//}

// Convert
double MPU6050::convertAccel(int16_t raw)
{
    return raw / 16384.0; // +-2g
}

double MPU6050::convertGyro(int16_t raw)
{
    return raw / 131.0; // +-250
}

// Process
void MPU6050::Data_Process()
{
    // Read
    int16_t accelX = i2cReadByteData(fd, ACCEL_XOUT_H);
    int16_t accelY = i2cReadByteData(fd, ACCEL_YOUT_H);
    int16_t accelZ = i2cReadByteData(fd, ACCEL_ZOUT_H);

    int16_t gyroX = i2cReadByteData(fd, GYRO_XOUT_H);
    int16_t gyroY = i2cReadByteData(fd, GYRO_YOUT_H);
    int16_t gyroZ = i2cReadByteData(fd, GYRO_ZOUT_H);

    // Convert
    accelX_g = convertAccel(accelX);
    accelY_g = convertAccel(accelY);
    accelZ_g = convertAccel(accelZ);
    gyroX_degPerSec = convertGyro(gyroX);
    gyroY_degPerSec = convertGyro(gyroY);
    gyroZ_degPerSec = convertGyro(gyroZ);
}