# Raspberry Pi Project: [My Step Monitor]
- Ins: https://www.instagram.com/mystepmonitor/
- Check Wiki page for detailed description of the project!
  
## Priliminary RPi & Environment Setup

### Hardware Setup
- Acquired a Raspberry Pi 3B+ board
- Prepared the necessary peripherals:
  - HDMI display
  - USB keyboard and mouse
  - Power supply
  - micro SD card with installed Raspbian OS (bookworm)

### Software Setup
- Installed the latest version of Raspbian OS (bookworm)
- Performed initial setup and configuration:
  - Set up language, time zone, and keyboard layout
 
## Additional Environmetal Configuration

### RPi Settings
-  Configured network settings (Wi-Fi or Ethernet)
  - Updated the system packages to the latest versions
- Enabled SSH and VNC for remote access

### Development Environment
- Installed required development tools and libraries:
  - Python 3.x
  - Git
  - Pigpio.h library
- Configured the development environment:
  - Set up a virtual environment for the project
  - Installed project dependencies using pip
- Cloned the project repository from GitHub

### Testing and Verification
- Ran initial tests to ensure the hardware and software setup is functioning correctly
- Verified connectivity and communication with external devices or services
- Conducted basic functionality tests for the project's core features

With the project setup and environment configuration complete, the Raspberry Pi 3B+ is now ready for further development and implementation of the project's specific features and functionalities.


## Dev log 17/01/2024
- Discuss the idea and the prototype of the project

## Dev log 18/01/2024
- Discuss the models of sensors that need to be purchased and how they collect human body data, and discuss their effectiveness

## Dev log 22/01/2024
- Draw the structure of the system and each module, and clearly write out the functions and connection methods of each module，including monitoring, transmission, processing, output modules

## Dev log 26/01/2024
- Clearly draw a flow chart of the posture judgment process and preliminarily define the preset conditions for each pose

## Dev log 31/03/2024
- Pitch Session

## Dev log 08/02/2024
- Discuss sequence and various subclasses of the program and the general structure of the program

## Dev log 15/02/2024
- Create the first version of the code for sensor data reading and processing
  * link: [MPU & Pressure-15-02-2024](#Dev_Doc-MPU-Pressure-15-02-2024) (Uploaded 14/04)

## Dev log 20/02/2024 
- Create the first version of the code about the response class, including the LCD and buzzer
  * link: [Buzzer & Screen-20-02-2024](#Dev-Doc-Buzzer-Screen-20-02-2024) (Uploaded 14/04)

## Dev log 25/02/2024
- Learn more about callback functions, threads, and more

## Dev log 01/03/2024
- Set up of Raspberry Pi, download librarirs

## Dev log 20/03/2024
 - Finish the code for Buzzer
   link: [RTEP_Buzzer_class\Buzzer.cpp](#Buzzer.cpp)
  - Buzzer can give sounds of different frequencies 
  - The buzzer serves well as one of the alarm units
- Test the readout of the Pressure Sensor
  link: [RTEP_MPU6050_class\Abandon\main.cpp](#main.cpp)
  - Correctly produced bool value based on the existence of the pressure
  - Cannot read the value of pressure due to lack of ADC
- Tesd the LCD12864 monitor module
  link: [RTEP_Lcd1602\lcd_test.cpp](#lcd_test.cpp)
  - Constantly errors "implicit declaration of function ‘WriteCmd’"
  - haven't located the library file that contains "WriteCmd" function
 
## Dev log 21/03/2024
- Test the LCD12864 monitor module _(Code Abandoned)_
  - Reconfigure the Pin
  - Successfully initiated the LCD 12864 monitor
- Preparation for Intranet Penetration using Tailscale **_(Hardware)_**
  - Setup Tailscale client on PC
 
## Dev log 23/03/2024
- Debug Lcd contorl class
  link: [RTEP_Lcd1602\LCD.cpp](#LCD.cpp); [RTEP_Lcd1602\LCD.h](#LCD.h)
  - Current code show partial success as it does display part of the intented text message, however the rest of the text message seems in wrong format

## Dev log 30/03/2024
- Add control class for the MPU6050 six-axis gryoscope module 

## Dev log 05/04/2024 _(Code Abandoned)_
- Add test code for LCD 12864 module 

## Dev log 08/04/2024
- Add multiple control classes for MPU6050
  I2C control class with WringPi _(Code Abandoned)_
  GPIO simulate I2C _(Code Abandoned)_
- Override the function of MPU6050 with Pigpio.h
  link: [RTEP_MPU6050_class\Abandon\MPU6050_Pigpio.cpp](#MPU6050_Pigpio.cpp)

## Dev log 09/04/2024
- Add test code for C25A and ADS1115 module _(Code Abandoned)_
  link: [RTEP_Pressure_class\Abandon\adcPressure.cpp](#adcPressure.cpp); [RTEP_Pressure_class\Abandon\adcPressure.cpp](#adcPressure.cpp)
- Add multiple control classes for C25A and ADS1115
  I2C control class with WringPi _(Code Abandoned)_
  link: [RTEP_Pressure_class\Abandon\C25A_I2C.cpp](#C25A_I2C.cpp)
- I2C control class with Pigpio
  link: [RTEP_Pressure_class\Abandon\C25A_Pigpio.cpp](#C25A_Pigpio.cpp)

## Dev log 10/04/2024
- Use pigpio.h library to replace wiringPi.h and wiringPiI2C.h
  link: [RTEP_Lcd1602\lcd_test.cpp](#lcd_test.cpp)
- Correct LCD1602
- Add some test part for mpu6050

## Dev log 11/04/2024
- Modify the code of Buzzer and LCD1602, seperation class definition, clarification, and unit tests
  Link: [RTEP_Buzzer_class\Buzzer_test.cpp](#Buzzer_test.cpp); [RTEP_Buzzer_class\Buzzer.h](#Buzzer.h)
- Edit the Buzzer and LCD1602 into classes to implement function encapsulation
- Simplify the code structure of the project
- Creat threads functions along with unit test
- Adding header files to several control classes
- All above dev are done in the MainProto2 branch
- Add condition judgment to the main function to implement functionality

## Dev log 12/04/2024
- master branch back to previous version
- Merged new features into master branch
- (Important)Adding "mpu6050_commu": "c" at line 52- 54 in settings.json 
- Implement the testing of pressure-sensitive sensors and digital-to-analog conversion modules (ads1115)

## Dev log 13/04/2024
- Correct ads1115 (adc module) and C25A pressure sensor, and complete unit testing
- Realize the packaging of ads1115 (adc module) and C25A pressure sensor unit
- Add the Abandon folder and organize the test units before ads1115
- Few refactor within 'Threads.h' & 'Threads.cpp'
- Becauese of the shortage of the IO pin, we have to add a 'mockLCD' in the LCD class in order to bypass the need for real LCD to use the mockLCD, simply use 'LCD lcd('l', 0, true);' instead of 'LCD lcd;'
- Create a new Abandon folders to manage temporarily unnecessary files
- Test the communication of mpu pipeline
- Complete and modify judgment threads, create variables to detect prevous posture compare with current posture to monitor dynamic movement
