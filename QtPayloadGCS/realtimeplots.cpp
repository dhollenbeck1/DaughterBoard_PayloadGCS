#include "realtimeplots.h"
#include <QDebug>
#include <QDateTime>

using namespace std;

RealTimePlots::RealTimePlots()
{
}

RealTimePlots::RealTimePlots( Ui::MainWindow *ui ) :
    ui( ui )
{
    config();
}

RealTimePlots::~RealTimePlots()
{
    serialThread.quit();
    serialThread.wait();
    delete arrow;
    delete out;
    delete dataLogFile;
}

void RealTimePlots::config() {
    ui->lidarPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    ui->lidarPlot->xAxis->setTickLabelFont(font);
    ui->lidarPlot->xAxis->setLabel( "Time" );
    ui->lidarPlot->yAxis->setTickLabelFont(font);
    ui->lidarPlot->yAxis->setLabel( "Distance in cm" );
    ui->lidarPlot->legend->setFont(font);
    ui->lidarPlot->addGraph(); // blue line
    ui->lidarPlot->graph(0)->setName( "Lidar data" );
    ui->lidarPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->lidarLcd->setPalette( Qt::blue );
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->lidarPlot->xAxis->setTicker(timeTicker);
    ui->lidarPlot->axisRect()->setupFullAxesBox();
    ui->lidarPlot->yAxis->setRange(0, 900);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->lidarPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->lidarPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->lidarPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->lidarPlot->yAxis2, SLOT(setRange(QCPRange)));

    ui->pyranometerPlot->setNotAntialiasedElements(QCP::aeAll);
    ui->pyranometerPlot->xAxis->setTickLabelFont(font);
    ui->pyranometerPlot->xAxis->setLabel( "Time" );
    ui->pyranometerPlot->yAxis->setTickLabelFont(font);
    ui->pyranometerPlot->yAxis->setLabel( "Distance in cm" );
    ui->pyranometerPlot->legend->setFont(font);
    ui->pyranometerPlot->addGraph(); // blue line
    ui->pyranometerPlot->graph(0)->setName( "Lidar data" );
    ui->pyranometerPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->pyranometerLcd->setPalette( Qt::blue );
    ui->pyranometerPlot->xAxis->setTicker(timeTicker);
    ui->pyranometerPlot->axisRect()->setupFullAxesBox();
    ui->pyranometerPlot->yAxis->setRange(0, 2500);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->pyranometerPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->pyranometerPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->pyranometerPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->pyranometerPlot->yAxis2, SLOT(setRange(QCPRange)));

    ui->windSensorPlot->addGraph(); // blue line
    ui->windSensorPlot->yAxis->setRange(-5, 5);
    ui->windSensorPlot->xAxis->setRange(-5, 5);
    arrow = new QCPItemLine( ui->windSensorPlot );
    arrow->setHead(QCPLineEnding::esSpikeArrow);
    arrow->start->setCoords( 0, 0 );
    arrow->end->setCoords( 0, 0 );

    ui->oplsPlot->setNotAntialiasedElements(QCP::aeAll);
    ui->oplsPlot->xAxis->setTickLabelFont(font);
    ui->oplsPlot->xAxis->setLabel( "Time" );
    ui->oplsPlot->yAxis->setTickLabelFont(font);
    ui->oplsPlot->yAxis->setLabel( "Concentration in ppm" );
    ui->oplsPlot->legend->setFont(font);
    ui->oplsPlot->addGraph(); // blue line
    ui->oplsPlot->graph(0)->setName( "Methane concentration" );
    ui->oplsPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->methaneLcd->setPalette( Qt::blue );
    ui->oplsPlot->addGraph(); // blue line
    ui->oplsPlot->graph(1)->setName( "Ethane concentration" );
    ui->oplsPlot->graph(1)->setPen(QPen(QColor(255, 40, 40)));
    ui->ethaneLcd->setPalette( Qt::red );
    ui->oplsPlot->xAxis->setTicker(timeTicker);
    ui->oplsPlot->axisRect()->setupFullAxesBox();
    ui->oplsPlot->yAxis->setRange(0, 10);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->oplsPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->oplsPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->oplsPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->oplsPlot->yAxis2, SLOT(setRange(QCPRange)));

    // Begin serial and move to a thread
    serial = new Serial_Port( "/dev/ttyUSB0", 38400 );
    serial->start();
    serial->moveToThread( &serialThread );
    connect(&serialThread, &QThread::finished, serial, &QObject::deleteLater);
    connect(this, &RealTimePlots::begin, serial, &Serial_Port::receiveData);
    connect(serial, &Serial_Port::dataReceived, this, &RealTimePlots::dataSlot);
    serialThread.start();

    lidarStop();
    pyranometerStop();
    recordAll = false;
    firstDataReceived = true;

    emit begin();
}

void RealTimePlots::setStartTime( unsigned int _startSec ) {
    startSec = _startSec;
}

void RealTimePlots::setTime( unsigned int _currSec, unsigned int _uSec ) {
    currSec  = _currSec - startSec;
    uSec     = _uSec;
    currTime = (double)currSec + (double)uSec / (double)1e6;
}

void RealTimePlots::lidarSetData( double _distance ) {
    distance = _distance;
}

void RealTimePlots::windSetData( double _windSpeed, int _windAngle, double _temperature ){
    windSpeed   = _windSpeed;
    windAngle   = _windAngle;
    temperature = _temperature;
}

void RealTimePlots::pyranometerSetData( double _solarIrradiance ) {
    solarIrradiance = _solarIrradiance;
}

