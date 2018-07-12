#include <bcm2835.h>
#include <unistd.h>
#include <iostream>


class i2cLidar{
	
public:
	// For registers definitions see: https://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf
	const char LIDAR_I2C_ADDR      = 0x62;
	const char ACQ_COMMAND_REG     = 0x00;
	const char BIAS_CORREC_VAL     = 0x04;
	const char STATUS_REG          = 0x01;
	const char FULL_DELAY_HIGH_REG = 0x0F;
	const char FULL_DELAY_LOW_REG  = 0x10;
	
	i2cLidar();
	~i2cLidar();
	int init();
	void measure();
	int getDistance();
	void end();	

private:
	int distance;
};


i2cLidar::i2cLidar() {
	init();
}

i2cLidar::~i2cLidar() {
	end();
}


int i2cLidar::init() {
	if (!bcm2835_init())
        return EXIT_FAILURE;
	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress ( LIDAR_I2C_ADDR );
	
	return EXIT_SUCCESS;	
}

void i2cLidar::measure() {
	// Take distance measurement with receiver bias correction
	char buf[]={ ACQ_COMMAND_REG, BIAS_CORREC_VAL };
	bcm2835_i2c_write( buf, 2 );
	
	// Wait until device is ready for new command
	char buf2[] = { STATUS_REG };
	bcm2835_i2c_write( buf2, 1 );
	char tmp[] = { 1 };
	while( ( tmp[ 0 ] & 1 ) != 0 ) {
		bcm2835_i2c_read( tmp, 1 );
		usleep( 100000 );
	}
	
	// Read distance measurement high byte
	char hiVal[] = { FULL_DELAY_HIGH_REG };
	bcm2835_i2c_write( hiVal, 1 );
	bcm2835_i2c_read( hiVal, 1 );
	
	// Read distance measurement low byte
	char loVal[] = { FULL_DELAY_LOW_REG };
	bcm2835_i2c_write( loVal, 1 );
	bcm2835_i2c_read( loVal, 1 );
	
	// Build distance word with high and low bytes
	distance = hiVal[ 0 ];
	distance <<= 8;
	distance += loVal[ 0 ];
}

int i2cLidar::getDistance() {
	return distance;
}

void i2cLidar::end() {
	bcm2835_i2c_end ();
}
