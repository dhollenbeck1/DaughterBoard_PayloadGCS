#include <iostream>
#include "i2cLidar.h"
#include "../SharedInclude/LidarMsgQueue.h"
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
	
	i2cLidar lidar;
	LidarMsgQueue msgQueue;
	
	usleep( 1000000 );	
	while( 1 ) {
		lidar.measure();
		msgQueue.setDistance( lidar.getDistance() );
		msgQueue.send();
		cout << lidar.getDistance() << endl;
	}

	
	return EXIT_SUCCESS;
}

