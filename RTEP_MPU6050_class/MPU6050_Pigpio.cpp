#include <iostream>
#include <pigpio.h>
#include <thread>
#include <chrono>

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

// Reading Function
void readMPU6050(int fd, uint8_t reg, uint8_t *data, int len)
{
    i2cWriteByte(fd, reg);
    i2cReadI2CBlockData(fd, reg, reinterpret_cast<char*>(data), len);
}

int main()
{
    // Initialize Pigpio
    if (gpioInitialise() < 0)
    {
        std::cerr << "Failed to initialize pigpio." << std::endl;
        return 1;
    }

    // Initialize I2C
    int fd = i2cOpen(1, MPU6050_ADDR, 0);
    if (fd < 0)
    {
        std::cerr << "Failed to initialize I2C communication." << std::endl;
        gpioTerminate();
        return 1;
    }

    // Enable MPU6050
    i2cWriteByteData(fd, 0x6B, 0x00);

    // Main
    while (true)
    {
        //Array
        uint8_t accelData[6];
        uint8_t gyroData[6];

        // Accelerometer
        readMPU6050(fd, ACCEL_XOUT_H, accelData, sizeof(accelData));
        int16_t accelX = (accelData[0] << 8) | accelData[1];
        int16_t accelY = (accelData[2] << 8) | accelData[3];
        int16_t accelZ = (accelData[4] << 8) | accelData[5];

        // Gyroscope
        readMPU6050(fd, GYRO_XOUT_H, gyroData, sizeof(gyroData));
        int16_t gyroX = (gyroData[0] << 8) | gyroData[1];
        int16_t gyroY = (gyroData[2] << 8) | gyroData[3];
        int16_t gyroZ = (gyroData[4] << 8) | gyroData[5];

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
    i2cClose(fd);

    // Terminate pigpio
    gpioTerminate();

    return 0;
}
