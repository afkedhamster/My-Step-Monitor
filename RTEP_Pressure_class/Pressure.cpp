#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#define pin 7

//int vaule;
int main(){
    if (gpioInitialise() < 0) {
        std::cout << "GPIO Initlialise Failed" << std::endl;
        return 1;
    }
    gpioSetMode(pin, PI_INPUT);
    while(1)
    {
        if(gpioRead(pin)==0)
        {
        //The pin reads LOW when there is pressure
             std::cout << "有压力" << std::endl;
             delay(1000);
             //vaule = analogRead(pin)
             //puts(vaule);
        }
	}
    return 0;
}