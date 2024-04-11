#ifndef Buzzer_h
#define Buzzer_h

class Buzzer {
public:
    Buzzer();
    void Buzzer_init();
    ~Buzzer();
    void Beep(int frequency, int duration);
};

#endif