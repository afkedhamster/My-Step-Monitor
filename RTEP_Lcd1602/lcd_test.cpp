#include <pigpio.h>
#include "./LCD.h"
#include <iostream>

using namespace std;

int main(){
    LCD lcd;
    char r = 'r';
    char l = 'l';
    char m = 'm';

    while(1){
        string hello = "Hello";

        lcd.clear(0);
        lcd.set_location(1);
        lcd.set_delay(500);
        lcd << hello;
        
        lcd.set_location(2);
        lcd.set_delay(500);
        lcd << "My step Monitor";

        gpioDelay(100000);
    }

    return 0;
}
