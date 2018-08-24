#ifndef REALTIMEPLOTS_H
#define REALTIMEPLOTS_H

#include "qcustomplot.h"
#include "ui_mainwindow.h"
#include "serialport.h"
#include <QThread>
#include <QObject>
#include <iostream>



class RealTimePlots : public QObject
{
    Q_OBJECT

public:
    RealTimePlots();
    RealTimePlots( Ui::MainWindow *ui );
    ~RealTimePlots();

private slots:
      void dataSlot();
      void lidarStart();      // TODO: send start/stop signals to the Daughter Board to enable/disable sensing
      void pyranometerStart();
      void lidarStop();
      void pyranometerStop();
      void startRecording();
      void stopRecording();
      void createLogFile();
      void closeLogFile();

private:
      void config();
      void setStartTime( unsigned int _startSec );
      void setTime( unsigned int _currSec, unsigned int _uSec );
      void initData();
      void lidarSetData( double _distance );
      void windSetData( double _windSpeed, int _windAngle, double _temperature );
      void pyranometerSetData( double _solarIrradiance );
      void oplsSetData( double _oplsTime, double _methane, double _ethane );

      bool recordAll, recordLidar, recordPyranometer;
      bool firstDataReceived;
      double distance, windSpeed, temperature, solarIrradiance, oplsTime, methane, ethane;
      int windAngle;
      unsigned int startSec, currSec, uSec;
      double currTime;
      Serial_Port *serial;
      QThread serialThread;
      Ui::MainWindow *ui;
      QFile *dataLogFile;
      QTextStream *out;
      QCPItemLine *arrow;

signals:
      void begin();
      void record();
};

#endif // REALTIMEPLOTS_H
