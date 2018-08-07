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
    serial = new Serial_Port( "/dev/ttyUSB0", 57600 );
    serial->start();
    serial->moveToThread( &serialThread );
    connect(&serialThread, &QThread::finished, serial, &QObject::deleteLater);
    connect(this, &RealTimePlots::begin, serial, &Serial_Port::receiveData);
    connect(serial, &Serial_Port::dataReceived, this, &RealTimePlots::dataSlot);
    serialThread.start();

    lidarStop();
    pyranometerStop();
    recordAll = false;

    emit begin();
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
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
      switch( serial->getMsgID() ) {
        case MAVLINK_MSG_ID_LIDAR:
          lidarSetData( serial->li.distance );
          ui->lidarPlot->graph(0)->addData(key, distance );
          // rescale value (vertical) axis to fit the current data:
          //ui->lidarPlot->graph(0)->rescaleValueAxis();
          ui->lidarPlot->xAxis->setRange(key, 8, Qt::AlignRight);
          ui->lidarPlot->replot();
          ui->lidarLcd->display( distance );
          if( recordAll )
              *out << "LI," << key << "," << distance << endl;
          lastPointKey = key;
        break;
        case MAVLINK_MSG_ID_WIND_SENSOR:
            windSetData( serial->ws.wind_speed, serial->ws.angle, serial->ws.temperature );
            /*ui->lidarPlot->graph(0)->addData(key, windSpeed );
            // rescale value (vertical) axis to fit the current data:*/
            ui->windSensorPlot->graph(0)->rescaleValueAxis();
            arrow->end->setCoords( - windSpeed * sin( windAngle * M_PI / 180 ), - windSpeed * cos( windAngle * M_PI / 180 ) );
            ui->windSensorPlot->replot();
            ui->windSpeedLcd->display( windSpeed );
            ui->windAngleLcd->display( windAngle );
            ui->windTemperatureLcd->display( temperature );
            if( recordAll )
                *out << "WS," << key << "," << windAngle << "," << windSpeed << "," << temperature <<  endl;
            lastPointKey = key;
        break;
        case MAVLINK_MSG_ID_PYRANOMETER:
          pyranometerSetData( serial->py.solarIrradiance );
          ui->pyranometerPlot->graph(0)->addData(key, solarIrradiance );
          // rescale value (vertical) axis to fit the current data:
          //ui->pyranometerPlot->graph(0)->rescaleValueAxis();
          ui->pyranometerPlot->xAxis->setRange(key, 8, Qt::AlignRight);
          ui->pyranometerPlot->replot();
          ui->pyranometerLcd->display(solarIrradiance );
          if( recordAll )
              *out << "PY," << key << "," << solarIrradiance << endl;
          lastPointKey = key;
        break;
        case MAVLINK_MSG_ID_OPLS:
          oplsSetData( serial->op.time, serial->op.ch4 * 1e6, serial->op.et * 1e6 );
          ui->oplsPlot->graph(0)->addData( key, methane );
          ui->oplsPlot->graph(1)->addData( key, ethane );
          // rescale value (vertical) axis to fit the current data:
          //ui->oplsPlot->graph(0)->rescaleValueAxis();
          ui->oplsPlot->xAxis->setRange(key, 8, Qt::AlignRight);
          ui->oplsPlot->replot();
          ui->methaneLcd->display( methane );
          ui->ethaneLcd->display( ethane );
          if( recordAll )
              *out << "OP," << oplsTime << "," << methane << "," << ethane << endl;
          lastPointKey = key;
        break;
      }
  }
}

void RealTimePlots::createLogFile() {
    QString filename;
    time_t t = time( nullptr );

    filename += "../QtPayloadGCS/LogFiles/DataLog_";
    filename += to_string( t ).c_str();
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

