#include "recordedplot.h"
#include <QFileDialog>


RecordedPlot::RecordedPlot()
{
}

RecordedPlot::RecordedPlot( QMainWindow *_mainWindow, Ui::MainWindow *_ui ) :
    mainWindow( _mainWindow ), ui( _ui )
{
    config();
}

RecordedPlot::~RecordedPlot()
{
}

void RecordedPlot::loadFromFile() {
    initData();
    if ( !QDir::setCurrent( QStringLiteral( "../QtPayloadGCS/LogFiles/" ) ) )
        qDebug() << "Could not change the current working directory";

    QString filename = QFileDialog::getOpenFileName( mainWindow,
           tr("Open data log file"), "",
           tr("Data log file (*.csv);;All Files (*)"));
    QFile dataLogFile( filename );
    if( !dataLogFile.open(QFile::ReadOnly |
                  QFile::Text) )
    {
        qDebug() << " Could not open the file for reading";
        return;
    }

    QTextStream in( &dataLogFile );

    while( !in.atEnd() ) {
        QString line = in.readLine();
        QStringList list = line.split( "," );
        if( list[ 0 ]  == "LI") {
            xLidar << list[ 1 ].toDouble();
            yLidar << list[ 2 ].toDouble();
        } else if( list[ 0 ]  == "PY") {
            xPyranometer << list[ 1 ].toDouble();
            yPyranometer << list[ 2 ].toDouble();
        } else if( list[ 0 ] == "WS") {
            xWindSpeed   << list[ 1 ].toDouble();
            xWindAngle   << xWindSpeed;
            xTemperature << xWindSpeed;
            yWindAngle   << list[ 2 ].toDouble();
            yWindSpeed   << list[ 3 ].toDouble();
            yTemperature << list[ 4 ].toDouble();
        } else if( list[ 0 ] == "OP" ) {
            xMethane << list[ 1 ].toDouble();
            xEthane  << xMethane;
            yMethane << list[ 2 ].toDouble();
            yEthane  << list[ 3 ].toDouble();
        }
    }

    dataLogFile.close();
    ui->recordPlot->clearGraphs();
}

void RecordedPlot::initData() {
    xLidar.clear();
    yLidar.clear();
    xWindSpeed.clear();
    yWindSpeed.clear();
    xWindAngle.clear();
    yWindAngle.clear();
    xTemperature.clear();
    yTemperature.clear();
    xPyranometer.clear();
    yPyranometer.clear();
    xMethane.clear();
    yMethane.clear();
    xEthane.clear();
    yEthane.clear();
}

void RecordedPlot::loadData() {
    switch( ui->recordDataSelect->currentIndex() ) {
    case 0:
        ui->nbPoints->display( xLidar.size() );
        break;
    case 1:
        ui->nbPoints->display( xWindAngle.size() );
        break;
    case 2:
        ui->nbPoints->display( xWindSpeed.size() );
        break;
    case 3:
        ui->nbPoints->display( xTemperature.size() );
        break;
    case 4:
        ui->nbPoints->display( xPyranometer.size() );
        break;
    case 5:
        ui->nbPoints->display( xMethane.size() );
        break;
    case 6:
        ui->nbPoints->display( xEthane.size() );
        break;
    }
}

void RecordedPlot::plotData() {
    switch( ui->recordDataSelect->currentIndex() ) {
    case 0:
        plotLidar();
        break;
    case 1:
        plotWindAngle();
        break;
    case 2:
        plotWindSpeed();
        break;
    case 3:
        plotTemperature();
        break;
    case 4:
        plotPyranometer();
        break;
    case 5:
        plotMethane();
        break;
    case 6:
        plotEthane();
        break;
    }
}


void RecordedPlot::plotLidar() {
    ui->recordPlot->addGraph(); // blue line
    int graphID = ui->lidarPlot->graphCount() - 1;
    qDebug() << graphID << endl;
    ui->recordPlot->graph( graphID )->setName( "Lidar data" );
    ui->recordPlot->graph( graphID )->setPen(QPen(QColor(40, 110, 255)));
    ui->recordPlot->graph( graphID )->setData( xLidar, yLidar );
    ui->recordPlot->graph( graphID )->rescaleAxes();
    ui->recordPlot->replot();
}

