#include "../SharedInclude/serial_port.h"
#include "../SharedInclude/constants.h"
#include "../SharedInclude/OPLSMsgQueue.h"
#include <string>
#include <sstream>
#include <queue>
#include <iostream>
#include <mutex>

using namespace std;

class OPLS{
	
public:
	const char* port   = "/dev/ttyUSB1";
	const int baudRate = 38400;
	
	OPLS();
	~OPLS();
	void waitForConfig();
	void serialData();
	bool parseData();
	oplsData getData();
	OPLSMsgQueue msgQueue;
	
private:
	Serial_Port* serial;
	//uint32_t solarIrradiance;
	char buf[ 32 ];
	queue<char*> fifo;
	char byte;	
	// OPLS data structure
	oplsData data;
};

OPLS::OPLS() {
	serial = new Serial_Port( port, baudRate, 0 );
	serial->start();
}

OPLS::~OPLS() {
	delete serial;
}

void OPLS::waitForConfig() {
	while( msgQueue.receiveConfig() != RCV_SUCCESS );
}

void OPLS::serialData() {
	mutex lockFifo;
	while( 1 ) {
		int count = 0;
		byte = '\0';
		while( byte != 0xAB ) {
			serial->read_port( &byte ); 
		}
		while( count < 32 ) {
			serial->read_port( &byte );
			buf[ count ] = byte;
			count++;
		}
		lockFifo.lock();
		fifo.push( buf );
		lockFifo.unlock();
	}
}

bool OPLS::parseData() {
	mutex lockFifo;
	usleep( 50000 );
	if( !fifo.empty() ) {
		lockFifo.lock();
		char *buf = fifo.front();
		fifo.pop();
		lockFifo.unlock();
		// Bytes 2-5 (Time)
		//-----------------------------------
		uint32_t tim = ((buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | (buf[3] << 0));
		data.time_ = ((double)tim)/10.0;
		
		
		// Bytes 6-9 (CH4)
		//-----------------------------------
		uint32_t ch4s = ((buf[4] << 24) | (buf[5] << 16) | (buf[6] << 8) | (buf[7] << 0));
		data.ch4 = ((double)ch4s)*1E-9;
		
		
		// Bytes 10-13 (Et)
		//-----------------------------------
		uint32_t ets = ((buf[8] << 24) | (buf[9] << 16) | (buf[10] << 8) | (buf[11] << 0));
		data.et = ((double)ets)*1E-9;
		
		
		// Bytes 14-15 (h2o)
		//-----------------------------------
		uint16_t h2os = ((buf[12] << 8) | buf[13]);
		data.h2o  = (double)h2os;
		
		
		// Bytes 16-17 (pressure)
		//-----------------------------------
		uint16_t ps   = ((buf[14] << 8) | buf[15]);
		data.p    = ((double)ps)*0.1;
		
		
		// Bytes 18-19 (temp)
		//-----------------------------------
		uint16_t ts   = ((buf[16] << 8) | buf[17]);
		data.t    = ((double)ts)*0.1;
		
		
		// Bytes 20-21 (Rangefinder)
		//-----------------------------------
		uint16_t rfs = ((buf[18] << 8) | buf[19]);
		data.rf  = (double)rfs;
		
		
		// Bytes 22-25 (longitude)
		//-----------------------------------
		uint32_t lons = ((buf[20] << 24) | (buf[21] << 16) | (buf[22] << 8) | (buf[23] << 0));
		data.lon  = ((double)lons)*1E-6;
	
	
		// Bytes 26-29 (latitude)
		//-----------------------------------
		uint32_t lats = ((buf[24] << 24) | (buf[25] << 16) | (buf[26] << 8) | (buf[27] << 0));
		data.lat = ((double)lats)*1E-6;
	
	
		// Bytes 30-31 (Laser power)
		//-----------------------------------
		uint16_t lsrs = ((buf[28] << 8) | buf[29]);
		data.lsr  = (double)lsrs;
		
		cout << data.time_ << " " << data.ch4 << endl;
		return true;
	}
	return false;
}	
	
oplsData OPLS::getData() {
	return data;
}
