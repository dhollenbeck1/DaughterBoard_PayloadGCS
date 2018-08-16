#include <string>
#include <iostream>
#include <sstream>
#include <list>  
#include <mutex>  
#include <time.h>
#include "../SharedInclude/constants.h"
#include "../SharedInclude/MAVLinkSerial_port.h"
#include "../SharedInclude/LidarMsgQueue.h"
#include "../SharedInclude/WindMsgQueue.h"
#include "../SharedInclude/PyranometerMsgQueue.h"
#include "../SharedInclude/OPLSMsgQueue.h"



#define DEBUG

using namespace std;


enum MAVmsgType { wind, lidar, pyranometer, opls }; 

class Handler{
	
public:
	const char* XBeePort = "/dev/ttyUSB0";
	const int baudRate   = 38400;
	const int DAUGHTER_BOARD_SYSID = 32;
//#define SENSOR_OK             0
//#define SENSOR_NOT_RESPONDING 0xFF
	
	Handler();
	~Handler();
	void init();
	void handle();
	void waitForConfig();
	void heartBeat();  
	
private:	
	LidarMsgQueue lidarMsgQueue;
	WindMsgQueue windMsgQueue;
	PyranometerMsgQueue pyranometerMsgQueue;
	OPLSMsgQueue oplsMsgQueue;
	
	MAVmsgType msgType;  			
	void receiveMsgQueue();
	void buildMAVMsg();              
	void sendMAVMsg();	
	void sendConfigToSensors(); 

	std::mutex serialLock;
	MAVLinkSerial_Port* MAVSerial;
	mavlink_message_t heartBeatMsg, configMsg, windMsg, lidarMsg, pyranometerMsg, oplsMsg;
	mavlink_config_t cfg;
	bool windBuild, lidarBuild, pyranometerBuild, oplsBuild, windSend, lidarSend, pyranometerSend, oplsSend;
	uint16_t angle;
	float windSpeed;
	float temperature;
	uint16_t distance;
	uint32_t solarIrradiance;
	oplsData oplsdata;
	uint8_t status;
};


Handler::Handler() {
}

Handler::~Handler() {
	MAVSerial->close_serial();
	delete MAVSerial;
}

void Handler::init() {
	MAVSerial = new MAVLinkSerial_Port( XBeePort, baudRate, 0 );
	MAVSerial->start();
	windBuild        = false;
	lidarBuild       = false;
	pyranometerBuild = false;
	oplsBuild        = false;
	windSend         = false;
	lidarSend        = false;
	pyranometerSend  = false;
	oplsSend         = false;
	first            = true;
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
	if( lidarBuild || windBuild || pyranometerBuild || oplsBuild ) {
		buildMAVMsg();
	}
	if( lidarSend || windSend || pyranometerSend || oplsSend ) {
		sendMAVMsg();
	}
}


void Handler::buildMAVMsg() {
	// Wind Sensor
	if( windBuild ) {
		#ifdef DEBUG
			cout << "Wind : " << angle << " " << windSpeed << " " << temperature << endl;
		#endif
		mavlink_msg_wind_sensor_pack( DAUGHTER_BOARD_SYSID, 1, &windMsg, angle, windSpeed, temperature, 0 ); 
		windSend = true;
		windBuild = false;
	}else {
		windSend = false;
	}
	// Lidar
	if( lidarBuild ) {
		#ifdef DEBUG
			cout << "Lidar : " << distance << endl;
		#endif
		mavlink_msg_lidar_pack( DAUGHTER_BOARD_SYSID, 1, &lidarMsg, distance, 0 ); 
		lidarSend = true;
		lidarBuild = false;
	}else {
		lidarSend = false;
	}
	// Pyranometer
	if( pyranometerBuild ) {
		mavlink_msg_pyranometer_pack( DAUGHTER_BOARD_SYSID, 1, &pyranometerMsg, solarIrradiance, 0 ); 
		pyranometerSend = true;
		pyranometerBuild = false;
	}else {
		pyranometerSend = false;
	}
	// OPLS
	if( oplsBuild ) {
		mavlink_msg_opls_pack( DAUGHTER_BOARD_SYSID, 1, &oplsMsg, oplsdata.time_, oplsdata.ch4,
							   oplsdata.et , oplsdata.h2o, oplsdata.p, oplsdata.t, oplsdata.rf, 
							   oplsdata.lon, oplsdata.lat, oplsdata.lsr ); 
		oplsSend  = true;
		oplsBuild = false;
	}else {
		oplsSend = false;
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
	// OPLS
	if( oplsSend ) {
		MAVSerial->write_message( &oplsMsg );
		oplsSend = false;
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
	if( lidarMsgQueue.receiveData() == RCV_SUCCESS ) {
		lidarBuild = true;
		distance = lidarMsgQueue.getDistance();
std::cout << "distance : " << distance << std::endl;
	}else {
		lidarBuild = false;
	}
	// Pyranometer
	if( pyranometerMsgQueue.receiveData() == RCV_SUCCESS ) {
		pyranometerBuild = true;
		solarIrradiance = pyranometerMsgQueue.getSolarIrradiance();
	}else {
		pyranometerBuild = false;
	}
	// OPLS
	if( oplsMsgQueue.receiveData() == RCV_SUCCESS ) {
		oplsBuild = true;
		oplsdata  = oplsMsgQueue.getOPLSData();
	}else {
		oplsBuild = false;
	}

}

void Handler::sendConfigToSensors() {
	windMsgQueue.setSensorStatus( cfg.windSensorStatus );
	windMsgQueue.setSensorType( cfg.windSensorType );
	windMsgQueue.setSerialPortNum( cfg.windSensorComPortNum );
	lidarMsgQueue.setSensorStatus( cfg.lidarStatus );
	pyranometerMsgQueue.setSensorStatus( cfg.pyranometerStatus );
	oplsMsgQueue.setSensorStatus( cfg.oplsStatus );
	oplsMsgQueue.setSerialPortNum( cfg.oplsComPortNum );
	windMsgQueue.sendConfig();
	lidarMsgQueue.sendConfig();
	pyranometerMsgQueue.sendConfig();
	oplsMsgQueue.sendConfig();
}

void Handler::heartBeat() {  // Sends a heartbeat message every seconds
	mavlink_msg_heartbeat_pack( DAUGHTER_BOARD_SYSID, 1, &heartBeatMsg, 0 ); 
	while( 1 ) {
		usleep( 1000000 );
		std::cout << "heartbeat" << std::endl;
		serialLock.lock();
		MAVSerial->write_message( &heartBeatMsg );
		serialLock.unlock();
	}
}
