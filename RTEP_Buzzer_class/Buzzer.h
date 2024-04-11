#ifndef Buzzer_h
#define Buzzer_h

class Buzzer {
private:
    int pin;
public:
    Buzzer(int pin);
    ~Buzzer();
    void buzz(int durationMicroseconds);
};

#endif