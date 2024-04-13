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

## Dev log 20/03/2024
- Finished the code for Buzzer
  - Buzzer can give sounds of different frequencies
  - The buzzer serves well as one of the alarm units
- Testing the readout of the Pressure Sensor
  - Correctly produced bool value based on the existence of the pressure
  - Cannot read the value of pressure due to lack of ADC
- Tested the LCD12864 monitor module
  - Constantly errors "implicit declaration of function ‘WriteCmd’"
  - haven't located the library file that contains "WriteCmd" function
 
## Dev log 21/03/2024
- Tested the LCD12864 monitor module
  - Reconfigure the Pin
  - Successfully initiated the LCD 12864 monitor
- Preparation for Intranet Penetration using Tailscale
  - Setup Tailscale client on PC of Jiewen Tan and Zhiyue Lu
 
## Dev log 23/03/2024
- Debuging Lcd contorl class
  - Current code show partial success as it does display part of the intented text message, however the rest of the text message seems in wrong format

## Dev log 30/03/2024
- Add control class for the MPU6050 six-axis gryoscope module

## Dev log 05/04/2024
- Add test code for LCD 12864 module 

## Dev log 08/04/2024
- Added multiple control classes (based on different languages and header files) for MPU6050
- Override the function of MPU6050 with Pigpio.h

## Dev log 09/04/2024
- Added multiple control classes (based on different languages and header files) for C25A

## Dev log 10/04/2024
- Use pigpio.h library to replace wiringPi.h and wiringPiI2C.h
- Correct LCD1602, add some test part for mpu6050

## Dev log 11/04/2024
- Modify the code of Buzzer and LCD1602, seperation class definition, clarification, and unit tests
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
- Add the abandon folder and organize the test units before ads1115
- Few refactor within 'Threads.h' & 'Threads.cpp'
- Becauese of the shortage of the IO pin, we have to add a 'mockLCD' in the LCD class in order to bypass the need for real LCD to use the mockLCD, simply use 'LCD lcd('l', 0, true);' instead of 'LCD lcd;'