void RealTimePlots::oplsSetData( double _oplsTime, double _methane, double _ethane ) {
    oplsTime = _oplsTime;
    methane  = _methane;
    ethane   = _ethane;
}

void RealTimePlots::lidarStart() {
}

void RealTimePlots::pyranometerStart() {
}

void RealTimePlots::lidarStop() {
}

void RealTimePlots::pyranometerStop() {
}

void RealTimePlots::startRecording() {
    recordAll = true;
    createLogFile();
}

void RealTimePlots::stopRecording() {
    recordAll = false;
    closeLogFile();
}

void RealTimePlots::initData() {
    lidarSetData( 0.0 );
    windSetData( 0.0, 0, 0.0 );
    pyranometerSetData( 0.0 );
}

void RealTimePlots::dataSlot()
{
    // add data to lines:
    switch( serial->getMsgID() ) {
      case MAVLINK_MSG_ID_LIDAR:
        if( firstDataReceived ) {
            setStartTime( serial->li.sec );
            setTime( serial->li.sec, serial->li.usec );
            firstDataReceived = false;
        } else {
            setTime( serial->li.sec, serial->li.usec );
        }

        lidarSetData( serial->li.distance );
        ui->lidarPlot->graph(0)->addData(currTime, distance );
        // rescale value (vertical) axis to fit the current data:
        //ui->lidarPlot->graph(0)->rescaleValueAxis();
        ui->lidarPlot->xAxis->setRange(currTime, 8, Qt::AlignRight);
        ui->lidarPlot->replot();
        ui->lidarLcd->display( distance );
        cout << "LI " << currTime << " " << distance << endl;
        if( recordAll )
            *out << "LI," << currTime << "," << distance << endl;
      break;
      case MAVLINK_MSG_ID_WIND_SENSOR:
        if( firstDataReceived ) {
            setStartTime( serial->li.sec );
            setTime( serial->li.sec, serial->li.usec );
            firstDataReceived = false;
        } else {
            setTime( serial->li.sec, serial->li.usec );
        }

        windSetData( serial->ws.wind_speed, serial->ws.angle, serial->ws.temperature );
        // rescale value (vertical) axis to fit the current data:*/
        ui->windSensorPlot->graph(0)->rescaleValueAxis();
        arrow->end->setCoords( - windSpeed * sin( windAngle * M_PI / 180 ), - windSpeed * cos( windAngle * M_PI / 180 ) );
        ui->windSensorPlot->replot();
        ui->windSpeedLcd->display( windSpeed );
        ui->windAngleLcd->display( windAngle );
        ui->windTemperatureLcd->display( temperature );
        cout << "WS " << currTime << " " << windAngle << " " << windSpeed << endl;
        if( recordAll )
            *out << "WS," << currTime << "," << windAngle << "," << windSpeed << "," << temperature <<  endl;
      break;
      case MAVLINK_MSG_ID_PYRANOMETER:
        if( firstDataReceived ) {
            setStartTime( serial->li.sec );
            setTime( serial->li.sec, serial->li.usec );
            firstDataReceived = false;
        } else {
            setTime( serial->li.sec, serial->li.usec );
        }

        pyranometerSetData( serial->py.solarIrradiance );
        ui->pyranometerPlot->graph(0)->addData(currTime, solarIrradiance );
        // rescale value (vertical) axis to fit the current data:
        //ui->pyranometerPlot->graph(0)->rescaleValueAxis();
        ui->pyranometerPlot->xAxis->setRange(currTime, 8, Qt::AlignRight);
        ui->pyranometerPlot->replot();
        ui->pyranometerLcd->display(solarIrradiance );
        cout << "PY " << currTime << " " << solarIrradiance << endl;
        if( recordAll )
            *out << "PY," << currTime << "," << solarIrradiance << endl;
      break;
      case MAVLINK_MSG_ID_OPLS:
        if( firstDataReceived ) {
            setStartTime( serial->li.sec );
            setTime( serial->li.sec, serial->li.usec );
            firstDataReceived = false;
        } else {
            setTime( serial->li.sec, serial->li.usec );
        }

       oplsSetData( serial->op.time, serial->op.ch4 * 1e6, serial->op.et * 1e6 );
       ui->oplsPlot->graph(0)->addData( currTime, methane );
       ui->oplsPlot->graph(1)->addData( currTime, ethane );
       // rescale value (vertical) axis to fit the current data:
       //ui->oplsPlot->graph(0)->rescaleValueAxis();
       ui->oplsPlot->xAxis->setRange(currTime, 8, Qt::AlignRight);
       ui->oplsPlot->replot();
       ui->methaneLcd->display( methane );
       ui->ethaneLcd->display( ethane );
       cout << "OP " << currTime << " " << methane << " " << ethane << endl;
       if( recordAll )
           *out << "OP," << currTime << "," << methane << "," << ethane << endl;
     break;
   }
}

void RealTimePlots::createLogFile() {
    QString filename;

    filename += "../QtPayloadGCS/LogFiles/DataLog_";
    filename += to_string( startSec ).c_str();
    filename += ".csv";
    dataLogFile = new QFile( filename );

    // Trying to open in WriteOnly
    if( !dataLogFile->open( QFile::WriteOnly ) )
    {
        qDebug() << " Could not open file for writing";
    }

    out = new QTextStream( dataLogFile );
}

void RealTimePlots::closeLogFile() {
    dataLogFile->flush();
    dataLogFile->close();
}

