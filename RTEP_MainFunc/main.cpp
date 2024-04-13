#include <iostream>
#include <thread>
#include <chrono>
#include "../RTEP_I2C_class/I2C.h"
#include "../RTEP_Lcd1602/LCD.h"
#include "./Threads.h"
#include "./Self_defined_classes.h"

using namespace std;

int main()
{
    Threads_Response t_res;
    Buzzer buzzer;
    LCD lcd;
    std::thread tid_res_thread(&Threads_Response::start, &t_res, &buzzer, &lcd);
    tid_res_thread.join();
    
    return 0;
}
// Path: RTEP_MainFunc/Threads.cpp
// Compare this snippet from RTEP_Lcd1602/LCD.cpp:
// #include "LCD.h"
