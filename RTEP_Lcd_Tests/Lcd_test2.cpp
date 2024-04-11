#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address
const int LCD_ADDRESS = 0x27;

// Set the LCD dimensions
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;

// Create an instance of the LiquidCrystal_I2C class
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
    // Initialize the LCD
    lcd.begin(LCD_COLUMNS, LCD_ROWS);
    lcd.backlight();
}

void loop() {
    // Clear the LCD screen
    lcd.clear();

    // Set the cursor to the first column of the first row
    lcd.setCursor(0, 0);

    // Print a message on the LCD
    lcd.print("Hello, LCD12864!");

    // Set the cursor to the first column of the second row
    lcd.setCursor(0, 1);

    // Print another message on the LCD
    lcd.print("This is a test.");

    // Delay for a while
    delay(2000);
}