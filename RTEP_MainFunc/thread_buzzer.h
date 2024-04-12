#ifndef Threads_h
#define Threads_h

#include <iostream>
#include <thread>
#include <chrono>
#include "../RTEP_Buzzer_class/Buzzer.cpp"


class Threads_Buzzer
{
public:
    //构造函数 初始化蜂鸣器 还有频率和持续时间
    Threads_Buzzer(int frequency, int duration){
        this->frequency = frequency;
        this->duration = duration;
    };
    //析构函数
    ~Threads_Buzzer(){
        buzzer.~Buzzer();
    };
    //开始线程
    void start(){
        thread = std::thread(&Threads_Buzzer::doSomething, this);
    };
    void stop(){
        thread.join();};
    void restart(){
        thread = std::thread(&Threads_Buzzer::doSomething, this);
    };
    void doSomething(){
        Buzzer buzzer;
        buzzer.Beep(frequency, duration);
    };
    std::thread thread;
public:
    Buzzer buzzer;
    int frequency = 0;
    int duration = 0;
};

//调用
// int main(){
//     Threads_Buzzer threads_Buzzer(1000, 1000);
//     threads_Buzzer.start();
//     threads_Buzzer.stop();
//     return 0;
// }
