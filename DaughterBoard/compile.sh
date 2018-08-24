#!/bin/bash

## Build the project executables
echo "Creating executables"
echo "Entering Handler folder..."
cd Handler/
echo "Compiling main_Handler.cpp..."
g++ -std=c++11 -o ../bin/main_Handler main_Handler.cpp -lpthread
echo "Entering Lidar folder..."
cd ../Lidar
echo "Compiling main_Lidar.cpp..."
g++ -std=c++11 -o ../bin/main_Lidar main_Lidar.cpp -lbcm2835
echo "Entering Pyranometer folder..."
cd ../Pyranometer
echo "Compiling main_Pyranometer.cpp..."
g++ -std=c++11 -o ../bin/main_Pyranometer main_Pyranometer.cpp
echo "Entering WindSensor folder..."
cd ../WindSensor
echo "Compiling main_WindSensor.cpp..."
g++ -std=c++11 -o ../bin/main_WindSensor main_WindSensor.cpp
echo "Entering OPLS folder..."
cd ../OPLS
echo "Compiling main_OPLS.cpp..."
g++ -std=c++11 -o ../bin/main_OPLS main_OPLS.cpp -lpthread
cd ..
chmod +x bin/*
