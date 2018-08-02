#include <sys/msg.h>
#include <iostream>
#include "constants.h"

using namespace std;


class WindMsgQueue {

public:
	const long DATA_MSG_TYPE   = 1;
	const long CONFIG_MSG_TYPE = 2;
	
	WindMsgQueue();
	~WindMsgQueue();
	int sendData();
	int receiveData();
	int sendConfig();
	int receiveConfig();
	void setSensorStatus( uint8_t _sensorStatus);
	void setAngle( uint16_t _angle );
	void setSpeed( float _speed );
	void setTemperature( float _temperature );
	void setSensorType( uint8_t __stype );
	void setSerialPortNum( uint8_t _num );
	
	uint16_t getAngle();
	float getSpeed();
	float getTemperature();
	uint8_t getSensorStatus();
	uint8_t getSensorType();
	uint8_t getSerialPortNum();
	
private:
	key_t key;
	int msgid;
	
	struct _dataMessage {
		long type;
		uint16_t angle;
		float speed;
		float temperature;
	} dataMessage;
	
	int dataMsgLength;
	
	struct _configMessage {
		long type;
		uint8_t sensorStatus;
		uint8_t stype;
		uint8_t serialPortNum;
	} configMessage;
	
	int configMsgLength;
};

WindMsgQueue::WindMsgQueue() {
	//key = ftok( "progfile", 65 );
	key = 0x99990001;
	if( ( msgid = msgget( key, 0600 | IPC_CREAT ) ) == -1 ) {
		perror( "msgget" );
		cout << "msgget error" << endl;
	}
	dataMessage.type    = DATA_MSG_TYPE;
	dataMessage.angle   = 0;
	dataMessage.speed   = 0.0;
	configMessage.type  = CONFIG_MSG_TYPE;
	configMessage.stype = FT205;
	dataMsgLength = sizeof( dataMessage ) - sizeof( long );
	configMsgLength = sizeof( configMessage ) - sizeof( long );
}

WindMsgQueue::~WindMsgQueue() {
	msgctl(msgid, IPC_RMID, NULL);   // Clear Msg Queue
}

int WindMsgQueue::sendConfig() {
	if( msgsnd( msgid, &configMessage, configMsgLength, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else 
		return SND_SUCCESS;
}

int WindMsgQueue::receiveConfig() {
	if( msgrcv( msgid, &configMessage, configMsgLength, CONFIG_MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else {
		return RCV_SUCCESS;
	}
}

int WindMsgQueue::sendData() {
	if( msgsnd( msgid, &dataMessage, dataMsgLength, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else 
		return SND_SUCCESS;
}

int WindMsgQueue::receiveData() {
	if( msgrcv( msgid, &dataMessage, dataMsgLength, DATA_MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else {
		return RCV_SUCCESS;
	}
}

void WindMsgQueue::setSensorStatus( uint8_t _sensorStatus ) {
	configMessage.sensorStatus = _sensorStatus;
}

void WindMsgQueue::setAngle( uint16_t _angle ) {
	dataMessage.angle = _angle;
}

void WindMsgQueue::setSpeed( float _speed ) {
	dataMessage.speed = _speed;
}
void WindMsgQueue::setTemperature( float _temperature ) {
	dataMessage.temperature = _temperature;
}

void WindMsgQueue::setSensorType( uint8_t _stype ) {
	configMessage.stype = _stype;
}

void WindMsgQueue::setSerialPortNum( uint8_t _num ) {
	configMessage.serialPortNum = _num;
}

uint8_t WindMsgQueue::getSensorStatus() {
	return configMessage.sensorStatus;
}

uint16_t WindMsgQueue::getAngle() {
	return dataMessage.angle;
}

float WindMsgQueue::getSpeed() {
	return dataMessage.speed;
}

float WindMsgQueue::getTemperature() {
	return dataMessage.temperature;
}

uint8_t WindMsgQueue::getSensorType() {
	return configMessage.stype;
}

uint8_t WindMsgQueue::getSerialPortNum() {
	return configMessage.serialPortNum;
}

