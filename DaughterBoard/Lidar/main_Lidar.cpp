#include <iostream>
#include "i2cLidar.h"
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
	
	i2cLidar lidar;
	lidar.waitForConfig();
	
	usleep( 1000000 );	
	while( 1 ) {
		lidar.measure();
		lidar.msgQueue.setDistance( lidar.getDistance() );
		lidar.msgQueue.sendData();
		cout << lidar.getDistance() << endl;
	}

	
	return EXIT_SUCCESS;
}

