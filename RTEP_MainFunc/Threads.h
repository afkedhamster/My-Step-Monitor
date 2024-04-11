#ifndef Threads_h
#define Threads_h

#include <iostream>
#include <thread>
#include <chrono>

class Threads{
public:
    int i = 0;
    void start();
    // void stop();
    // void pause();
    // void resume();
    // void restart();
    // void setPriority();
    // void setAffinity();
    void doSomething();
    std::thread thr;
};

#endif