void RecordedPlot::plotPyranometer() {
    ui->recordPlot->addGraph(); // red line
    int graphID = ui->lidarPlot->graphCount() - 1;
    qDebug() << graphID << endl;
    ui->recordPlot->graph( graphID )->setName( "Pyranometer data" );
    ui->recordPlot->graph( graphID )->setPen(QPen(QColor(255, 40, 40)));
    ui->recordPlot->graph( graphID )->setData( xPyranometer, yPyranometer );
    ui->recordPlot->graph( graphID )->rescaleAxes();
    ui->recordPlot->replot();
}

void RecordedPlot::plotWindAngle() {
    ui->recordPlot->addGraph(); // red line
    int graphID = ui->lidarPlot->graphCount() - 1;
    qDebug() << graphID << endl;
    ui->recordPlot->graph( graphID )->setName( "Wind Angle" );
    ui->recordPlot->graph( graphID )->setPen(QPen(QColor(255, 40, 40)));
    ui->recordPlot->graph( graphID )->setData( xWindAngle, yWindAngle );
    ui->recordPlot->graph( graphID )->rescaleAxes();
    ui->recordPlot->replot();
}

void RecordedPlot::plotWindSpeed() {
    ui->recordPlot->addGraph(); // red line
    int graphID = ui->lidarPlot->graphCount() - 1;
    qDebug() << graphID << endl;
    ui->recordPlot->graph( graphID )->setName( "Wind Speed" );
    ui->recordPlot->graph( graphID )->setPen(QPen(QColor(255, 40, 40)));
    ui->recordPlot->graph( graphID )->setData( xWindSpeed, yWindSpeed );
    ui->recordPlot->graph( graphID )->rescaleAxes();
    ui->recordPlot->replot();
}

void RecordedPlot::plotTemperature() {
    ui->recordPlot->addGraph(); // red line
    int graphID = ui->lidarPlot->graphCount() - 1;
    qDebug() << graphID << endl;
    ui->recordPlot->graph( graphID )->setName( "Pyranometer data" );
    ui->recordPlot->graph( graphID )->setPen(QPen(QColor(255, 40, 40)));
    ui->recordPlot->graph( graphID )->setData( xTemperature, yTemperature );
    ui->recordPlot->graph( graphID )->rescaleAxes();
    ui->recordPlot->replot();
}

void RecordedPlot::plotMethane() {
    ui->recordPlot->addGraph(); // red line
    int graphID = ui->lidarPlot->graphCount() - 1;
    qDebug() << graphID << endl;
    ui->recordPlot->graph( graphID )->setName( "Pyranometer data" );
    ui->recordPlot->graph( graphID )->setPen(QPen(QColor(255, 40, 40)));
    ui->recordPlot->graph( graphID )->setData( xMethane, yMethane );
    ui->recordPlot->graph( graphID )->rescaleAxes();
    ui->recordPlot->replot();
}

void RecordedPlot::plotEthane() {
    ui->recordPlot->addGraph(); // red line
    int graphID = ui->lidarPlot->graphCount() - 1;
    qDebug() << graphID << endl;
    ui->recordPlot->graph( graphID )->setName( "Pyranometer data" );
    ui->recordPlot->graph( graphID )->setPen(QPen(QColor(255, 40, 40)));
    ui->recordPlot->graph( graphID )->setData( xEthane, yEthane );
    ui->recordPlot->graph( graphID )->rescaleAxes();
    ui->recordPlot->replot();
}


void RecordedPlot::config() {
    ui->recordPlot->axisRect()->setupFullAxesBox();
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->recordPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->recordPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->recordPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->recordPlot->yAxis2, SLOT(setRange(QCPRange)));
    ui->recordPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

