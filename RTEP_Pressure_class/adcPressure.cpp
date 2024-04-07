#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHANNEL 0
#define ADC_CHANNEL 0

//read the pressure value from the ADC
int readADC(int adcnum) {
    unsigned char buffer[3];
    buffer[0] = 1; // Start bit
    buffer[1] = (8 + adcnum) << 4;
    buffer[2] = 0;

    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);

    return ((buffer[1] & 3) << 8) + buffer[2];
}

//each 1 second read the pressure value and print
int main() {
    wiringPiSetup();
    wiringPiSPISetup(SPI_CHANNEL, 1000000);

    while (1) {
        int value = readADC(ADC_CHANNEL);
        printf("Pressure: %d\n", value);
        delay(1000);
    }

    return 0;
}