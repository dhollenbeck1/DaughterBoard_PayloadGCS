#include "Pyranometer.h"
#include "../SharedInclude/PyranometerMsgQueue.h"
#include <unistd.h>

int main( int argc, char **argv ){

	Pyranometer pyranometer;
	PyranometerMsgQueue msgQueue;
		
	usleep( 1000000 );
	while( 1 ){
		pyranometer.sense();
		msgQueue.setSolarIrradiance( pyranometer.getSolarIrradiance() );
		cout << pyranometer.getSolarIrradiance() << endl;
		msgQueue.send();
	}

	return EXIT_SUCCESS;
}
