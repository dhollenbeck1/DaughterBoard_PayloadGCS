#include <sys/msg.h>
#include <iostream>
#include "constants.h"

using namespace std;


class PyranometerMsgQueue {

public:
	const long DATA_MSG_TYPE   = 1;
	const long CONFIG_MSG_TYPE = 2;
	
	PyranometerMsgQueue();
	~PyranometerMsgQueue() ;
	int sendData();
	int receiveData();
	int sendConfig();
	int receiveConfig();
	void setSolarIrradiance( uint32_t _solarIrrandiance );
	void setSpeed( float speed );
	
	uint32_t getSolarIrradiance();
	
private:
	key_t key;
	int msgid;
	struct _dataMessage {
		long type;
		uint32_t solarIrradiance;
	} dataMessage;
	int dataMsgLength;
	
	struct _configMessage {
		long type;
	} configMessage;
	
	int configMsgLength;

};


PyranometerMsgQueue::PyranometerMsgQueue() {
	//key = ftok( "progfile", 65 );
	key = 0x99990003;
	if( ( msgid = msgget( key, 0600 | IPC_CREAT ) ) == -1 ) {
		perror( "msgget" );
		cout << "msgget error" << endl;
	}
	dataMessage.type = DATA_MSG_TYPE;
	dataMessage.solarIrradiance = 0;
	dataMsgLength = sizeof( dataMessage ) - sizeof( long );
	configMessage.type  = CONFIG_MSG_TYPE;
	configMsgLength = sizeof( configMessage ) - sizeof( long );
}

PyranometerMsgQueue::~PyranometerMsgQueue() {
	msgctl(msgid, IPC_RMID, NULL);   // Delete Msg Queue
}

int PyranometerMsgQueue::sendConfig() {
	if( msgsnd( msgid, &configMessage, configMsgLength, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else 
		return SND_SUCCESS;
}

int PyranometerMsgQueue::receiveConfig() {
	if( msgrcv( msgid, &configMessage, configMsgLength, CONFIG_MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else {
		return RCV_SUCCESS;
	}
}

int PyranometerMsgQueue::sendData() {
	if( msgsnd( msgid, &dataMessage, dataMsgLength, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else 
		return SND_SUCCESS;
}

int PyranometerMsgQueue::receiveData() {
	if( msgrcv( msgid, &dataMessage, dataMsgLength, DATA_MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else {
		return RCV_SUCCESS;
	}
}

void PyranometerMsgQueue::setSolarIrradiance( uint32_t _solarIrradiance ) {
	dataMessage.solarIrradiance = _solarIrradiance;
}

uint32_t PyranometerMsgQueue::getSolarIrradiance() {
	return dataMessage.solarIrradiance;
}


