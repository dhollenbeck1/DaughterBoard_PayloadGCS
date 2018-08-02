#include "WindSensor.h"
#include <unistd.h>

int main( int argc, char **argv ){

	WindSensor windSensor;
	windSensor.waitForConfig();
	if( !windSensor.isAdded() )
		return EXIT_SUCCESS;
	windSensor.init();
	
	usleep( 1000000 );
	while( 1 ){
		windSensor.sense();
		windSensor.msgQueue.setAngle( windSensor.getAngle() );
		windSensor.msgQueue.setSpeed( windSensor.getWindSpeed() );
		windSensor.msgQueue.setTemperature( windSensor.getTemperature() );
		cout << windSensor.getAngle() << " " << windSensor.getWindSpeed() 
			 << " " << windSensor.getTemperature() << endl;
		windSensor.msgQueue.sendData();
	}

	return EXIT_SUCCESS;
}
