#include "WindSensor.h"
#include "../SharedInclude/WindMsgQueue.h"
#include <unistd.h>

int main( int argc, char **argv ){

	WindSensor windSensor;
	WindMsgQueue msgQueue;
	windSensor.init();
		
	while( 1 ){
		windSensor.sense();
		msgQueue.setAngle( windSensor.getAngle() );
		msgQueue.setSpeed( windSensor.getWindSpeed() );
		cout << windSensor.getAngle() << " " << windSensor.getWindSpeed() << endl;
		msgQueue.send();
	}

	return EXIT_SUCCESS;
}
