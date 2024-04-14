@@ -0,0 +1,296 @@
#include <iostream>
#include <pigpio.h>
#include <thread>
#include <chrono>
#include <stdint.h>


// Define Address and Registers
#define MPU6050_ADDR 0x68
#define PWR_MGMT_1 0x6B
#define SMPLRT_DIV 0x19
#define CONFIG 0x1a
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x45
#define GYRO_ZOUT_H 0x47
#define Time 20

// Pin
#define SDA_PIN 2
#define SCL_PIN 3


// GPIO
static struct gpio_config
{
    int SDA;
    int SCL;
    short accelX;
    short accelY;
    short accelZ;
    short gyroX;
    short gyroY;
    short gyroZ;
} config;


// I2C On/Off
void i2c_start(void)
{
    gpioSetMode(config.SDA, PI_OUTPUT);
    gpioSetMode(config.SCL, PI_OUTPUT);
	gpioWrite(config.SDA, 1);
    gpioWrite(config.SCL, 1);
    gpioDelay(Time);
    // SCL=1 SDA=0
	gpioWrite(config.SDA, 0);
    gpioDelay(Time);
}

void i2c_stop(void)
{
    gpioWrite(config.SCL, 1);
    gpioSetMode(config.SDA, PI_OUTPUT);
    gpioWrite(config.SDA, 0);
    gpioDelay(Time);
    // SCL=0 SDA=1
    gpioWrite(config.SDA, 1);
}


// ACK
unsigned char i2c_read_ack(void)
{
    unsigned char r;  
    gpioSetMode(config.SDA, PI_INPUT);
    // SCL=1 Read
    gpioWrite(config.SCL, 1);
    gpioDelay(Time);
    r = gpioRead(config.SDA);
    gpioDelay(Time);
    // Reset
    gpioWrite(config.SCL, 0);
    gpioDelay(Time);
    // r=SDA=0 ACK; r=SDA=1 NoACK
    return r;
}

void i2c_send_ack(void)
{
     // SCL=0 SDA=0
    gpioWrite(config.SCL, 0);
    gpioSetMode(config.SDA, PI_OUTPUT);
    gpioDelay(Time);
    // SCL=1 Read Read SDA=0 ACK
    gpioWrite(config.SCL, 1);
    gpioDelay(Time);
    // Reset
    gpioWrite(config.SCL, 0);
    gpioDelay(Time);
}

void i2c_send_noack(void)
{
    // SCL=0 SDA=1
    gpioWrite(config.SCL, 0);
    gpioSetMode(config.SDA, PI_OUTPUT);
    gpioWrite(config.SDA, 1);
    gpioDelay(Time);
    // SCL=1 Read SDA=1 NoACK
    gpioWrite(config.SCL, 1);
    gpioDelay(Time);
    // Reset
    gpioWrite(config.SCL, 0);
    gpioDelay(Time);
}

// I2C Byte Read/Write
unsigned char i2c_read_byte(void)
{  
	int i;  
	unsigned char r = 0; 

	gpioWrite(config.SCL, 0);
    gpioDelay(Time);
    gpioSetMode(config.SDA, PI_INPUT);

	for (i=7; i>=0; i--) 
    {  
		gpioWrite(config.SCL, 1); // Read
        gpioDelay(Time);
        // Read from 7 to 0
        r = (r << 1) | gpioRead(config.SDA);
        gpioWrite(config.SCL, 0); // Reset
        gpioDelay(Time);
	}
    // Finish Reading; Send NoACK 
	i2c_send_noack(); 

	return r;  
}

void i2c_write_byte(unsigned char b)
{  
	int i;

	gpioSetMode(config.SDA, PI_OUTPUT);
    gpioDelay(Time);

    for (i = 7; i >= 0; i--)
    {
        gpioWrite(config.SCL, 0); // Write
        gpioDelay(Time);
        // Write SDA from 7 to 0
        gpioWrite(config.SDA, b & (1 << i));
        gpioDelay(Time);
        gpioWrite(config.SCL, 1); // Read
        gpioDelay(Time);
    }
    gpioWrite(config.SCL, 0); // Reset
    gpioDelay(Time);
    // Check ACK
    if (i2c_read_ack() == 1) // r=1 NoACK
    {
        std::cerr << "this is no ACK" << std::endl;
        i2c_stop(); // Stop
    }
}

