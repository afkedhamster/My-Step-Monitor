#include <stdio.h>
#include <pigpio.h>

#define I2C_ADDR 0x68 // MPU6050 的地址
#define ACCEL_XOUT_H 0x3B // 加速度计 X 轴高位寄存器
#define ACCEL_XOUT_L 0x3C // 加速度计 X 轴低位寄存器
#define ACCEL_YOUT_H 0x3D // 加速度计 Y 轴高位寄存器
#define ACCEL_YOUT_L 0x3E // 加速度计 Y 轴低位寄存器
#define ACCEL_ZOUT_H 0x3F // 加速度计 Z 轴高位寄存器
#define ACCEL_ZOUT_L 0x40 // 加速度计 Z 轴低位寄存器
#define GYRO_XOUT_H 0x43 // 陀螺仪 X 轴高位寄存器
#define GYRO_XOUT_L 0x44 // 陀螺仪 X 轴低位寄存器
#define GYRO_YOUT_H 0x45 // 陀螺仪 Y 轴高位寄存器
#define GYRO_YOUT_L 0x46 // 陀螺仪 Y 轴低位寄存器
#define GYRO_ZOUT_H 0x47 // 陀螺仪 Z 轴高位寄存器
#define GYRO_ZOUT_L 0x48 // 陀螺仪 Z 轴低位寄存器

int main() {
    // 初始化pigpio库
    if (gpioInitialise() < 0) {
        printf("pigpio initialization failed.\n");
        return 1;
    }

    // 打开I2C总线
    int handle = i2cOpen(1, I2C_ADDR, 0); // 在树莓派上，I2C总线通常是1
    if (handle < 0) {
        printf("Failed to open I2C device.\n");
        gpioTerminate();
        return 1;
    }

    while (1) {
        // 写入要读取的寄存器地址
        i2cWriteByte(handle, ACCEL_XOUT_H);
        i2cWriteByte(handle, ACCEL_XOUT_L);
        i2cWriteByte(handle, ACCEL_YOUT_H);
        i2cWriteByte(handle, ACCEL_YOUT_L);
        i2cWriteByte(handle, ACCEL_ZOUT_H);
        i2cWriteByte(handle, ACCEL_ZOUT_L);
        i2cWriteByte(handle, GYRO_XOUT_H);
        i2cWriteByte(handle, GYRO_XOUT_L);
        i2cWriteByte(handle, GYRO_YOUT_H);
	i2cWriteByte(handle, GYRO_YOUT_L);
	i2cWriteByte(handle, GYRO_ZOUT_H);
	i2cWriteByte(handle, GYRO_ZOUT_L);
        // 读取加速度计数据
        int16_t accel_x = (i2cReadByte(handle) << 8) | i2cReadByte(handle);
        int16_t accel_y = (i2cReadByte(handle) << 8) | i2cReadByte(handle);
        int16_t accel_z = (i2cReadByte(handle) << 8) | i2cReadByte(handle);

        // 读取陀螺仪数据
        int16_t gyro_x = (i2cReadByte(handle) << 8) | i2cReadByte(handle);
        int16_t gyro_y = (i2cReadByte(handle) << 8) | i2cReadByte(handle);
        int16_t gyro_z = (i2cReadByte(handle) << 8) | i2cReadByte(handle);

        // 输出读取到的数据
        printf("Accelerometer: X=%d, Y=%d, Z=%d\n", accel_x, accel_y, accel_z);
        printf("Gyroscope: X=%d, Y=%d, Z=%d\n", gyro_x, gyro_y, gyro_z);

        // 延时1秒
        gpioDelay(10000); // 1 秒 = 1000000 微秒
    }

    // 关闭I2C设备
    i2cClose(handle);

    // 关闭pigpio库
    gpioTerminate();

    return 0;
}
