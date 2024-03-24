#include <pigpio.h>
#include <stdint.h>

#define I2C_ADDR 0x00 // Replace with your device's I2C address

int fd; // File descriptor for the I2C device

void I2C_init(void) {
    if (gpioInitialise() < 0) {
        // Handle error
    }

    fd = i2cOpen(1, I2C_ADDR, 0); // Open the I2C device
}

void I2C_start(void) {
    // The pigpio library does not require a separate start function.
    // Communication starts with the i2cWriteByte or i2cReadByte functions.
}

void I2C_stop(void) {
    i2cClose(fd); // Close the I2C device
}

uint8_t I2C_to_write(void) {
    // The pigpio library does not require a separate function to set write mode.
    // Writing is done with the i2cWriteByte function.
    return 0;
}

void I2C_send(uint8_t data) {
    i2cWriteByte(fd, data); // Write a byte of data to the I2C device
}