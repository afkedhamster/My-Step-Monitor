/*
未经封装的ads1115（adc模块）与C25A压力传感器测试单元
Unpackaged ads1115 (adc module) and C25A pressure sensor test unit
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>


// Define Address and Registers
#define I2C_DEVICE_PATH "/dev/i2c-1" // Change
#define ADS1115_ADDRESS 0x48 
#define ADS1115_REG_POINTER_CONVERT 0x00
#define ADS1115_REG_POINTER_CONFIG  0x01
// Parameters
#define ADS1115_REG_CONFIG_DEFAULT \
    (ADS1115_REG_CONFIG_CQUE_NONE | \
     ADS1115_REG_CONFIG_CLAT_NONLAT | \
     ADS1115_REG_CONFIG_CPOL_ACTVLOW | \
     ADS1115_REG_CONFIG_CMODE_TRAD | \
     ADS1115_REG_CONFIG_DR_128SPS | \
     ADS1115_REG_CONFIG_MODE_SINGLE)
#define ADS1115_REG_CONFIG_PGA_RANGE ADS1015_REG_CONFIG_PGA_4_096V


// I2C
int i2cFile;

// On/Off
void i2c_start() 
{
    i2cFile = open(I2C_DEVICE_PATH, O_RDWR);
    if (i2cFile < 0) {
        perror("Unable to open I2C device");
        exit(1);
    }
}

void i2c_stop() 
{
    close(i2cFile);
}

// Read/Write
void i2cWriteReg(uint8_t reg, uint16_t value) 
{
    uint8_t buf[3];
    buf[0] = reg;
    buf[1] = (value >> 8) & 0xFF;
    buf[2] = value & 0xFF;
    if (write(i2cFile, buf, 3) != 3) {
        perror("Unable to write to I2C device");
        exit(1);
    }
}

int16_t i2cRead(uint8_t reg) 
{
    uint8_t buf[2];
    buf[0] = reg;
    if (write(i2cFile, &buf[0], 1) != 1) {
        perror("Unable to write to I2C device");
        exit(1);
    }
    if (read(i2cFile, buf, 2) != 2) {
        perror("Unable to read from I2C device");
        exit(1);
    }
    return (buf[0] << 8) | buf[1];
}

// Analog Data
int16_t analogRead() 
{
    i2cWriteReg(ADS1115_REG_POINTER_CONFIG,0x8583); 
    usleep(10000); // Wait
    return i2cRead(ADS1115_REG_POINTER_CONVERT);
}

int main() 
{
    i2cInit();
    int16_t value;
    double voltage;
    
    while (1) {
        value = analogRead();
        voltage = value * (4.096 / 32768);
        printf("ADS1115 reading: %d\n\r", value);
        printf("ADS1115 voltage: %g\n\r", voltage);
        usleep(1000000); // Delay
    }

    i2cClose();
    return 0;
}
