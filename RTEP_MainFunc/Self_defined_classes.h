// Screen
#ifndef SCREEN_H
#define SCREEN_H

#include <string>

class Screen {
public:
    Screen();
    void displayText(const std::string& text);
    void bmp_read(int address);
    void display_bmp(int bmp);
};

#endif // SCREEN_H

// PostureMonitor
#ifndef POSTURE_MONITOR_H
#define POSTURE_MONITOR_H

class PostureMonitor {
public:
    PostureMonitor(Screen& screen);
    void handlePostureChange();
private:
    Screen& screen;
};

#endif // POSTURE_MONITOR_H

// Posture_change
#ifndef POS_CHANGE_H
#define POS_CHANGE_H

class PostureChange{
public:
	PostureChange();
    int previous_data;
    int current_data;
    // compare function, need to be modified 
    void Compare(PostureMonitor monitor) {
       bool res = ((current_data - previous_data) / 100) > 1;
        if (res) {
            std::string text = "posture changed";
            monitor.handlePostureChange();
        }
            
    }

private:

};
#endif // !POS_CHANGE_H

// Buzzer
#ifndef BUZZER_H
#define BUZZER_H

class Buzzer{
public:
    Buzzer();
    void alarm();
    void close();
    bool ring;
};

void Buzzer::alarm() {
    this->ring = true;
    close();
}

void Buzzer::close() {
    Timer timer(500);
    timer.countdown();
    this->ring = false;
}
#endif // !BUZZER_H

#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer(int n);
    void countdown();
    int count;
private:

};

Timer::Timer(int n)
{
    count = n;
}

void Timer::countdown()
{
    if (this->count != 0) {
        this->count--;
        if (count == 0)
            return;
    }

}

#endif // !TIMER_H

