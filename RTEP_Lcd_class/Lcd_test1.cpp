#include <wiringPi.h>
#include <iostream>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdio.h>

// Define I2C address of LCD12864
#define LCD_ADDR 0x00

// Define commands for LCD initialization
#define LCD_INIT_CMD 0x38 // Function set
#define LCD_DISP_ON 0x0C // Display on, cursor off, blink off
#define LCD_CLR_CMD 0x01  // Clear display

// Function to send command to LCD
// void lcdCommand(int fd, unsigned char value) {
//     unsigned char buffer[2];
//     buffer[0] = 0x00; // Control byte for command
//     buffer[1] = value;
//     write(fd, buffer, 2);
//     delay(1000);
//     //usleep(1000);
//     puts("write Command done");
//     return;
// }

void lcdCommand(int fd, unsigned char value) {
    unsigned char buffer[2];
    buffer[0] = 0x00; // Control byte for command
    buffer[1] = value;

    if (write(fd, buffer, 2) != 2) {
        std::cerr << "I2C write failed" << std::endl;
    }
    usleep(1000); // Wait for 1ms to let the LCD process the command
}

// Function to send data to LCD
void lcdData(int fd, unsigned char value) {
    unsigned char buffer[2];
    buffer[0] = 0x40; // Control byte for data
    buffer[1] = value;
    write(fd, buffer, 2);
    delay(1000);
    //usleep(1000);
    puts("Write data done");
    return;
}

// Function to initialize LCD
void lcdInit(int fd) {
    lcdCommand(fd, 0x33); // Initialize
    lcdCommand(fd, 0x32); // Initialize
    lcdCommand(fd, 0x28); // 4-bit
    lcdCommand(fd, LCD_DISP_ON);  // Display on
    lcdCommand(fd, LCD_CLR_CMD);  // Clear display
    delay(2000);
    //usleep(2000);
    puts("Init done");
    return;
}

// Function to write string to LCD
void lcdWriteString(int fd, const char* str) {
    while (*str) {
        lcdData(fd, *str++);
    }
    puts("Write str done");
}

int main() {
    int lcd_fd;

    // Initialize wiringPi library
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi library." << std::endl;
        puts("1111");
        return 1;
    }

    // Open I2C device
    if ((lcd_fd = wiringPiI2CSetup(LCD_ADDR)) == -1) {
        std::cerr << "Failed to open I2C device." << std::endl;
        puts("2222");
        return 1;
    }
    printf("%d",lcd_fd);
    // Initialize LCD
    lcdCommand(lcd_fd, LCD_CLR_CMD);  // Clear display
    lcdInit(lcd_fd);

    // Write test messages to LCD
    lcdCommand(lcd_fd, 0x80); // Set cursor to first line
    lcdWriteString(lcd_fd, "LCD12864 Test");
    lcdCommand(lcd_fd, 0xC0); // Set cursor to second line
    lcdWriteString(lcd_fd, "Hello, world!");
    
    puts("First part done");
    // Wait for a few seconds
    delay(5000);
     
    // Clear the display
    lcdCommand(lcd_fd, LCD_CLR_CMD);

    // Write another message
    lcdCommand(lcd_fd, 0x80); // Set cursor to first line
    lcdWriteString(lcd_fd, "Test Passed!");
    puts("second part done");
    return 0;
}
