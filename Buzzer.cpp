#include <pigpio.h>
#include <unistd.h>
#define PIN 0

int main() {
    if (gpioInitialise() < 0) {
        // 初始化失败
        return 1;
    }

    //if (gpioInitialise() < 0) {
        // 初始化失败
       // return 1;
    //}

    gpioSetMode(PIN, PI_OUTPUT); // 设置GPIO引脚为输出模式

    for (;;) {
        gpioWrite(PIN, 0); // 设置GPIO引脚为低电平
        usleep(1000);      // 延迟1毫秒（1000微秒）
        gpioWrite(PIN, 1); // 设置GPIO引脚为高电平
        usleep(1000);      // 延迟1毫秒（1000微秒）
    }

    gpioTerminate(); // 清理pigpio库
    return 0;
}

