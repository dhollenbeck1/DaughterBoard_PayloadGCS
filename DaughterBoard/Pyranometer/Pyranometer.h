#include "../SharedInclude/serial_port.h"
#include "../SharedInclude/PyranometerMsgQueue.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

//Pyranometer SP-212 from apogee Instruments

class Pyranometer{
	
public:
	const char* port   = "/dev/ttyS0";
	const int baudRate = 9600;
	
	Pyranometer();
	~Pyranometer();
	void waitForConfig();
	void sense();
	void extractData();
	uint32_t getSolarIrradiance();
	PyranometerMsgQueue msgQueue;

	
private:
	Serial_Port* serial;
	uint32_t solarIrradiance;
	string buf;
	char byte;	
};

Pyranometer::Pyranometer() {
	serial = new Serial_Port( port, baudRate, 1 );
	serial->start();
}

Pyranometer::~Pyranometer() {
	delete serial;
}

void Pyranometer::waitForConfig() {
	while( msgQueue.receiveConfig() != RCV_SUCCESS );
}

void Pyranometer::sense() {
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

void Pyranometer::extractData() {
	solarIrradiance = (uint32_t)stoi( buf );
	buf.clear();
}

uint32_t Pyranometer::getSolarIrradiance() {
	return solarIrradiance;
}
