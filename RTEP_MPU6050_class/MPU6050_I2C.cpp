#include <iostream>
#include <wiringPi.h>
#include <thread> 
#include <chrono>
#include <unistd.h>

// Define Address and Registers
#define MPU6050_ADDR 0x68
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x45
#define GYRO_ZOUT_H 0x47

// Convert Functions
double convertAccel(int16_t raw) 
{
    return raw / 16384.0; // +-2g
}
double convertGyro(int16_t raw) 
{
    return raw / 131.0; // +-250
}

int main() 
{
    // Initialize WiringPi
    wiringPiSetup();

    // Inintialize I2C
    int fd = wiringPiI2CSetup(MPU6050_ADDR);
    if (fd == -1) 
    {
        std::cerr << "Failed to initialize I2C communication." << std::endl;
        return 1;
    }
    
    // Enable MPU6050
    wiringPiI2CWriteReg8(fd, 0x6B, 0x00);

    // Main
    while (true) 
    {
        // Accelerometer
        int16_t accelX = static_cast<int16_t>(wiringPiI2CReadReg16(fd, ACCEL_XOUT_H));
        int16_t accelY = static_cast<int16_t>(wiringPiI2CReadReg16(fd, ACCEL_YOUT_H));
        int16_t accelZ = static_cast<int16_t>(wiringPiI2CReadReg16(fd, ACCEL_ZOUT_H));

        // Gyroscope
        int16_t gyroX = static_cast<int16_t>(wiringPiI2CReadReg16(fd, GYRO_XOUT_H));
        int16_t gyroY = static_cast<int16_t>(wiringPiI2CReadReg16(fd, GYRO_YOUT_H));
        int16_t gyroZ = static_cast<int16_t>(wiringPiI2CReadReg16(fd, GYRO_ZOUT_H));

        // Convert
        double accelX_g = convertAccel(accelX);
        double accelY_g = convertAccel(accelY);
        double accelZ_g = convertAccel(accelZ);
        double gyroX_degPerSec = convertGyro(gyroX);
        double gyroY_degPerSec = convertGyro(gyroY);
        double gyroZ_degPerSec = convertGyro(gyroZ);

        // Display
        std::cout << "Acceleration (g): X=" << accelX_g << ", Y=" << accelY_g << ", Z=" << accelZ_g << std::endl;
        std::cout << "Angular Rate (deg/s): X=" << gyroX_degPerSec << ", Y=" << gyroY_degPerSec << ", Z=" << gyroZ_degPerSec << std::endl;

        // Delay for a short period
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Close I2C
    close(fd);
    
    return 0;
}
