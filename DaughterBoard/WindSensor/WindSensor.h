#include "../SharedInclude/serial_port.h"
#include "../SharedInclude/WindMsgQueue.h"
#include <string>
#include <sstream>
#include <iostream>


using namespace std;


class WindSensor{
	
public: 
	WindSensor();
	~WindSensor();
	void waitForConfig();
	void init();
	void sense();
	uint16_t getAngle();
	float getWindSpeed();
	float getTemperature();
	WindMsgQueue msgQueue;
	
private:
	Serial_Port* serial;
	uint8_t stype;
	uint16_t angle;
	float windSpeed, U, V, W, temperature;
	string buf;
	char byte;
	const char* port;
	int baudrate;
	void extractData();
	
};

WindSensor::WindSensor() {
}

WindSensor::~WindSensor() {
	delete serial;
}

void WindSensor::waitForConfig() {
	while( msgQueue.receiveConfig() != RCV_SUCCESS );
	stype = msgQueue.getSensorType();
}
	
void WindSensor::init() {
	switch( stype ) {
		case FT205 :
			port = "/dev/ttyUSB2";
			baudrate = 9600;
			break;
		case TRISONICA :
			port = "/dev/ttyUSB2";
			baudrate = 115200;
			break;
	}
	serial = new Serial_Port( port, baudrate, 1 );
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
	
	switch( stype ) {
		case FT205:
			while ( ss.good() )
			{
				count++;
				string substr;
				getline( ss, substr, ',' );
				if ( count == 2 ) {
					angle = (uint16_t)stoi( substr );
				}
				if( count == 4 ) {
					windSpeed = stof( substr );
				}
			}
			break;
		case TRISONICA:
			string tmp;
			ss >> windSpeed >> angle >> tmp >> tmp >> tmp >> temperature;
			break;
	}
	buf.clear();
}

uint16_t WindSensor::getAngle() {
	return angle;
}

float WindSensor::getWindSpeed() {
	return windSpeed;
}

float WindSensor::getTemperature() {
	return temperature;
}

