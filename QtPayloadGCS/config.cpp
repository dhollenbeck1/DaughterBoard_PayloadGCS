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
    delete windSelect;
    delete comError;
}

Config::Config( Ui::configWindow *ui, Serial_Port *serial ) :
    ui( ui ), serial( serial )
{
    initData();
    ui->sendConfigButton->setEnabled( false );
    ui->addSensorButton->setEnabled( false );
    windSelect = new WindSensorSelect();
    connect( ui->sendConfigButton, SIGNAL( clicked() ), this, SLOT( sendConfig() ) );
    connect( ui->sensorsComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( setSensor() ) );
    connect( ui->addSensorButton, SIGNAL( clicked() ), this, SLOT( addSensor() ) );
    moveToThread( &thread );
    connect( &thread, SIGNAL( started() ), this, SLOT( waitForDaughterBoard() ) );
    thread.start();

}

void Config::begin() {
}

void Config::sendConfig() {
    buildMAVMsg();
    serial->write_message( &configMsg );
    serial->close_serial();
    delete windSelect;

    emit openMainWindow();
}

void Config::setWindSensorType() {

}

void Config::initData() {
    windSensorStatus = 0;
    windSensorType = 0;
    lidarStatus = 0;
    pyranometerStatus = 0;
    oplsStatus = 0;
    sensorComPortNum = 1;
    windSensorComPortNum = 0;
    oplsComPortNum = 0;
}

void Config::buildMAVMsg() {
    mavlink_msg_config_pack( 254, 1, &configMsg, (uint8_t)windSensorStatus, (uint8_t)windSensorType,
                             (uint8_t)windSensorComPortNum, (uint8_t)lidarStatus, (uint8_t)pyranometerStatus,
                             (uint8_t)oplsStatus, (uint8_t)oplsComPortNum );
}

void Config::setSensor() {
    sensor = ui->sensorsComboBox->currentIndex();
}

void Config::addSensor() {
    if( !sensorsList.contains( ui->sensorsComboBox->currentText() )) {
        switch( sensor ) {
        case 0:
            windSensorStatus = 1;
            windSelect->show();
            while( windSelect->isVisible() );
            windSensorType = windSelect->getWindSensorType();
            windSensorComPortNum = sensorComPortNum;
            sensorComPortNum++;
            break;
        case 1:
            lidarStatus = 1;
            break;
        case 2:
            pyranometerStatus = 1;
            break;
        case 3:
            oplsStatus = 1;
            oplsComPortNum = sensorComPortNum;
            sensorComPortNum++;
            break;
        default:
            break;
        }
        ui->addedSensorsList->addItem( ui->sensorsComboBox->currentText() );
        sensorsList.append( ui->sensorsComboBox->currentText() );
        cout << "windType : " << windSensorType << " win port : " << windSensorComPortNum << " opls port : " << oplsComPortNum << endl;
    }
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
    ui->addSensorButton->setEnabled( true );
    ui->waitText->hide();
}

