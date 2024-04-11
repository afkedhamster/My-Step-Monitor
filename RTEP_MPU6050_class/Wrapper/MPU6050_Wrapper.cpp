#include <pigpio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "MPU6050.h"
#include "MPU6050_Wrapper.h"

// MPU6050_Wrapper_h
MPU6050_Wrapper::MPU6050_Wrapper() // Constructor
{
    init();
}
MPU6050_Wrapper::~MPU6050_Wrapper() // Destructor
{
    stop();
}

// On/Off
int MPU6050_Wrapper::init()
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

    // Enable MPU6050
    i2cWriteByteData(fd, 0x68, 0x00);

    return 0;
}

int MPU6050_Wrapper::stop()
{
    i2cClose(fd);
    gpioTerminate();
    return 0;
}

// Read
void MPU6050_Wrapper::readMPU6050(uint8_t reg, uint8_t *data, int len)
{
    i2cWriteByteData(fd, reg, 0);
    i2cReadI2CBlockData(fd, reg, reinterpret_cast<char *>(data), len);
}

// Convert
double MPU6050_Wrapper::convertAccel(int16_t raw)
{
    return raw / 16384.0; // +-2g
}
double MPU6050_Wrapper::convertGyro(int16_t raw)
{
    return raw / 131.0; // +-250
}

// Process
void MPU6050_Wrapper::Process(double& accelX_g, double& accelY_g, double& accelZ_g, double& gyroX_degPerSec, double& gyroY_degPerSec, double& gyroZ_degPerSec)
{
    //Array
    uint8_t accelData[6];
    uint8_t gyroData[6];

    // Accelerometer
    readMPU6050(ACCEL_XOUT_H, accelData, sizeof(accelData));
    int16_t accelX = (accelData[0] << 8) | accelData[1];
    int16_t accelY = (accelData[2] << 8) | accelData[3];
    int16_t accelZ = (accelData[4] << 8) | accelData[5];

    // Gyroscope
    readMPU6050(GYRO_XOUT_H, gyroData, sizeof(gyroData));
    int16_t gyroX = (gyroData[0] << 8) | gyroData[1];
    int16_t gyroY = (gyroData[2] << 8) | gyroData[3];
    int16_t gyroZ = (gyroData[4] << 8) | gyroData[5];

    // Convert
    accelX_g = convertAccel(accelX);
    accelY_g = convertAccel(accelY);
    accelZ_g = convertAccel(accelZ);
    gyroX_degPerSec = convertGyro(gyroX);
    gyroY_degPerSec = convertGyro(gyroY);
    gyroZ_degPerSec = convertGyro(gyroZ);
}
