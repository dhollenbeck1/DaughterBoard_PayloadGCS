#!/bin/bash


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

