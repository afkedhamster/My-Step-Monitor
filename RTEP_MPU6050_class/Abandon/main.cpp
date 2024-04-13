#include <iostream>
#include <wiringPi.h>
#include <MPU6050.h>
#include <chrono>
#include <thread>

// Define the threshold values for acceleration and angular rate
const float ACCELERATION_THRESHOLD = 2.0; // m/s^2
const float ANGULAR_RATE_THRESHOLD = 5.0; // degrees/s
const float PRESSURE_MIN_VALUE = 0.5; // arbitrary unit
const float PRESSURE_20_PERCENT = 0.2 * USER_WEIGHT; // 20% of user's weight

// Variables to track pressure fluctuation
float lastPressure = 0;
float pressureChangeTime = 0;

int main() {
    // Initialize MPU6050 sensor
    MPU6050 mpu;
    mpu.initialize();

    // Main loop
    while (true) {
        // Read accelerometer, gyroscope, and pressure sensor data
        Vector3f acceleration = mpu.getAcceleration();
        Vector3f angularRate = mpu.getAngularRate();
        float pressure = pressureSensor.getPressure();
        
        // Check if acceleration and angular rate exceed the threshold
        bool accelerationExceeds = acceleration.norm() > ACCELERATION_THRESHOLD;
        bool angularRateExceeds = angularRate.norm() > ANGULAR_RATE_THRESHOLD;

        // Check if pressure sensor data is less than the minimum value
        bool pressureLow = pressure < PRESSURE_MIN_VALUE;

        // Check if acceleration is close to 0 and pressure is 20% of user's weight
        bool sitting = abs(acceleration.norm()) < 0.1 && abs(pressure - PRESSURE_20_PERCENT) < 0.1 * PRESSURE_20_PERCENT;

        // Check if pressure sensor value fluctuates between high and low for more than 1 second
        bool walking = false;
        if (abs(pressure - lastPressure) > 0.1 * PRESSURE_20_PERCENT) {
            pressureChangeTime = millis();
        } else if (millis() - pressureChangeTime > 1000) {
            walking = true;
        }
        lastPressure = pressure;
    }

        // Send appropriate message to LCD screen based on the conditions
        if (accelerationExceeds && angularRateExceeds && pressureLow) {
            lcdPosition(lcd, 0, 0);
            lcdPuts(lcd, "Falling Detected");
        } else if (sitting) {
            lcdPosition(lcd, 0, 0);
            lcdPuts(lcd, "Sitting Detected");
        } else if (walking) {
            lcdPosition(lcd, 0, 0);
            lcdPuts(lcd, "Walking Detected");
        } else {
            lcdClear(lcd);
        }
    
        // Delay for a short period of time
        std::this_thread::sleep_for(std::chrono::seconds(1));
}