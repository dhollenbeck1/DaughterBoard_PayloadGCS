#include <sys/msg.h>
#include <iostream>
#include "constants.h"

using namespace std;


class PyranometerMsgQueue {

public:
	const long MSG_TYPE = 1;
	
	PyranometerMsgQueue();
	~PyranometerMsgQueue() ;
	int send();
	int receive();
	void setSolarIrradiance( uint32_t _solarIrrandiance );
	void setSpeed( float speed );
	
	uint32_t getSolarIrradiance();
	
private:
	key_t key;
	int msgid;
	struct _message {
		long type;
		uint32_t solarIrradiance;
	} message;
	int length;
};


PyranometerMsgQueue::PyranometerMsgQueue() {
	//key = ftok( "progfile", 65 );
	key = 0x99990003;
	if( ( msgid = msgget( key, 0600 | IPC_CREAT ) ) == -1 ) {
		perror( "msgget" );
		cout << "msgget error" << endl;
	}
	message.type = MSG_TYPE;
	message.solarIrradiance = 0;
	length = sizeof( message ) - sizeof( long );
}

PyranometerMsgQueue::~PyranometerMsgQueue() {
	msgctl(msgid, IPC_RMID, NULL);   // Delete Msg Queue
}


int PyranometerMsgQueue::send() {
	if( msgsnd( msgid, &message, length, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else 
		return SND_SUCCESS;
}

int PyranometerMsgQueue::receive() {
	if( msgrcv( msgid, &message, length, MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else {
		return RCV_SUCCESS;
	}
}

void PyranometerMsgQueue::setSolarIrradiance( uint32_t _solarIrradiance ) {
	message.solarIrradiance = _solarIrradiance;
}

uint32_t PyranometerMsgQueue::getSolarIrradiance() {
	return message.solarIrradiance;
}


