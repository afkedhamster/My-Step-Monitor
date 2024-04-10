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
  - [Other specific tools or libraries for your project]
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

## Dev log 10/04/2024
- use pigpio.h library to replace wiringPi.h and wiringPiI2C.h