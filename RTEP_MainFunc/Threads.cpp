#ifndef Threads_h
#define Threads_h

#include <iostream>
#include <thread>
#include <chrono>
#include "../RTEP_Buzzer_class/Buzzer.cpp"
#include "../RTEP_Lcd1602/LCD.cpp"

enum Pos_change{
    FALL,
    RISE,
    WALKING,
    SITDOWN,
    LAYDOWN
};
class Threads_Response{
public: 
    void start(){
        thread = std::thread(&Threads_Response::doSomething, this);
    };
    //typedef void (*CallbackFunc)();   
    //virtual void eventhandler() = 0;
    void regInf_Buzzer(Buzzer* obj){
        buzzer = obj;
    };
    void regInf_LCD(LCD* obj){
        lcd = obj;
    };
    void stop(){
        thread.join();};
    void restart(){
        thread = std::thread(&Threads_Response::doSomething, this);
    };
    void trigger_buzz_lcd(enum Pos_change posChange){
        if (buzzer != nullptr && lcd !=nullptr && posChange == FALL){
            buzzer->buzz(50000);
            lcd->print("Emergengcy!!! Fall detected!!!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == RISE){
            buzzer->buzz(3000);
            lcd->print("Rise detected!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == SIT2LAY){
            buzzer->buzz(3000);
            lcd->print("Sit to lay detected!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == LAY2SIT){
            buzzer->buzz(3000);
            lcd->print("Lay to sit detected!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == SIT2STAND){
            buzzer->buzz(3000);
            lcd->print("Sit to stand detected!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == STAND2SIT){
            buzzer->buzz(3000);
            lcd->print("Stand to sit detected!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == STAND2LAY){
            buzzer->buzz(3000);
            lcd->print("Stand to lay detected!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == LAY2STAND){
            buzzer->buzz(3000);
            lcd->print("Lay to stand detected!");
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
    //CallbackFunc callbackFunc = nullptr;
};

#endif