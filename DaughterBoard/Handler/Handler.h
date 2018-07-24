#include <string>
#include <iostream>
#include <sstream>
#include <list>  
#include <mutex>  
#include "../SharedInclude/MAVLinkSerial_port.h"
#include "../SharedInclude/LidarMsgQueue.h"
#include "../SharedInclude/WindMsgQueue.h"
#include "../SharedInclude/PyranometerMsgQueue.h"


#define DEBUG

using namespace std;


enum MAVmsgType { wind, lidar, pyranometer }; 

class Handler{
	
public:
	const char* XBeePort = "/dev/ttyUSB0";
	const int baudRate   = 57600;
	const int DAUGHTER_BOARD_SYSID = 32;
//#define SENSOR_OK             0
//#define SENSOR_NOT_RESPONDING 0xFF
	
	Handler();
	~Handler();
	void handle();
	void waitForConfig();
		void heartBeat();   		 

private:	
	LidarMsgQueue lidarMsgQueue;
	WindMsgQueue windMsgQueue;
	PyranometerMsgQueue pyranometerMsgQueue;

	MAVmsgType msgType;  			 // Adding more sensors
	void receiveMsgQueue();
	void buildMAVMsg();              
	void sendMAVMsg();	
	void sendConfigToSensors(); 

	std::mutex serialLock;
	MAVLinkSerial_Port* MAVSerial;
	mavlink_message_t heartBeatMsg, configMsg, windMsg, lidarMsg, pyranometerMsg;
	mavlink_config_t cfg;
	bool windBuild, lidarBuild, pyranometerBuild, windSend, lidarSend, pyranometerSend;
	uint16_t angle;
	float windSpeed;
	float temperature;
	uint16_t distance;
	uint32_t solarIrradiance;
	uint8_t status;
	
};


Handler::Handler() {
	MAVSerial = new MAVLinkSerial_Port( XBeePort, baudRate );
	MAVSerial->start();
	windBuild        = false;
	lidarBuild       = false;
	pyranometerBuild = false;
	windSend         = false;
	lidarSend        = false;
	pyranometerSend  = false;
}

Handler::~Handler() {
	MAVSerial->close_serial();
	delete MAVSerial;
}

void Handler::waitForConfig() {
	while( 1 ) {
		if( MAVSerial->read_message( &configMsg ) ) {
			if( configMsg.msgid == MAVLINK_MSG_ID_CONFIG ) {
				mavlink_msg_config_decode( &configMsg, &cfg );
				sendConfigToSensors();
				return;
			}
		}
	}
}	

void Handler::handle() {
	receiveMsgQueue();
	if( lidarBuild || windBuild || pyranometerBuild ) {
		buildMAVMsg();
	}
	if( lidarSend || windSend || pyranometerSend ) {
		sendMAVMsg();
	}
}


void Handler::buildMAVMsg() {
	// Wind Sensor
	if( windBuild ) {
		cout << "Wind : " << angle << " " << windSpeed << " " << temperature << endl;
		mavlink_msg_wind_sensor_pack( DAUGHTER_BOARD_SYSID, 1, &windMsg, angle, windSpeed, temperature, 0 ); 
		windSend = true;
		windBuild = false;
	}else {
		windSend = false;
	}
	// Lidar
	if( lidarBuild ) {
		cout << "Lidar : " << distance << endl;
		mavlink_msg_lidar_pack( DAUGHTER_BOARD_SYSID, 1, &lidarMsg, distance, 0 ); 
		lidarSend = true;
		lidarBuild = false;
	}else {
		lidarSend = false;
	}
	// Pyranometer
	if( pyranometerBuild ) {
		cout << "Pyranometer : " << solarIrradiance << endl;
		mavlink_msg_pyranometer_pack( DAUGHTER_BOARD_SYSID, 1, &pyranometerMsg, solarIrradiance, 0 ); 
		pyranometerSend = true;
		pyranometerBuild = false;
	}else {
		pyranometerSend = false;
	}
}

void Handler::sendMAVMsg() {
	// Wind sensor
	if( windSend ) {
		MAVSerial->write_message( &windMsg );
		windSend = false;
	}
	// Lidar
	if( lidarSend ) {
		MAVSerial->write_message( &lidarMsg );
		lidarSend = false;
	}
	// Pyranometer
	if( pyranometerSend ) {
		MAVSerial->write_message( &pyranometerMsg );
		pyranometerSend = false;
	}

}

void Handler::receiveMsgQueue() {	
	// Wind sensor	
	if( windMsgQueue.receiveData() == RCV_SUCCESS ) {
		windBuild = true;
		angle = windMsgQueue.getAngle();
		windSpeed = windMsgQueue.getSpeed();
		temperature = windMsgQueue.getTemperature();
	}else { 
		windBuild = false;
	}
	// Lidar
	if( lidarMsgQueue.receive() == RCV_SUCCESS ) {
		lidarBuild = true;
		distance = lidarMsgQueue.getDistance();
	}else {
		lidarBuild = false;
	}
	// Pyranometer
	if( pyranometerMsgQueue.receive() == RCV_SUCCESS ) {
		pyranometerBuild = true;
		solarIrradiance = pyranometerMsgQueue.getSolarIrradiance();
	}else {
		pyranometerBuild = false;
	}
}

void Handler::sendConfigToSensors() {
	windMsgQueue.setSensorType( cfg.windSensorType );
	windMsgQueue.sendConfig();
}

void Handler::heartBeat() {  // Sends a heartbeat message every seconds
	mavlink_msg_heartbeat_pack( DAUGHTER_BOARD_SYSID, 1, &heartBeatMsg, 0 ); 
	std::cout << "HERE" << std::to_string( heartBeatMsg.msgid ) << std::endl;
	while( 1 ) {
		usleep( 1000000 );
		std::cout << "heartbeat" << std::endl;
		serialLock.lock();
		MAVSerial->write_message( &heartBeatMsg );
		serialLock.unlock();
	}
}
