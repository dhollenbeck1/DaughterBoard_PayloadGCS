# DaughterBoard_PayloadGCS

## DaughterBoard
To be compiled with geany IDE on raspberry PI.
This program takes in sensor data from USB, I2C,PWM, and converts them into Mavlink Messages. They are then sent to the QtPayloadGCS via XBee communication. Sensors currently implemented:
- (Wind+) Trisonica Mini Tactical Weather Station
- (Wind) FT-Technologies FT742-SM
- (Wind) FT-Technologies FT205
- (Pyranometer) Apogee
- (Methane/Ethane*) JPL
- (Lidar) Garmin Lidar Lite v3

* In Progress
+ Has other sensing capabilities

## QtPayloadGCS
Qt Project

Reads in Mavlink data from the XBee communication and plots/saves the data for user feedback/post-processing.
