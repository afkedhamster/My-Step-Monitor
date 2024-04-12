#include <pigpio.h>
#include <unistd.h>
#include <iostream>
#include "./Buzzer.h"

#define PIN 0

int main() {
    try {
        Buzzer buzzer;
        while(1){
            buzzer.Beep(1000, 1000);
            buzzer.Beep(1500, 1000);
            buzzer.Beep(1800, 2000);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}