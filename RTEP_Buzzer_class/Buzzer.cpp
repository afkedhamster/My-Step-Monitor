#include <pigpio.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <string>
#define PIN 0

class Buzzer {
private:
    int pin;

public:
    Buzzer(int pin) : pin(pin) {
        if (gpioInitialise() < 0) {
            throw std::runtime_error("GPIO initialization failed");
        }
        gpioSetMode(pin, PI_OUTPUT);
    }

    ~Buzzer() {
        gpioTerminate();
    }

    void buzz(int durationMicroseconds) {
        gpioWrite(pin, 0);
        usleep(durationMicroseconds);
        gpioWrite(pin, 1);
        usleep(durationMicroseconds);
    }
};