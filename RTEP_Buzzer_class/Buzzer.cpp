#include <pigpio.h>
#include <unistd.h>
#define PIN 0



int main() {
    if (gpioInitialise() < 0) {
        // ��ʼ��ʧ��
        return 1;
    }

    gpioSetMode(PIN, PI_OUTPUT); // ����GPIO����Ϊ���ģʽ

    for (;;) {
        gpioWrite(PIN, 0); // ����GPIO����Ϊ�͵�ƽ
        usleep(1000);      // �ӳ�1���루1000΢�룩
        gpioWrite(PIN, 1); // ����GPIO����Ϊ�ߵ�ƽ
        usleep(1000);      // �ӳ�1���루1000΢�룩
    }

    gpioTerminate(); // ����pigpio��
    return 0;
}

class Buzzer {
private:
    int pin;

public:
    Buzzer(int pin) : pin(pin) {
        if (gpioInitialise() < 0) {
            throw std::runtime_error("GPIO initialization failed");
        }
        gpioSetMode(pin, PI_OUTPUT);
    }

    ~Buzzer() {
        gpioTerminate();
    }

    void buzz(int durationMicroseconds) {
        gpioWrite(pin, 0);
        usleep(durationMicroseconds);
        gpioWrite(pin, 1);
        usleep(durationMicroseconds);
    }
};

int main() {
    try {
        Buzzer buzzer(PIN);
        for (;;) {
            buzzer.buzz(1000);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

