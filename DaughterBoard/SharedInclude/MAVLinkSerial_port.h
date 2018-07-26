#include "serial_port.h"
#include "MAVLink/sensors/mavlink.h"


class MAVLinkSerial_Port : public Serial_Port {
	
public:
	MAVLinkSerial_Port( const char* _uart_name , int _baudrate, int _mode );
	
	int read_message(mavlink_message_t* message);
	int write_message(mavlink_message_t* message);

private:
	mavlink_status_t lastStatus;

	
};

MAVLinkSerial_Port::MAVLinkSerial_Port( const char* _uart_name , int _baudrate, int _mode ) {
	initialize_defaults();
	uart_name = _uart_name;
	baudrate  = _baudrate;
	mode      = _mode;
}

int MAVLinkSerial_Port::read_message(mavlink_message_t* message)
{
	char          cp;
	mavlink_status_t status;
	uint8_t          msgReceived = false;

	// --------------------------------------------------------------------------
	//   READ FROM PORT
	// --------------------------------------------------------------------------

	// this function locks the port during read
	int result = read_port(&cp);


	// --------------------------------------------------------------------------
	//   PARSE MESSAGE
	// --------------------------------------------------------------------------
	if (result > 0)
	{
		// the parsing
		msgReceived = mavlink_parse_char(MAVLINK_COMM_1, cp, message, &status);

		// check for dropped packets
		if ( (lastStatus.packet_rx_drop_count != status.packet_rx_drop_count) && debug )
		{
			printf("ERROR: DROPPED %d PACKETS\n", status.packet_rx_drop_count);
			unsigned char v=cp;
			fprintf(stderr,"%02x ", v);
		}
		lastStatus = status;
	}

	// Couldn't read from port
	else
	{
		fprintf(stderr, "ERROR: Could not read from fd %d\n", fd);
	}

	// --------------------------------------------------------------------------
	//   DEBUGGING REPORTS
	// --------------------------------------------------------------------------
	if(msgReceived && debug)
	{
		// Report info
		printf("Received message from serial with ID #%d (sys:%d|comp:%d):\n", message->msgid, message->sysid, message->compid);

		fprintf(stderr,"Received serial data: ");
		unsigned int i;
		uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

		// check message is write length
		unsigned int messageLength = mavlink_msg_to_send_buffer(buffer, message);

		// message length error
		if (messageLength > MAVLINK_MAX_PACKET_LEN)
		{
			fprintf(stderr, "\nFATAL ERROR: MESSAGE LENGTH IS LARGER THAN BUFFER SIZE\n");
		}

		// print out the buffer
		else
		{
			for (i=0; i<messageLength; i++)
			{
				unsigned char v=buffer[i];
				fprintf(stderr,"%02x ", v);
			}
			fprintf(stderr,"\n");
		}
	}

	// Done!
	return msgReceived;
}

int MAVLinkSerial_Port::write_message(mavlink_message_t* message)
{
	char buf[300];

	// Translate message to buffer
	unsigned len = mavlink_msg_to_send_buffer((uint8_t*)buf, message);

	// Write buffer to serial port, locks port while writing
	int bytesWritten = write_port(buf,len);

	return bytesWritten;
}
