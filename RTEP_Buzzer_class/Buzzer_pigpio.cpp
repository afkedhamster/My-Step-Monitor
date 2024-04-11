#include <iostream>
#include <pigpio.h>
#include <chrono>
#include <thread>
#include <cstdlib>

// Pin
#define BUZZER_PIN 27 // GPIO number

// Initialize
int setup()
{
    // Initialize Pigpio
    if (gpioInitialise() < 0)
    {
        std::cerr << "Failed to initialize pigpio." << std::endl;
        return -1;
    }
    // Set
    gpioSetMode(BUZZER_PIN, PI_OUTPUT); 
    return 0;
}

// High Frequency Square Wave
void Beep(int frequency, int duration)
{
    float halfPeriod = 500000.0f / frequency; // Half Period
    int iterations = duration * 1000 / (2 * halfPeriod); // Iterations
    
    for (int i = 0; i < iterations; i++) 
    {
        gpioWrite(BUZZER_PIN, PI_LOW); // Low Voltage
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(halfPeriod))); // Delay
        gpioWrite(BUZZER_PIN, PI_HIGH); // High Voltage
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(halfPeriod))); // Delay
    }
}

int main()
{
    if (setup() < 0) 
    {
        return -1;
    }
    // Frequency 1000Hz，Duration 1000 ms
    Beep(1000, 1000); 
    Beep(1500, 1000);
    Beep(1800, 2000);

    gpioTerminate(); 

    return 0;
}
