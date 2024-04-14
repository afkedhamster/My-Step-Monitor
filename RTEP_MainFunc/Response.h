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
        FALL,
        STAND,
        // WALKING,
        SIT,
        LAY,
        RISE,
        SIT2LAY,
        STAND2SIT,
        STAND2LAY,
    };

    void start(Buzzer *bobj, LCD *lobj, enum POS_CHANGE *posChange);
    void Read();
    void trigger_buzz_lcd(enum POS_CHANGE posChange);

    std::thread thread;

private:
    Buzzer *buzzer = nullptr;
    LCD *lcd = nullptr;
};

#endif
