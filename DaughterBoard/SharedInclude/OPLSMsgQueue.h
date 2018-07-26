#include <sys/msg.h>
#include <iostream>
#include "constants.h"

using namespace std;


class OPLSMsgQueue {

public:
	const long DATA_MSG_TYPE   = 1;
	const long CONFIG_MSG_TYPE = 2;
	
	OPLSMsgQueue();
	~OPLSMsgQueue() ;
	int sendConfig();
	int receiveConfig();
	int sendData();
	int receiveData();
	void setOPLSData( oplsData _data );
	oplsData getOPLSData();

	uint32_t getSolarIrradiance();
	
private:
	key_t key;
	int msgid;
	struct _dataMessage {
		long type;
		oplsData data;
	} dataMessage;
	int dataMsgLength;
	void initDataStructure();
	
	struct _configMessage {
		long type;
	} configMessage;
	
	int configMsgLength;
};


OPLSMsgQueue::OPLSMsgQueue() {
	//key = ftok( "progfile", 65 );
	key = 0x99990004;
	if( ( msgid = msgget( key, 0600 | IPC_CREAT ) ) == -1 ) {
		perror( "msgget" );
		cout << "msgget error" << endl;
	}
	
	dataMessage.type = DATA_MSG_TYPE;
	initDataStructure();
	dataMsgLength = sizeof( dataMessage ) - sizeof( long );
	configMessage.type  = CONFIG_MSG_TYPE;
	configMsgLength = sizeof( configMessage ) - sizeof( long );
}

OPLSMsgQueue::~OPLSMsgQueue() {
	msgctl(msgid, IPC_RMID, NULL);   // Delete Msg Queue
}

int OPLSMsgQueue::sendConfig() {
	if( msgsnd( msgid, &configMessage, configMsgLength, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else 
		return SND_SUCCESS;
}

int OPLSMsgQueue::receiveConfig() {
	if( msgrcv( msgid, &configMessage, configMsgLength, CONFIG_MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else {
		return RCV_SUCCESS;
	}
}

int OPLSMsgQueue::sendData() {
	if( msgsnd( msgid, &dataMessage, dataMsgLength, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else 
		return SND_SUCCESS;
}

int OPLSMsgQueue::receiveData() {
	if( msgrcv( msgid, &dataMessage, dataMsgLength, DATA_MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else {
		return RCV_SUCCESS;
	}
}


void OPLSMsgQueue::setOPLSData( oplsData _data ) {
	dataMessage.data = _data;
}

oplsData OPLSMsgQueue::getOPLSData() {
	return dataMessage.data;
}

void OPLSMsgQueue::initDataStructure() {
	dataMessage.data.time_ = 0;
	dataMessage.data.ch4   = 0;
	dataMessage.data.et    = 0;
	dataMessage.data.h2o   = 0;
	dataMessage.data.lat   = 0;
	dataMessage.data.lon   = 0;
	dataMessage.data.lsr   = 0;
	dataMessage.data.p     = 0;
	dataMessage.data.rf    = 0;
	dataMessage.data.t     = 0;
}

