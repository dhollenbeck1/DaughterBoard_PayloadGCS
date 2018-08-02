#include <sys/msg.h>
#include <iostream>
#include "constants.h"
using namespace std;

class LidarMsgQueue {

public:
	const long DATA_MSG_TYPE   = 1;
	const long CONFIG_MSG_TYPE = 2;
	
	LidarMsgQueue();
	~LidarMsgQueue();
	int sendConfig();
	int receiveConfig();
	int sendData();
	int receiveData();
	void setSensorStatus( uint8_t _sensorStatus );
	void setDistance( uint16_t _distance );
	uint8_t getSensorStatus();
	uint16_t getDistance();
	
private:
	key_t key;
	int msgid;
	struct _dataMessage {
		long type;
		uint16_t distance;
	} dataMessage;
	int dataMsgLength;
	
	struct _configMessage {
		long type;
		uint8_t sensorStatus;
	} configMessage;
	
	int configMsgLength;
};


LidarMsgQueue::LidarMsgQueue() {
	//key = ftok( "progfile", 65 );
	key = 0x99990002;
	if( ( msgid = msgget( key, 0600 | IPC_CREAT ) ) == -1 ) {
		perror( "msgget" );
	}
	dataMessage.type = DATA_MSG_TYPE;
	dataMessage.distance = 0;
	dataMsgLength = sizeof( dataMessage ) - sizeof( long );
	configMessage.type  = CONFIG_MSG_TYPE;
	configMsgLength = sizeof( configMessage ) - sizeof( long );
}

LidarMsgQueue::~LidarMsgQueue() {
	msgctl(msgid, IPC_RMID, NULL);   // Clear Msg Queue
}

int LidarMsgQueue::sendConfig() {
	if( msgsnd( msgid, &configMessage, configMsgLength, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else 
		return SND_SUCCESS;
}

int LidarMsgQueue::receiveConfig() {
	if( msgrcv( msgid, &configMessage, configMsgLength, CONFIG_MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else {
		return RCV_SUCCESS;
	}
}

int LidarMsgQueue::sendData() {
	if( msgsnd( msgid, &dataMessage, dataMsgLength, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else
		return SND_SUCCESS;
}

int LidarMsgQueue::receiveData() {
	if( msgrcv( msgid, &dataMessage, dataMsgLength, DATA_MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else  {
		return RCV_SUCCESS;
	}
}

void LidarMsgQueue::setSensorStatus( uint8_t _sensorStatus ) {
	configMessage.sensorStatus = _sensorStatus;
}

void LidarMsgQueue::setDistance( uint16_t _distance ) {
	dataMessage.distance = _distance;
}

uint8_t LidarMsgQueue::getSensorStatus() {
	return configMessage.sensorStatus;
}

uint16_t LidarMsgQueue::getDistance() {
	return dataMessage.distance;
}


