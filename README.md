# Raspberry Pi Project: [My Step Monitor]
- Ins: https://www.instagram.com/mystepmonitor/
- Check _*Wiki page*_ for detailed description of the project!
  Link: [WikiPage](https://github.com/afkedhamster/My-Step-Monitor/wiki)
  
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
- Create the first version of the code for sensor data reading and processing _(Uploaded 14/04)_
  * Link: [Dev_Doc\Buzzer & Screen_20_02](https://github.com/afkedhamster/My-Step-Monitor/blob/master/Dev_Doc/Buzzer%20%26%20Screen_20_02) 

## Dev log 20/02/2024 
- Create the first version of the code about the response class, including the LCD and buzzer _(Uploaded 14/04)_
  * Link: [Dev_Doc\Buzzer & Screen_20_02](https://github.com/afkedhamster/My-Step-Monitor/blob/master/Dev_Doc/Buzzer%20%26%20Screen_20_02) 

## Dev log 25/02/2024
- Learn more about callback functions, threads, and more

## Dev log 01/03/2024
- Set up of Raspberry Pi, download librarirs

## Dev log 20/03/2024
 - Finish the code for Buzzer\
  Link: [RTEP_Buzzer_class\Buzzer.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Buzzer_class/Buzzer.cpp)
  - Buzzer can give sounds of different frequencies 
  - The buzzer serves well as one of the alarm units
- Test the readout of the Pressure Sensor\
  Link: [RTEP_MPU6050_class\Abandon\main.cpp](#main.cpp)
  - Correctly produced bool value based on the existence of the pressure
  - Cannot read the value of pressure due to lack of ADC
- Tesd the LCD12864 monitor module\
  Link: [RTEP_Lcd1602\lcd_test.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/lcd_test.cpp)
  - Constantly errors "implicit declaration of function ‘WriteCmd’"
  - haven't located the library file that contains "WriteCmd" function
 
## Dev log 21/03/2024
- Test the LCD12864 monitor module _(Code Abandoned)_
  - Reconfigure the Pin
  - Successfully initiated the LCD 12864 monitor
- Test the Pressure unit\
  Link: [RTEP_Pressure_class\Abandon\Pressure.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Abandon/Pressure.cpp)
- Preparation for Intranet Penetration using Tailscale **_(Hardware)_**
  - Setup Tailscale client on PC
 
## Dev log 23/03/2024
- Debug Lcd contorl class\
  Link: [RTEP_Lcd1602\LCD.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/LCD.cpp); [RTEP_Lcd1602\LCD.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/LCD.h)
  - Current code show partial success as it does display part of the intented text message, however the rest of the text message seems in wrong format

## Dev log 30/03/2024
- Add control class for the MPU6050 six-axis gryoscope module\
  Link: [RTEP_MPU6050_class\Abandon\6050.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/6050.cpp); [RTEP_MPU6050_class\Abandon\mpu6050.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/mpu6050.cpp)

## Dev log 05/04/2024 
- Test LCD 12864 module _(Code Abandoned)_

## Dev log 07/04/2024
- Add Function code for MPU6050\
  Link: [RTEP_MPU6050_class\Abandon\main.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/main.cpp)
- Add function code for Pressure unit\
  Link: [RTEP_Pressure_class\Abandon\adcPressure.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Abandon/adcPressure.cpp)

## Dev log 08/04/2024
- Add multiple control classes for MPU6050
  * I2C control class with WringPi _(Code Abandoned)_
  * GPIO simulate I2C\
    Link: [RTEP_MPU6050_class\Abandon\pigpio.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/pigpio.cpp)
- Override the function of MPU6050 with Pigpio.h\
  Link: [RTEP_MPU6050_class\Abandon\MPU6050_Pigpio.cpp](RTEP_MPU6050_class\Abandon\MPU6050_Pigpio.cpp)
- Test LCD1602\
  Link: [RTEP_Lcd1602\lcd_test.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/lcd_test.cpp); [RTEP_Lcd1602\LCD.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/LCD.cpp); [RTEP_Lcd1602\LCD.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/LCD.h)

## Dev log 09/04/2024
- Add test code for C25A and ADS1115 module\
  Link: [RTEP_Pressure_class\Abandon\adcPressure.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Abandon/adcPressure.cpp); 
- Add multiple control classes for C25A and ADS1115
  * I2C control class with WringPi _(Code Abandoned)_\
    Link: [RTEP_Pressure_class\Abandon\C25A_I2C.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Abandon/C25A_I2C.cpp)
  * I2C control class with Pigpio\
    Link: [RTEP_Pressure_class\Abandon\C25A_Pigpio.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Abandon/C25A_Pigpio.cpp)

## Dev log 10/04/2024
- Use pigpio.h library to replace wiringPi.h and wiringPiI2C.h\
  Link: [RTEP_Lcd1602\lcd_test.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/lcd_test.cpp); [RTEP_MPU6050_class\Abandon\mpu6050.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/mpu6050.cpp)
- Correct LCD1602\
  Link: [RTEP_MPU6050_class\Abandon\6050.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/6050.cpp)
- Add some test part for mpu6050\
  Link: [RTEP_MPU6050_class\Abandon\mpu6050.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/mpu6050.cpp);[RTEP_MPU6050_class\Abandon\6050.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/6050.cpp)
  
- Code ADS1115 and C25A
  Link: [RTEP_Pressure_class\ADS1115.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/ADS1115.h); [RTEP_Pressure_class\ADS1115.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/ADS1115.cpp)

## Dev log 11/04/2024
- Debug Buzzer and LCD1602\
  Link: [RTEP_Buzzer_class\Buzzer.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Buzzer_class/Buzzer.cpp); [RTEP_Buzzer_class\Buzzer.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Buzzer_class/Buzzer.h); [RTEP_Buzzer_class\Buzzer_test.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Buzzer_class/Buzzer_test.cpp)\
  [RTEP_Lcd1602\lcd_test.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/lcd_test.cpp); [RTEP_Lcd1602\LCD.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/LCD.cpp); [RTEP_Lcd1602\LCD.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/LCD.h)
  * Modify seperation class definition, clarification, and unit tests
  * Edit classes to implement function encapsulation
- Simplify the code structure of the project
  * Wrap C25A\
    From: [RTEP_Pressure_class\Abandon\C25A_Pigpio.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Abandon/C25A_Pigpio.cpp); [RTEP_Pressure_class\ADS1115.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/ADS1115.h); [RTEP_Pressure_class\ADS1115.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/ADS1115.cpp)\
    Link: [RTEP_Pressure_class\Wrapper\C25A_Wrapper.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Wrapper/C25A_Wrapper.cpp); [RTEP_Pressure_class\Wrapper\ADS1115_Wrapper.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Wrapper/ADS1115_Wrapper.h); [RTEP_Pressure_class\Wrapper\ADS1115_Wrapper.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Wrapper/ADS1115_Wrapper.cpp)
  * Wrap MPU6050\
    From: [RTEP_MPU6050_class\Abandon\MPU6050_Pigpio.cpp](RTEP_MPU6050_class\Abandon\MPU6050_Pigpio.cpp); \
    Link: [RTEP_MPU6050_class\Wrapper\MPU6050.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Wrapper/MPU6050.h); [RTEP_MPU6050_class\Wrapper\MPU6050_Wrapper.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Wrapper/MPU6050_Wrapper.h); [RTEP_MPU6050_class\Wrapper\MPU6050_Wrapper.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Wrapper/MPU6050_Wrapper.cpp); [RTEP_MPU6050_class\Wrapper\MPU6050_main.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Wrapper/MPU6050_main.cpp)
- Creat threads functions along with unit test\
  Link: [RTEP_MainFunc\Abandon\judgment.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/judgment.cpp); [RTEP_MainFunc\Abandon\Threads.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads.h); [RTEP_MainFunc\Abandon\Threads_1.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads_1.h); 
- Adding header files to several control classes
- All above dev are done in the *_MainProto2 branch_*
- Add condition judgment to the main function to implement functionality

## Dev log 12/04/2024
- master branch back to previous version
- Merged new features into *_master branch_*
- Debug MPU6050\
  From: [RTEP_MPU6050_class\MPU6050_test_main.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/MPU6050_test_main.cpp); [RTEP_MPU6050_class\MPU6050_test.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Mpu6050_test.cpp); [RTEP_MPU6050_class\Abandon\Mpu6050.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/Mpu6050.h)\
  Link: [RTEP_MPU6050_class\Abandon\Mpu6050_test.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/Mpu6050_test.cpp); [RTEP_MPU6050_class\Abandon\mpu6050.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Abandon/mpu6050.cpp); [RTEP_MPU6050_class\MPU6050_test.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/MPU6050_test.h); [RTEP_MPU6050_class\Mpu6050_test.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Mpu6050_test.cpp); [RTEP_MPU6050_class\MPU6050_test_main.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/MPU6050_test_main.cpp)
- Debug Wrapper C25A\
  Link: [RTEP_Pressure_class\Wrapper\C25A_Wrapper.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Wrapper/C25A_Wrapper.cpp); [RTEP_Pressure_class\Wrapper\ADS1115_Wrapper.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Wrapper/ADS1115_Wrapper.h); [RTEP_Pressure_class\Wrapper\ADS1115_Wrapper.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Wrapper/ADS1115_Wrapper.cpp)
- (Important)Adding "mpu6050_commu": "c" at line 52- 54 in settings.json
  Link: [.vscode\settings.json](https://github.com/afkedhamster/My-Step-Monitor/blob/master/.vscode/settings.json)
- Implement the testing of pressure-sensitive sensors and digital-to-analog conversion modules (ads1115)
- Code Threads functions
  Link: [RTEP_MainFunc\Abandon\judgment.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/judgment.cpp); [RTEP_MainFunc\Abandon\Threads.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads.h); [RTEP_MainFunc\Abandon\Threads_1.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads_1.h); 
- Reunit Threads functions \
  Resource: [RTEP_MainFunc\Abandon\Threads.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads.h); [RTEP_MainFunc\Abandon\Threads_1.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads_1.h); 
  Link: [RTEP_MainFunc\Abandon\Threads_Response.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads_Response.cpp); [RTEP_MainFunc\Abandon\Threads_read_detect.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads_read_detect.cpp)
- Wrap buzzer for Threads
  Link: [RTEP_MainFunc\Abandon\thread_buzzer.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/thread_buzzer.h)

## Dev log 13/04/2024
- Correct ads1115 (adc module) and C25A pressure sensor, and complete unit testing; Realize the packaging of ads1115 (adc module) and C25A pressure sensor unit
  From: [RTEP_Pressure_class\Wrapper\C25A_Wrapper.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Abandon/C25A_Pigpio.cpp)\
  Link: [RTEP_Pressure_class\C25A_ADS1115_Pressure_test.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/C25A_ADS1115_Pressure_test.cpp); 
- Add the Abandon folder and organize the test units before ads1115 and MPU6050\
  Link: [RTEP_Pressure_class\Abandon](https://github.com/afkedhamster/My-Step-Monitor/tree/master/RTEP_Pressure_class/Abandon); [RTEP_MPU6050_class\Abandon](https://github.com/afkedhamster/My-Step-Monitor/tree/master/RTEP_MPU6050_class/Abandon);
  [RTEP_Commu\Abandon](https://github.com/afkedhamster/My-Step-Monitor/tree/master/RTEP_Commu/Abandon);
- Few refactor within 'Threads.h' & 'Threads.cpp'\
  Link: [RTEP_MainFunc\Abandon\Threads.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads.h); [RTEP_MainFunc\Abandon\Threads_Response.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads_Response.cpp)
- Becauese of the shortage of the IO pin, we have to add a 'mockLCD' in the LCD class in order to bypass the need for real LCD to use the mockLCD, simply use 'LCD lcd('l', 0, true);' instead of 'LCD lcd;'\
  Link: [RTEP_Lcd1602\lcd_test.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/lcd_test.cpp); [RTEP_Lcd1602\LCD.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/LCD.cpp); [RTEP_Lcd1602\LCD.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Lcd1602/LCD.h)
- Code communication of IPC\
  Link: [RTEP_Commu\IPC.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Commu/IPC.h); [RTEP_Commu\IPC.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Commu/IPC.cpp); [RTEP_Commu\MPU6050_Commu.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Commu/MPU6050_Commu.cpp);[RTEP_Commu\C25A_Commu.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Commu/C25A_Commu.cpp)
  * Wrapper IPC
  * Add communication function to MPU6050 and C25A
- Complete and modify judgment threads, create variables to detect prevous posture compare with current posture to monitor dynamic movement
- Debug Judgment\
  Link: [RTEP_MainFunc\Abandon\Threads_read_detect.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads_read_detect.cpp)

## Dev log 14/04/2024

- Adjust code to fit 

  Link: [RTEP_MPU6050_class\MPU6050_test.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/MPU6050_test.h); [RTEP_MPU6050_class\Mpu6050_test.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/Mpu6050_test.cpp); [RTEP_MPU6050_class\MPU6050_test_main.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MPU6050_class/MPU6050_test_main.cpp); \
  [RTEP_Pressure_class\Wrapper\C25A_Wrapper.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Wrapper/C25A_Wrapper.cpp); [RTEP_Pressure_class\Wrapper\ADS1115_Wrapper.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Wrapper/ADS1115_Wrapper.h); [RTEP_Pressure_class\Wrapper\ADS1115_Wrapper.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Pressure_class/Wrapper/ADS1115_Wrapper.cpp)
- Debug IPC
  * Add code for different data type
  * Implement IPC with MPU6050 and ADS1115
  Link: [RTEP_Commu\IPC.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Commu/IPC.h); [RTEP_Commu\IPC.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Commu/IPC.cpp); [RTEP_Commu\MPU6050_Commu.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Commu/MPU6050_Commu.cpp);[RTEP_Commu\C25A_Commu.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_Commu/C25A_Commu.cpp)
- Create Judgment Function\
  Resource: [RTEP_MainFunc\Abandon\Threads_read_detect.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads_read_detect.cpp); \

  Link: [RTEP_MainFunc\Judgment.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Judgment.h); [RTEP_MainFunc\Judgment.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Judgment.cpp)
  * Reconstruct
  * Add IPC
- Reconstruct Response Function\

  Resource: [RTEP_MainFunc\Abandon\Threads_Response.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Abandon/Threads_Response.cpp)
  Link: [RTEP_MainFunc\Response.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Response.h); [RTEP_MainFunc\Response.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Response.cpp)
  * Reconstruct
  * Add IPC
- Main Function\
  Link: [RTEP_MainFunc\Main.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Main.cpp)
- Add Abandon folder and organize the test units\
  Link: [RTEP_MainFunc\Abandon](https://github.com/afkedhamster/My-Step-Monitor/tree/master/RTEP_MainFunc/Abandon)
- Creat *_Num branch_* to avoid the issues of different data type involving IPC

## Dev log 15/04/2024
- Debug Judgment Function, Response Function, and Main Function.\
  Link: [RTEP_MainFunc\Judgment.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Judgment.h); [RTEP_MainFunc\Judgment.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Judgment.cpp); \
  [RTEP_MainFunc\Response.h](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Response.h); [RTEP_MainFunc\Response.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Response.cpp); \
  [RTEP_MainFunc\Main.cpp](https://github.com/afkedhamster/My-Step-Monitor/blob/master/RTEP_MainFunc/Main.cpp)
- Implement with Hardware
- Merge with _*master branch*_
- Finish Wiki Page\
  Link: [WikiPage](https://github.com/afkedhamster/My-Step-Monitor/wiki)



# Team 6 Member Labour Division

## Zhiyue Lu (2931528L)

## Jiahui Tang (2855848T)

## Jiewen Tan (2934324T) 
Github Link: [Afked Hamster](https://github.com/afkedhamster)
- One of the testors of the devices
- Control class for buzzer
- Control class for LCD 12864
- Threads_Response definition & declaration
- Fundamental main function
- Global debug
- Github Management & Pull Request handling
- Early Dev log & Wiki

## Shuaifei Wang (2936142W) 
Github Link: [ShuaifeiWang5173](https://github.com/ShuaifeiWang5173?tab=overview&from=2024-03-01&to=2024-03-31)
- Code and debug MPU6050 and C25A & ADS1115
- Code and debug communication function of IPC
- Code main function and settle Judgmen and Response 
- Part of the report
