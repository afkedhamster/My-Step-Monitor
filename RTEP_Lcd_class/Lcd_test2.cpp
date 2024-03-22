#include <wiringPi.h>
#include <iostream>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdio.h>

#define LCD_ADDR 0x00
#define LCD_INIT_CMD 0x38
#define LCD_DISP_ON 0x0C
#define LCD_CLR_CMD 0x01

class LCD12864 {
private:
    int fd;

    void lcdCommand(unsigned char value) {
        unsigned char buffer[2];
        buffer[0] = 0x00;
        buffer[1] = value;

        if (write(fd, buffer, 2) != 2) {
            std::cerr << "I2C write failed" << std::endl;
        }
        usleep(1000);
    }

    void lcdData(unsigned char value) {
        unsigned char buffer[2];
        buffer[0] = 0x40;
        buffer[1] = value;
        write(fd, buffer, 2);
        usleep(1000);
    }

public:
    LCD12864() {
        if (wiringPiSetup() == -1) {
            std::cerr << "Failed to initialize WiringPi library." << std::endl;
            exit(1);
        }

        if ((fd = wiringPiI2CSetup(LCD_ADDR)) == -1) {
            std::cerr << "Failed to open I2C device." << std::endl;
            exit(1);
        }

        lcdCommand(0x33);
        lcdCommand(0x32);
        lcdCommand(0x28);
        lcdCommand(LCD_DISP_ON);
        lcdCommand(LCD_CLR_CMD);
        delay(2000);
    }

    void writeString(const char* str) {
        while (*str) {
            lcdData(*str++);
        }
    }

    void clear() {
        lcdCommand(LCD_CLR_CMD);
    }

    void setCursor(unsigned char pos) {
        lcdCommand(pos);
    }
};

int main() {
    LCD12864 lcd;

    lcd.setCursor(0x80);
    lcd.writeString("LCD12864 Test");
    lcd.setCursor(0xC0);
    lcd.writeString("Hello, world!");

    delay(5000);

    lcd.clear();

    lcd.setCursor(0x80);
    lcd.writeString("Test Passed!");

    return 0;
}