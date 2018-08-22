#!/bin/bash

apt update
# apt install cmake
## Library needed to handle GPIO I2C for Lidar sensor. This project is using the version 1.56. Visit this website to get the latest version: http://www.airspayce.com/mikem/bcm2835/
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.56.tar.gz
tar zxvf bcm2835-1.56.tar.gz
cd bcm2835-1.56
./configure
make
make check
make install
cd ..
## Build the project executables
mkdir bin
cd Handler/
g++ -std=c++11 -o ../bin/main_Handler main_Handler.cpp -lpthread
cd ../Lidar
g++ -std=c++11 -o ../bin/main_Lidar main_Lidar.cpp -lbcm2835
cd ../Pyranometer
g++ -std=c++11 -o ../bin/main_Pyranometer main_Pyranometer.cpp
cd ../WindSensor
g++ -std=c++11 -o ../bin/main_WindSensor main_WindSensor.cpp
cd ../OPLS
g++ -std=c++11 -o ../bin/main_OPLS main_OPLS.cpp -lpthread
cd ..
chmod +x bin/*
## Apply a patch to the kernel in order to use an older driver for i2c communication. This is required for the Lidar Garmin Lite v3  to work properly.
echo "# Patch to use previous i2c driver" >> /boot/config.txt
echo "dtoverlay=i2c_bcm2708" >> /boot/config.txt

## Enables uart on GPIO pins 8 and 10
echo "# Enables uart on GPIO pins 8 and 10" >> /boot/config.txt
echo "enable_uart=1" >> /boot/config.txt
