#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h> 

// 引脚
#define BUZZER_PIN 0 // 板子

// 初始化
void wiringPi_st()
{
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi library" << std::endl;
        exit(1);
    }
}

void setup()
{
    pinMode(BUZZER_PIN, OUTPUT); // 输出
}

// 发声
void Beep(int frequency, int duration)
{
    for (int i = 0; i < duration / 2; i++) {
        digitalWrite(BUZZER_PIN, LOW); // 发声音
        delay( 1000 / frequency ); // 延时1ms 
        digitalWrite(BUZZER_PIN, HIGH); // 不发声音
        delay( 1000 / frequency ); // 延时1ms 
    }
}

int main()
{
    wiringPi_st();
    setup();
    Beep(1000, 1000); // 1000Hz，3000ms
    Beep(1500,1000)
    return 0;
}
