#include "LCD.h"
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
        lcd << "This is a test";

        delay(1000);
    }

    return 0;
}