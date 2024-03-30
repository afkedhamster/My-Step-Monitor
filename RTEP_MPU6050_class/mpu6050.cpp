#include <iostream>
#include <wiringPiI2C.h>

// MPU6050 registers
#define MPU6050_ADDR 0x68
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x45
#define GYRO_ZOUT_H 0x47

int main() {
    // Initialize I2C communication
    int fd = wiringPiI2CSetup(MPU6050_ADDR);
    if (fd == -1) {
        std::cerr << "Failed to initialize I2C communication." << std::endl;
        return 1;
    }

    // Enable MPU6050
    wiringPiI2CWriteReg8(fd, 0x6B, 0x00);

    while (true) {
        // Read accelerometer data
        int16_t accelX = wiringPiI2CReadReg16(fd, ACCEL_XOUT_H);
        int16_t accelY = wiringPiI2CReadReg16(fd, ACCEL_YOUT_H);
        int16_t accelZ = wiringPiI2CReadReg16(fd, ACCEL_ZOUT_H);

        // Read gyroscope data
        int16_t gyroX = wiringPiI2CReadReg16(fd, GYRO_XOUT_H);
        int16_t gyroY = wiringPiI2CReadReg16(fd, GYRO_YOUT_H);
        int16_t gyroZ = wiringPiI2CReadReg16(fd, GYRO_ZOUT_H);

        // Convert raw data to meaningful values
        double accelX_g = accelX / 16384.0;
        double accelY_g = accelY / 16384.0;
        double accelZ_g = accelZ / 16384.0;
        double gyroX_degPerSec = gyroX / 131.0;
        double gyroY_degPerSec = gyroY / 131.0;
        double gyroZ_degPerSec = gyroZ / 131.0;

        // Display the values
        std::cout << "Acceleration (g): X=" << accelX_g << ", Y=" << accelY_g << ", Z=" << accelZ_g << std::endl;
        std::cout << "Angular Rate (deg/s): X=" << gyroX_degPerSec << ", Y=" << gyroY_degPerSec << ", Z=" << gyroZ_degPerSec << std::endl;

        // Delay for a short period
        delay(100);
    }

    return 0;
}