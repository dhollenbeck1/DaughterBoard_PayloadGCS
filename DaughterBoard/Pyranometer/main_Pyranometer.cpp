#include "Pyranometer.h"
#include <unistd.h>

int main( int argc, char **argv ){

	Pyranometer pyranometer;
	
	pyranometer.waitForConfig();
		
	usleep( 1000000 );
	while( 1 ){
		pyranometer.sense();
		pyranometer.msgQueue.setSolarIrradiance( pyranometer.getSolarIrradiance() );
		cout << pyranometer.getSolarIrradiance() << endl;
		pyranometer.msgQueue.sendData();
	}

	return EXIT_SUCCESS;
}
