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
        }
        // TODO: add other data sensors
    }

    dataLogFile.close();
    ui->recordPlot->clearGraphs();
    ui->recordPlot->replot();
    ui->lidarNbPts->display( xLidar.size() );
    ui->pyranometerNbPts->display( xPyranometer.size() );
}

void RecordedPlot::initData() {
    xLidar.clear();
    yLidar.clear();
    xWind.clear();
    yWind.clear();
    xPyranometer.clear();
    yPyranometer.clear();
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

void RecordedPlot::plotWind() {
}


void RecordedPlot::config() {
    ui->recordPlot->axisRect()->setupFullAxesBox();
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->recordPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->recordPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->recordPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->recordPlot->yAxis2, SLOT(setRange(QCPRange)));
    ui->recordPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

