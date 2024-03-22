# Raspberry Pi Project: [My Step Monitor]

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
  - Setup Tailscale client on PC of Jiewen Tan
