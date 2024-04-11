#include <thread>  // std::thread
#include <iostream> // std::cout
#include <chrono>   // std::chrono::seconds

class Threads{
public:
    int i = 0;
    void start(){
        thr = std::thread(&Threads::doSomething, this);
    };
    // void stop();
    // void pause();
    // void resume();
    // void restart();
    // void setPriority();
    // void setAffinity();
    void doSomething();
    std::thread thr;
};