#ifndef Threads_h
#define Threads_h

#include <iostream>
#include <thread>
#include <chrono>
#include "../RTEP_Buzzer_class/Buzzer.h"
#include "../RTEP_Lcd1602/LCD.h"

enum Pos_change{
    FALL,
    RISE,
    SIT2LAY,
    LAY2SIT,
    SIT2STAND,
    STAND2SIT,
    STAND2LAY,
    LAY2STAND
};
class Threads{
public: 
    int i = 0;
    void start(){
        thread = std::thread(&Threads::doSomething, this);
    };
    typedef void (*CallbackFunc)();   
    //virtual void eventhandler() = 0;
    void regInf_Buzzer(Buzzer* obj,CallbackFunc callbackFunc){
        buzzer = obj;
        this->callbackFunc = callbackFunc;
    };
    void regInf_LCD(LCD* obj,CallbackFunc callbackFunc){
        lcd = obj;
        this->callbackFunc = callbackFunc;
    };
    void stop(){
        thread.join();};
    void restart(){
        thread = std::thread(&Threads::doSomething, this);
    };
    void trigger_buzz_lcd(enum Pos_change posChange){
        if (buzzer != nullptr && lcd !=nullptr && posChange == FALL){
            buzzer->buzz(50000);
            lcd->print("Emergengcy!!! Fall detected!!!");
            callbackFunc();
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == RISE){
            buzzer->buzz(3000);
            lcd->print("Rise detected!");
            callbackFunc();
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == SIT2LAY){
            buzzer->buzz(3000);
            lcd->print("Sit to lay detected!");
            callbackFunc();
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == LAY2SIT){
            buzzer->buzz(3000);
            lcd->print("Lay to sit detected!");
            callbackFunc();
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == SIT2STAND){
            buzzer->buzz(3000);
            lcd->print("Sit to stand detected!");
            callbackFunc();
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == STAND2SIT){
            buzzer->buzz(3000);
            lcd->print("Stand to sit detected!");
            callbackFunc();
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == STAND2LAY){
            buzzer->buzz(3000);
            lcd->print("Stand to lay detected!");
            callbackFunc();
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == LAY2STAND){
            buzzer->buzz(3000);
            lcd->print("Lay to stand detected!");
            callbackFunc();
        }
    }
    // void pause();
    // void resume();
    // void setPriority();
    // void setAffinity();
    void doSomething();
    std::thread thread;
private:
    Buzzer* buzzer = nullptr;
    LCD* lcd = nullptr;
    CallbackFunc callbackFunc = nullptr;
};

#endif