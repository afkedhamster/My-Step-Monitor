#include <pigpio.h>
#include <unistd.h>
#define PIN 0

int main() {
    if (gpioInitialise() < 0) {
        // ��ʼ��ʧ��
        return 1;
    }

    //if (gpioInitialise() < 0) {
        // ��ʼ��ʧ��
       // return 1;
    //}

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

