#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h> 

// ����
#define BUZZER_PIN 0 // ����

// ��ʼ��
void wiringPi_st()
{
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi library" << std::endl;
        exit(1);
    }
}

// ��ʼ��
void testwiringPi_st()
{
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi library" << std::endl;
        exit(1);
    }
}

void setup()
{
    pinMode(BUZZER_PIN, OUTPUT); // ���
}

// ����
void loop(int frequency, int duration)
{
    for (int i = 0; i < duration / 2; i++) {
        digitalWrite(BUZZER_PIN, LOW); // ������
        delay(1000 / frequency); // ��ʱ1ms 
        digitalWrite(BUZZER_PIN, HIGH); // ��������
        delay(1000 / frequency); // ��ʱ1ms 
    }
}

int main()
{
    wiringPi_st();
    setup();
    loop(1000, 3000); // 1000Hz��1��
    return 0;
}