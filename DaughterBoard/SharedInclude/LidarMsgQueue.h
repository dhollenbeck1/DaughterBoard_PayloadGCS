#include <sys/msg.h>
#include <iostream>
#include "constants.h"
using namespace std;

class LidarMsgQueue {

public:
	const long MSG_TYPE = 2;
	
	LidarMsgQueue();
	~LidarMsgQueue();
	int send();
	int receive();
	void setDistance( uint16_t _distance );
	uint16_t getDistance();
	
private:
	key_t key;
	int msgid;
	struct _message {
		long type;
		uint16_t distance;
	} message;
	int length;
};


LidarMsgQueue::LidarMsgQueue() {
	//key = ftok( "progfile", 65 );
	key = 0x99990002;
	if( ( msgid = msgget( key, 0600 | IPC_CREAT ) ) == -1 ) {
		perror( "msgget" );
	}
	message.type = MSG_TYPE;
	message.distance = 0;
	length = sizeof( message ) - sizeof( long );
}

LidarMsgQueue::~LidarMsgQueue() {
	msgctl(msgid, IPC_RMID, NULL);   // Clear Msg Queue
}

int LidarMsgQueue::send() {
	if( msgsnd( msgid, &message, length, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else
		return SND_SUCCESS;
}

int LidarMsgQueue::receive() {
	if( msgrcv( msgid, &message, length, MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else  {
		return RCV_SUCCESS;
	}
}

uint16_t LidarMsgQueue::getDistance() {
	return message.distance;
}

void LidarMsgQueue::setDistance( uint16_t _distance ) {
	message.distance = _distance;
}

