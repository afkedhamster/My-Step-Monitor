#include <pigpio.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class LCD
{
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
    LCD(const char &alignment = 'l', int pause = 0, bool mock = false);
    void clear(int pause);
    // Note: this changes currentln value
    void set_location(int line);
    void printNum(int number);
    void printNum(float number);
    void print(const string &message);

    void set_delay(int pause);
    void set_alignment(const char &c);
    void operator<<(const char *s);
    void operator<<(const string &s);
};

LCD::LCD(const char &alignment, int pause, bool mock) : alignment{alignment}, pause{pause}, mockMode{mock}
{

    if (!mockMode)
    {
        if (gpioInitialise() < 0)
            throw runtime_error("Gpio Initialise failed.");
    }

    if (alignment != 'l' && alignment != 'm' && alignment != 'r')
        throw runtime_error("LCD::LCD: alignment has no valid value. (l, m, r).");

    this->set_variables();

    this->lcd_init();
}

void LCD::set_variables()
{
    I2C_ADDR = 0x27;
    LCD_CHR = 1;
    LCD_CMD = 0;
    Line1 = 0x80;
    Line2 = 0xC0;
    currentln = 1;
    LCD_Backlight = 0x08;
    ENABLE = 0b00000100;

    fd = i2cOpen(1, I2C_ADDR, 0);
}

void LCD::lcd_init()
{
    if (!mockMode)
    {
        lcd_byte(0x33, LCD_CMD); // Initialise
        lcd_byte(0x32, LCD_CMD); // Initialise
        lcd_byte(0x06, LCD_CMD); // Cursor move direction
        lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
        lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
        lcd_byte(0x01, LCD_CMD); // Clear display
        gpioDelay(500);
    }
}

void LCD::lcd_byte(int bits, int mode)
{

    // Send byte to data pins
    //  bits = the data
    //  mode = 1 for data, 0 for command
    int bits_high;
    int bits_low;
    // uses the two half byte writes to LCD
    bits_high = mode | (bits & 0xF0) | LCD_Backlight;
    bits_low = mode | ((bits << 4) & 0xF0) | LCD_Backlight;

    // High bits
    i2cReadByteData(fd, bits_high);
    lcd_toggle_enable(bits_high);

    // Low bits
    i2cReadByteData(fd, bits_low);
    lcd_toggle_enable(bits_low);
}

void LCD::lcd_toggle_enable(int bits)
{
    // Toggle enable pin on LCD display
    gpioDelay(500);
    i2cReadByteData(fd, (bits | ENABLE));
    gpioDelay(500);
    i2cReadByteData(fd, (bits & ~ENABLE));
    gpioDelay(500);
}

void LCD::set_location(int line)
{
    if (line == 1)
    {
        lcd_byte(Line1, LCD_CMD);
        currentln = 1;
    }
    else
    {
        lcd_byte(Line2, LCD_CMD);
        currentln = 2;
    }
}

void LCD::clear(int pause)
{
    if (pause > 0)
        gpioDelay(pause);

    lcd_byte(0x01, LCD_CMD);
    lcd_byte(0x02, LCD_CMD);
}

void LCD::printNum(int number)
{
    string temp = to_string(number);

    for (char c : temp)
    {
        lcd_byte(c, LCD_CHR);
        if (pause > 0 && c != ' ')
            ;
        gpioDelay(pause);
    }
}

void LCD::printNum(float number)
{
    string temp = to_string(number);

    for (char c : temp)
    {
        lcd_byte(c, LCD_CHR);
        if (pause > 0 && c != ' ')
            gpioDelay(pause);
    }
}

void LCD::print(const string &message)
{

    // Word-wrap
    if (message.length() > 15)
    {
        string temp_m{message};

        for (int i{0}; i < 16; ++i)
        {
            lcd_byte(temp_m.at(i), LCD_CHR);
            if (pause > 0 && temp_m.at(i) != ' ')
                gpioDelay(pause);
        }

        temp_m = "";

        for (int i{16}; i < message.length(); ++i)
            temp_m += message.at(i);

        if (currentln == 1)
            set_location(2);

        else
        {
            set_location(1);
            clear(0);
        }

        print(temp_m);
    }

    else
    {
        if (alignment == 'l')
        {
            for (int i{0}; i < message.length(); ++i)
            {
                lcd_byte(message.at(i), LCD_CHR);
                if (pause > 0 && message.at(i) != ' ')
                    gpioDelay(pause);
            }
        }

        else if (alignment == 'm')
        {

            string temp;
            int getspaces{0};

            getspaces = (16 - message.length()) / 2 - 1;

            for (int i{0}; i <= getspaces; ++i)
                temp += " ";

            temp += message;
            for (int i{0}; i < temp.length(); ++i)
            {
                lcd_byte(temp.at(i), LCD_CHR);
                if (i > getspaces && temp.at(i) != ' ')
                    gpioDelay(pause);
            }
        }

        if (alignment == 'r')
        {

            string temp;
            int getspaces{0};

            getspaces = (16 - message.length());

            for (int i{0}; i < getspaces; ++i)
                temp += " ";

            temp += message;
            for (int i{0}; i < temp.length(); ++i)
            {
                lcd_byte(temp.at(i), LCD_CHR);
                if (i > getspaces && temp.at(i) != ' ')
                    gpioDelay(pause);
            }
        }
    }
}
/*
void LCD::print(char alignment, const char *s){
    while ( *s ) lcd_byte(*(s++), LCD_CHR);
}*/

void LCD::set_delay(int pause)
{
    this->pause = pause;
}

void LCD::set_alignment(const char &c)
{
    if (alignment != 'l' && alignment != 'm' && alignment != 'r')
        throw runtime_error("LCD::set_alignment: No valid value for variable 'alignment' (options are l, m, r).");
    alignment = c;
}

void LCD::operator<<(const char *s)
{
    string message{s};
    this->print(message);
}

void LCD::operator<<(const string &s)
{
    this->print(s);
}