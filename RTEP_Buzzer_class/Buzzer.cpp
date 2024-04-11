#include <pigpio.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <string>

#define BUZZER_PIN 0// 物理引脚27

class Buzzer {
public:
    Buzzer();
    void Buzzer_init();
    ~Buzzer();
    void Beep(int frequency, int duration);
};

Buzzer::Buzzer(){
    Buzzer_init();
}

void Buzzer::Buzzer_init(){
    // Initialize Pigpio
    if (gpioInitialise() < 0)
    {
        std::cerr << "Failed to initialize pigpio." << std::endl;
    }
    // Set
    gpioSetMode(BUZZER_PIN, PI_OUTPUT);
}

Buzzer::~Buzzer() {
    gpioTerminate();
}

void Buzzer::Beep(int frequency, int duration){
    int halfPeriod = 500000 / frequency; // half period in microseconds
    int iterations = duration * 1000 / (2 * halfPeriod); // number of iterations
    for (int i = 0; i < iterations; i++) {
        gpioWrite(BUZZER_PIN, 0); // Low voltage
        gpioDelay(halfPeriod); // Delay
        gpioWrite(BUZZER_PIN, 1); // High voltage
        gpioDelay(halfPeriod); // Delay
    }
}