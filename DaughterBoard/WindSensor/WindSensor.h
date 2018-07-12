#include "../SharedInclude/serial_port.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class WindSensor{
	
public:
	const char* port   = "/dev/ttyUSB0";
	const int baudRate = 9600;
	
	WindSensor();
	~WindSensor();
	void init();
	void sense();
	uint16_t getAngle();
	float getWindSpeed();
	
private:
	Serial_Port* serial;
	uint16_t angle;
	float windSpeed;
	string buf;
	char byte;
	void extractData();
	
};

WindSensor::WindSensor() {
	serial = new Serial_Port( port, baudRate );
}

WindSensor::~WindSensor() {
	delete serial;
}

void WindSensor::init() {
	serial->start();
}

void WindSensor::sense() {
	byte = '\0';
	while( byte != '\r' ) {
		if( serial->read_port( &byte ) != 1 ) {
			cout << "Error reading from windSensor port " << port << endl;
		}
		buf += byte;	
	}				
	byte = '\0';
	extractData();	
}

void WindSensor::extractData() {
	stringstream ss(buf);
	int count = 0;
	
    while ( ss.good() )
    {
		count++;
		string substr;
		getline( ss, substr, ',' );
		if( count == 2 ) {
			angle = (uint16_t)stoi( substr );
		}

		if( count == 4 ) {
			windSpeed = stof( substr );
		}
	}
	buf.clear();
}

uint16_t WindSensor::getAngle() {
	return angle;
}

float WindSensor::getWindSpeed() {
	return windSpeed;
}
