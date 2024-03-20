#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#define pin 7
//int vaule;
int main(){
    wiringPiSetup();
    pinMode(pin,INPUT);
    while(1)
    {
        if(digitalRead(pin)==0)
        {
        //有压力低电平
             puts("有压力...");
             delay(1000);
             //vaule = analogread(pin)
             //puts(vaule);
        }
	}
    return 0;
}