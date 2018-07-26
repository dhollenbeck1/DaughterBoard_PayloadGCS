#!/bin/bash

ipcrm --all=msg
cd /home/pi/projects/DaughterBoard/Handler
./main_Handler&
cd ../Lidar
sudo ./main_Lidar&
cd ../Pyranometer
./main_Pyranometer&
cd ../WindSensor
./main_WindSensor&
cd ../OPLS
./main_OPLS&

