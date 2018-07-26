#include "config.h"
#include <iostream>

using namespace std;

Config::Config()
{
}

Config::~Config()
{
    thread.quit();
    thread.wait();
    delete serial;
}

Config::Config( Ui::configWindow *ui ) :
    ui( ui )
{
    ui->errorText->setReadOnly( true );
    ui->waitText->setReadOnly( true );
    ui->infoText->setReadOnly( true );

    serial = new Serial_Port( "/dev/ttyUSB0", 57600 );
    if( serial->start() != EXIT_SUCCESS ) {
        ui->infoText->hide();
        ui->WindSensorGroupBox->hide();
        ui->sendConfigButton->hide();
        ui->waitText->hide();
        ui->errorText->show();
        ui->closeButton->show();
    } else {
        ui->errorText->hide();
        ui->closeButton->hide();
        connect( ui->sendConfigButton, SIGNAL( clicked() ), this, SLOT( sendConfig() ) );
        connect( ui->windSensorBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( setWindSensorType() ) );
        ui->sendConfigButton->setEnabled( false );
        windSensorType = 0;  // TODO: put this into an initData() method
        moveToThread( &thread );
        connect( &thread, SIGNAL( started() ), this, SLOT( waitForDaughterBoard() ) );
        thread.start();
    }

}

void Config::sendConfig() {
    buildMAVMsg();
    serial->write_message( &configMsg );
    serial->close_serial();
    delete serial;

    emit openMainWindow();
}

void Config::setWindSensorType() {
    switch( ui->windSensorBox->currentIndex() ) {
    case 0:
        windSensorType = 0;  // FT205
        std::cout << "HERE 0" << std::endl;
        break;
    case 1:
        windSensorType = 1;  // FT742
        std::cout << "HERE 1" << std::endl;
        break;
    case 2:
        windSensorType = 2;  // Trisonica
        std::cout << "HERE 2" << std::endl;
        break;
    default:
        windSensorType = 0;  // FT205
        std::cout << "HERE 0 default" << std::endl;
    }
}

void Config::buildMAVMsg() {
    mavlink_msg_config_pack( 254, 1, &configMsg, (uint8_t)windSensorType );
}

bool Config::daughterBoardAlive() {
    serial->read_message( &heartBeatMsg );
    if( heartBeatMsg.msgid == MAVLINK_MSG_ID_HEARTBEAT ) {
        return true;
    }
    return false;
}

void Config::waitForDaughterBoard() {
    while( !daughterBoardAlive() ){};
    ui->sendConfigButton->setEnabled( true );
    ui->waitText->hide();
}

