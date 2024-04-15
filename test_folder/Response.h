#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>
#include <thread>
#include <chrono>
#include "IPC.h"
#include "Buzzer.h"
#include "LCD.h"

class Response
{
public:
    enum POS_CHANGE
    {
        FALL = 0,
        STAND = 1,
        // WALKING
        SIT = 2,
        LAY = 3,
        RISE = 4,
        SIT2LAY = 5,
        STAND2SIT = 6,
        STAND2LAY = 7,
    };

    Response();

    void start(Buzzer *bobj, LCD *lobj, enum POS_CHANGE *posChange);
    void stop();
    void Read();
    void trigger_buzz_lcd(enum POS_CHANGE posChange);
    
    void wait_R_ready() 

    std::thread thread;

private:
    Buzzer *buzzer = nullptr;
    LCD *lcd = nullptr;

    IPC ipc_C;
};

#endif
