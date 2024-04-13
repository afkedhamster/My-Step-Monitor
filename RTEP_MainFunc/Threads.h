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

#endif