#ifndef LCD_H
#define LCD_H

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class LCD {
    int I2C_ADDR;
    int LCD_CHR;
    int LCD_CMD;
    int LCD_Backlight = 0x08;
    int ENABLE = 0b00000100;
    int Line1;
    int Line2;

    int currentln;
    char alignment;
    int pause;

  

    void set_variables();
    void lcd_init();
    void lcd_byte(int bits, int mode);
    void lcd_toggle_enable(int bits);

    int fd;

    public:
        LCD(const char& alignment = 'l', int pause = 0);
        void clear(int pause);
        //Note: this changes currentln value
        void set_location(int line);
        void printNum(int number);
        void printNum(float number);
        void print(const string& message);

        void set_delay(int pause);
        void set_alignment(const char& c);
        void operator<<(const char *s);
        void operator<<(const string& s);
};

#endif