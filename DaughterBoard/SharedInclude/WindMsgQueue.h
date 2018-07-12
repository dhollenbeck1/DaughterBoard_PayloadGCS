#include <sys/msg.h>
#include <iostream>
#include "constants.h"

using namespace std;


class WindMsgQueue {

public:
	const long MSG_TYPE = 1;
	
	WindMsgQueue();
	~WindMsgQueue() ;
	int send();
	int receive();
	void setAngle( uint16_t _angle );
	void setSpeed( float speed );
	
	uint16_t getAngle();
	float getSpeed();
	
private:
	key_t key;
	int msgid;
	struct _message {
		long type;
		uint16_t angle;
		float speed;
	} message;
	int length;
};


WindMsgQueue::WindMsgQueue() {
	//key = ftok( "progfile", 65 );
	key = 0x99990001;
	if( ( msgid = msgget( key, 0600 | IPC_CREAT ) ) == -1 ) {
		perror( "msgget" );
		cout << "msgget error" << endl;
	}
	message.type = MSG_TYPE;
	message.angle = 0;
	message.speed = 0.0;
	length = sizeof( message ) - sizeof( long );
}

WindMsgQueue::~WindMsgQueue() {
	msgctl(msgid, IPC_RMID, NULL);   // Clear Msg Queue
}


int WindMsgQueue::send() {
	if( msgsnd( msgid, &message, length, IPC_NOWAIT ) == -1 )
		return SND_FAILURE;
	else 
		return SND_SUCCESS;
}

int WindMsgQueue::receive() {
	if( msgrcv( msgid, &message, length, MSG_TYPE, IPC_NOWAIT ) == -1 ) {
		return RCV_FAILURE;
	}else {
		return RCV_SUCCESS;
	}
}

void WindMsgQueue::setAngle( uint16_t _angle ) {
	message.angle = _angle;
}

void WindMsgQueue::setSpeed( float _speed ) {
	message.speed = _speed;
}

uint16_t WindMsgQueue::getAngle() {
	return message.angle;
}

float WindMsgQueue::getSpeed() {
	return message.speed;
}
