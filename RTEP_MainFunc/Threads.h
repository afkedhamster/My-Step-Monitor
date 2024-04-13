#ifndef Threads_h
#define Threads_h

#include <iostream>
#include <thread>
#include <chrono>
#include "../RTEP_Buzzer_class/Buzzer.cpp"
#include "../RTEP_Lcd1602/LCD.cpp"

enum POS_CHANGE{
    FALL,
    RISE,
    SIT2LAY,
    STAND2SIT,
    STAND2LAY
};

class Threads_Response{
public:    
    void start();
    //typedef void (*CallbackFunc)();   
    void regInf_Buzzer(Buzzer* bobj);
    void regInf_LCD(LCD* lobj);
    void stop();
    void restart();
    void trigger_buzz_lcd(enum POS_CHANGE  posChange);
    void doSomething();
    std::thread thread;
private:
    private:
    Buzzer* buzzer = nullptr;
    LCD* lcd = nullptr;
    //CallbackFunc callbackFunc = nullptr;
}

class Threads_Read{
public:
    void start();
    void stop();
    void restart();
    void doSomething();
    std::thread thread;
private:
    float accelX_g = 0, accelY_g = 0, accelZ_g = 0;     // acceleration
    float gyroX_degPerSec = 0, gyroY_degPerSec = 0, gyroZ_degPerSec = 0;  // angular velocity
    float pressure1 = 0, pressure2 = 0;        // pressure
}   

class Threads_posEstimation{
public:
    void start();
    void stop();
    void restart();
    void doSomething();
    std::thread thread;
private:
    float accelX_g = 0, accelY_g = 0, accelZ_g = 0;     // acceleration
    float gyroX_degPerSec = 0, gyroY_degPerSec = 0, gyroZ_degPerSec = 0;  // angular velocity
    float pressure1 = 0, pressure2 = 0;        // pressure
}


#endif