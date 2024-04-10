## Report


# Background

According to the World Health Organization (WHO), falling is one of the significant global public health concerns. It is estimated that around 646,000 fatal falls occur worldwide each year, making it the second leading cause of unintentional injury death. 

Furthermore, falls often lead to functional dependencies among the elderly population. The WHO Global Report on Falls Prevention in Older Age (2008) highlights that approximately 28–35% of individuals aged 65 and over experience falls each year, while this figure increases to 32–42% for those over 70 years of age. 

These situations arise the urgent need of effective fall prevention measures for the health of individuals, particularly the elderly.


# Introduction




# Components

The entire device comprises four modules: Monitoring, Transmission, Processing, and Output.

The pivotal module is the monitoring module, which equips with a six-axis sensor and a set of pressure sensors. The six-axis sensor operates as gyroscope and acceleration sensor, capturing data on angular velocity and acceleration, while the pressure sensors collect information on stress variations, during movements and directional changes.

The transmission module comprises a Bluetooth module to receive data from the monitoring module, passing it to the processing module in real time. The processing module undertakes the analysis of the wearers movement status after the data is in position, maintaining a continuous monitor for changes indicative of alterations in subject posture or potential falls.
If any such changes are detected during monitoring, the device promptly dispatches message to the output module, which autonomously allocates tasks to the display unit and alarm unit based on the received message. 

This coordination realizes the functionality of continuous posture changing detection and fall alarms.

![alt text](1.png)


# Structure

1. Monitoring Module:
(1) Six-Axis Sensor (MPU6050), positioned around the barycenter of the human body, the MPU6050 comprises:
Gyroscope: Monitors the body's angular velocity in the x, y, and z directions.
Acceleration Sensor: Tracks the body's acceleration in the x, y, and z directions.
output data including angular velocity and acceleration.
electrically connected to the transmission module, to transmit the angular velocity and acceleration data to the processing module in real time.
(2) Pressure Sensor, positioned at least on the soles of the human feet, the pressure sensor includes:
C25A: Outputs an analog signal representing pressure.
ADS1115: Analog-to-digital converter (ADC) that converts the analog signal to digital, producing a voltage proportional to the pressure.
The C25A is connected to ADS1115, while ADS1115 connected to the transmission module, to transmit the pressure data to the processing module in real time.

2. Transmission Module:
Communication Port
and/or
Communication Unit:
Bluetooth unit for receiving data sent by six-axis sensors and pressure sensors.

3. Processing Module:
Raspberry PI, electrically connected with transmission module, used to integrate data, transform data, and estimate according to data.
Integration: Stores collected data.
Conversion: Converts angular velocity data into degrees per second (deg/s), acceleration data into gravity (G), and pressure data into kilogram (kg).
Judgment: Based on the acquired angular velocity, acceleration, and pressure data, estimates the body's posture, including walking, standing, sitting, and lying states.

4. Output Module: electrical connected with the processing module, to respond on the command of the processing module.
(1) Display Unit:
Display the current human body posture.
(2) Alarm Unit:
Alarm when falling occurs.


# Internal Logic

1. Processing Steps
S1: receive the angular velocity and acceleration obtained by the six-axis sensor, and the pressure data obtained by the pressure sensor;
S2: pre-process, at least including conversion, the angular velocity, acceleration and pressure data;
S3: according to the angular velocity, acceleration and pressure data to judge the body posture;
S4: according to the human body posture, control the output module to respond.
![alt text](2.png)

2. Judgment Conditions
