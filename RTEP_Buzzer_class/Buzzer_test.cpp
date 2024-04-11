#include <pigpio.h>
#include <unistd.h>
#include <iostream>
#include "./Buzzer.h"

#define PIN 0

int main() {
    try {
        Buzzer buzzer(PIN);
        for (;;) {
            buzzer.buzz(1000);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}