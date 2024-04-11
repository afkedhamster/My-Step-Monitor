#include <iostream>
#include <thread>
#include <chrono>
#include "../RTEP_I2C_class/I2C.h"
#include "../RTEP_Lcd1602/LCD.h"
#include "./Threads.h"
#include "./Self_defined_classes.h"

using namespace std;

void Threads::doSomething(){
    bool running = true;
    int i = 0;
    while(running){
        cout << "Thread " << i << " is running" << endl;
        i++;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main(){
    Threads tid_mpu;
    tid_mpu.start();
    
    while(1){
        cout << "Main thread is running" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    return 0;
}
// Path: RTEP_MainFunc/Threads.cpp
// Compare this snippet from RTEP_Lcd1602/LCD.cpp:
// #include "LCD.h"