// I2C Read/Write
void i2c_read(unsigned char addr, unsigned char* buf, int len)
{  
	int i;  
	unsigned char t;
	i2c_start();
    // Address
	i2c_write_byte(0xD0); // Set 0 to Write (11010000)
	t = addr;
	i2c_write_byte(t); // Address
    // Restart
	i2c_start();
    // Read Buffer
	i2c_write_byte(0xD1); // Set 1 to Read (11010001)
	for (i=0; i<len; i++)
    {
		buf[i] = i2c_read_byte(); // Data
    }
	i2c_stop();
}

void i2c_write(unsigned char addr, unsigned char buf)
{  
	unsigned char t;  
	i2c_start();
    // Address
	i2c_write_byte(0xD0); // Set 0 to Write
	t = addr;
    // Write Buffer
	i2c_write_byte(t); // Address
	i2c_write_byte(buf); // Data
    // Send ACK to Read
	i2c_send_ack(); 
	i2c_stop(); 
}


// Data
int16_t GetData(char REG_Address)
{
    int16_t H, L; 
    i2c_read(REG_Address, (unsigned char *)&H, 1);
    i2c_read(REG_Address + 1, (unsigned char *)&L, 1);
    return (H << 8) + L; // Read from 7 to 0
}


// Initialize MPU6050
static uint8 MPU6050_Init(void)
{
    unsigned char a = 0x80; // 10000000
    unsigned char b = 0x07; // 00000111
    unsigned char c = 0x06; // 00000110
    unsigned char e = 0x10; // 00010000
    unsigned char d;
    gpioDelay(100);
    // Reset
    i2c_write(0x6b, a); // Power
    gpioDelay(100);
    i2c_write(0x19, b); // Sample
    gpioDelay(100);
    i2c_write(0x1a, c); // Config
    gpioDelay(100);
    //Accelerometer
    i2c_read(0x1c, &d, 1);
	d = d & 0xE7; // 11100111; +-2g
	i2c_write(0x1c, d); // Rewrite
    gpioDelay(10);
    // Gyroscope
	i2c_write(0x1b, e); // +-250 deg
	return(1);
}


// Convert
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
    // Initialize Pigpio
    if (gpioInitialise() < 0)
    {
        std::cerr << "Failed to initialize pigpio." << std::endl;
        return 1;
    }

    // Initialize Pin
    config.SDA = SDA_PIN;
    config.SCL = SCL_PIN;

    // Enable MPU6050
    MPU6050_Init();

    // Main
    while (true)
    {
        // Accelerometer & Gyroscope
        config.accelX = GetData(ACCEL_XOUT_H);
        config.accelY = GetData(ACCEL_YOUT_H);
        config.accelZ = GetData(ACCEL_ZOUT_H);
        config.gyroX = GetData(GYRO_XOUT_H);
        config.gyroY = GetData(GYRO_YOUT_H);
        config.gyroZ = GetData(GYRO_ZOUT_H);

        // Convert
        double accelX_g = convertAccel(config.accelX);
        double accelY_g = convertAccel(config.accelY);
        double accelZ_g = convertAccel(config.accelZ);
        double gyroX_degPerSec = convertGyro(config.gyroX);
        double gyroY_degPerSec = convertGyro(config.gyroY);
        double gyroZ_degPerSec = convertGyro(config.gyroZ);

        // Display
        std::cout << "Acceleration (g): X=" << accelX_g << ", Y=" << accelY_g << ", Z=" << accelZ_g << std::endl;
        std::cout << "Angular Rate (deg/s): X=" << gyroX_degPerSec << ", Y=" << gyroY_degPerSec << ", Z=" << gyroZ_degPerSec << std::endl;

        // Delay
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Terminate Pigpio
    gpioTerminate();

    return 0;
}