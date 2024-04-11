#include <iostream>
#include <pigpio.h>

// Pin
#define BUZZER_PIN 0 // GPIO number 27

// Initialize
void Buzzer_init()
{
    // Initialize Pigpio
    if (gpioInitialise() < 0)
    {
        std::cerr << "Failed to initialize pigpio." << std::endl;
    }
    // Set
    gpioSetMode(BUZZER_PIN, PI_OUTPUT); 
}

// High Frequency Square Wave
void Beep(int frequency, int duration)
{
    int halfPeriod = 500000 / frequency; // half period in microseconds
    int iterations = duration * 1000 / (2 * halfPeriod); // number of iterations
    for (int i = 0; i < iterations; i++) {
        gpioWrite(BUZZER_PIN, 0); // Low voltage
        gpioDelay(halfPeriod); // Delay
        gpioWrite(BUZZER_PIN, 1); // High voltage
        gpioDelay(halfPeriod); // Delay
    }
}

int main()
{
    Buzzer_init();
    // Frequency 1000Hz，Duration 1000 ms
    Beep(1000, 1000); 
    Beep(1500, 1000);
    Beep(1800, 2000);

    gpioTerminate(); 

    return 0;
}
