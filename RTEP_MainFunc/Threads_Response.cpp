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
    void start(){
        thread = std::thread(&Threads_Response::doSomething, this);
    };
    //typedef void (*CallbackFunc)();   
    //virtual void eventhandler() = 0;
    void regInf_Buzzer(Buzzer* bobj){
        buzzer = bobj;
    };
    void regInf_LCD(LCD* lobj){
        lcd = lobj;
    };
    void stop(){
        thread.join();};
    void restart(){
        thread = std::thread(&Threads_Response::doSomething, this);
    };
    void trigger_buzz_lcd(enum POS_CHANGE  posChange){
        if (buzzer != nullptr && lcd !=nullptr && posChange == FALL){
            buzzer->Beep(5000, 20000)
            lcd->print("Emergengcy!!! Fall detected!!!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == RISE){
            buzzer->Beep(3000, 1500)
            lcd->print("Rise detected!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == SIT2LAY){
            buzzer->Beep(2000, 1000);
            lcd->print("Sit to lay detected!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == STAND2SIT){
            buzzer->Beep(2000, 1000);
            lcd->print("Stand to sit detected!");
        }
        if (buzzer != nullptr && lcd !=nullptr && posChange == STAND2LAY){
            buzzer->Beep(2000, 1000);
            lcd->print("Stand to lay detected!");
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
