#ifndef CONFIG_H
#define CONFIG_H

#include "ui_configwindow.h"
#include "windsensorselect.h"
#include "communicationerror.h"
#include "serialport.h"
#include <QThread>
#include <QObject>
#include <iostream>

class Config : public QObject
{
    Q_OBJECT

public:
    Config();
    Config( Ui::configWindow *ui, Serial_Port *serial );
    ~Config();
    void begin();

private slots:
    void sendConfig();
    void setWindSensorType();
    void setSensor();
    void addSensor();
    void waitForDaughterBoard();

signals:
    void openMainWindow();
    void close();

private:
    Ui::configWindow *ui;
    Serial_Port *serial;
    QThread thread;
    WindSensorSelect *windSelect;
    CommunicationError *comError;
    int windSensorType;
    int sensor; // index 0: Lidar, 1: Pyranometer, 2: Wind sensor, 3: OPLS
    QStringList sensorsList;
    int windSensorStatus, lidarStatus, pyranometerStatus, oplsStatus;
    int sensorComPortNum;
    int windSensorComPortNum;
    int oplsComPortNum;
    void initData();
    void buildMAVMsg();
    bool daughterBoardAlive();
    mavlink_message_t configMsg, heartBeatMsg;
};

#endif // CONFIG_H

