#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h> 

// Set GPIO Pin for buzzer
#define BUZZER_PIN 0 // 0 stands for the GPIO No.

// Initialization of wiringPi function
void wiringPi_st()
{
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi library" << std::endl;
        exit(1);
    }
}

void setup()
{
    pinMode(BUZZER_PIN, OUTPUT); //Set Pin mode > output 
}

// Generate high frequency square wave to drive the buzzer
void Beep(int frequency, int duration)
{
    for (int i = 0; i < duration / 2; i++) {
        digitalWrite(BUZZER_PIN, LOW); // low voltage
        delay( 1000 / frequency ); // delay for 1 ms 
        digitalWrite(BUZZER_PIN, HIGH); // high voltage
        delay( 1000 / frequency ); // delay for 1 ms
    }
}

int main()
{
    wiringPi_st();
    setup();
    Beep(1000,1000); // set frequency = 1000Hz，duration = 3000 ms
    Beep(1500,1000);
    Beep(1800,2000);
    return 0;
}
