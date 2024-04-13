#include <iostream>
#include <pigpio.h>
#include <pthread.h>
#include <unistd.h>
#include "RTEP_Buzzer_class/Buzzer.h"
#include "RTEP_LCD_class/LCD.h"
#include "RTEP_MPU6050_class/mpu6050.h"
#include "RTEP_Pressure_class/Pressure.h"

using namespace std;

// 定义全局变量
float accelX_g, accelY_g, accelZ_g;
float gyroX_degPerSec, gyroY_degPerSec, gyroZ_degPerSec;
float pressure1, pressure2;

// 创建线程 用于读取MPU6050数据
void* thread_mpu6050(void* arg)
{
    MPU6050 mpu6050(1, 0x68);
    if (!mpu6050.initialize())
    {
        cout << "MPU6050 initialize failed" << endl;
        return NULL;
    }

    while (1)
    {
        // mpu6050.readAcceleration(accelX_g, accelY_g, accelZ_g);
        // mpu6050.readGyroscope(gyroX_degPerSec, gyroY_degPerSec, gyroZ_degPerSec);
        usleep(100000);
    }
    return NULL;
}

// 创建线程 用于读取压力传感器数据
void* thread_pressure(void* arg)
{
    //Pressure pressure1();
    //Pressure pressure2();
    if (!pressure1.initialize() || !pressure2.initialize())
    {
        cout << "Pressure initialize failed" << endl;
        return NULL;
    }

    while (1)
    {
       // pressure1.readPressure(pressure1);
       // pressure2.readPressure(pressure2);
        usleep(100000);
    }
    return NULL;
}

int main()
{
    // 初始化pigpio库
    if (gpioInitialise() < 0)
    {
        cout << "pigpio initial failed" << endl;
        return -1;
    }

    // 创建线程 用于读取MPU6050数据
    pthread_t tid_mpu6050;
    pthread_create(&tid_mpu6050, NULL, thread_mpu6050, NULL);

    // 创建线程 用于读取压力传感器数据
    pthread_t tid_pressure;
    pthread_create(&tid_pressure, NULL, thread_pressure, NULL);

    // 初始化LCD1602
    LCD1602 lcd(17, 18, 27, 22, 23, 24, 25, 4);
    lcd.initLCD();

    // 初始化蜂鸣器
    Buzzer buzzer(5);

    // 定义阈值
    float pressure_threshold = 0.5;
    float acc_threshold = 0.1;
    float gyro_threshold = 0.1;

    while (1)
    {
        // 判断用户是否跌倒在判断用户跌倒的情况下，输出模块会报警
        // 至少有一个压力数据超过闻值,至少两个方向的加速度数据超过阈值,表示用户跌倒
        if(pressure1 > pressure_threshold || pressure2 > pressure_threshold)
        {
            if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
            {
                buzzer.buzz_on();
                lcd.setCursor(0, 0);
                lcd.print("FALL DOWN");
            }
            else
            {
                buzzer.buzz_off();
                lcd.clearScreen();
            }
        }
        else
        {
            buzzer.buzz_off();
            lcd.clearScreen();
        }

        // 至少有一个压力数据超过闻值,至少两个方向的角速度数据产生80%以上的变化，包括但不限于波动、上升或下降
        if(pressure1 > pressure_threshold || pressure2 > pressure_threshold)
        {
            if((gyroX_degPerSec > gyro_threshold && gyroY_degPerSec > gyro_threshold) || (gyroY_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold) || (gyroX_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold))
            {
                buzzer.buzz_on();
                lcd.setCursor(0, 0);
                lcd.print("FALL DOWN");
            }
            else
            {
                buzzer.buzz_off();
                lcd.clearScreen();
            }
        }
        else
        {
            buzzer.buzz_off();
            lcd.clearScreen();
        }
        // 至少两个方向的加速度数据超过阔值,至少两个方向的角速度数据产生80%以上的变化，包括但不限于波动、上升或下降
        if((accelX_g > acc_threshold && accelY_g > acc_threshold) || (accelY_g > acc_threshold && accelZ_g > acc_threshold) || (accelX_g > acc_threshold && accelZ_g > acc_threshold))
        {
            if((gyroX_degPerSec > gyro_threshold && gyroY_degPerSec > gyro_threshold) || (gyroY_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold) || (gyroX_degPerSec > gyro_threshold && gyroZ_degPerSec > gyro_threshold))
            {
                buzzer.buzz_on();
                lcd.setCursor(0, 0);
                lcd.print("FALL DOWN");
            }
            else
            {
                buzzer.buzz_off();
                lcd.clearScreen();
            }
        }
        else
        {
            buzzer.buzz_off();
            lcd.clearScreen();
        }

        // 当加速度接近0时，两个压力传感器达到闻值，液晶屏出现站立。
        if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 > pressure_threshold && pressure2 > pressure_threshold)
        {
            lcd.setCursor(0, 0);
            lcd.print("STAND UP");
        }
         // 至少一个方向的加速度数据超过阈值;两个压力数据在1秒内变化超过阈值的40%，液晶屏出现行走。

        if((accelX_g > acc_threshold || accelY_g > acc_threshold || accelZ_g > acc_threshold) && (pressure1 > 0.4 * pressure_threshold && pressure2 > 0.4 * pressure_threshold))
        {
            // 1秒内变化超过阈值的40%
            usleep(1000000);
            if((pressure1 > 0.4 * pressure_threshold && pressure2 > 0.4 * pressure_threshold))
            {
                lcd.setCursor(0, 0);
                lcd.print("WALKING");
            }
        }
        // 当加速度接近 0 时，压力传感器小于，LCD 屏幕显示为坐下
        if(accelX_g < 0.01 && accelY_g < 0.01 && accelZ_g < 0.01 && pressure1 < pressure_threshold && pressure2 < pressure_threshold)
        {
            lcd.setCursor(0, 0);
            lcd.print("SIT DOWN");
        }

        usleep(100000);
        //1）鞋底压力降低，且至少小于体重的1/5; 2）在一定时间内，至少两个方向的角速度数据变化80%以上; 3）加速度数据小于阈值; 判定为躺下
        if((pressure1 < 0.2 * pressure_threshold && pressure2 < 0.2 * pressure_threshold) && ((gyroX_degPerSec > 0.8 * gyro_threshold && gyroY_degPerSec > 0.8 * gyro_threshold)||(gyroY_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)||(gyroX_degPerSec > 0.8 * gyro_threshold && gyroZ_degPerSec > 0.8 * gyro_threshold)) && (accelX_g < acc_threshold && accelY_g < acc_threshold && accelZ_g < acc_threshold))
        {
            lcd.setCursor(0, 0);
            lcd.print("LYING DOWN");
        }

        usleep(100000);
    }
}
