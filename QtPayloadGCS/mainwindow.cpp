#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(100, 100, 1250, 750);

    realTimePlots = new RealTimePlots( ui );
    recordedPlot = new RecordedPlot( this, ui );

    // Connect buttons start and stop record for "real time" tab
    connect( ui->lidarStartButton, SIGNAL( clicked() ), realTimePlots, SLOT( lidarStart() ) );
    connect( ui->pyranometerStartButton, SIGNAL( clicked() ), realTimePlots, SLOT( pyranometerStart() ) );
    connect( ui->lidarStopButton, SIGNAL( clicked() ), realTimePlots, SLOT( lidarStop() ) );
    connect( ui->pyranometerStopButton, SIGNAL( clicked() ), realTimePlots, SLOT( pyranometerStop() ) );
    connect( ui->startRecordButton, SIGNAL( clicked() ), realTimePlots, SLOT( startRecording() ) );
    connect( ui->stopRecordButton, SIGNAL( clicked() ), realTimePlots, SLOT( stopRecording() ) );

    // Connect load file button and plot buttons for "recorded" tab
    connect( ui->loadFileButton, SIGNAL( clicked() ), recordedPlot, SLOT( loadFromFile() ) );
    connect( ui->recordDataSelect, SIGNAL( currentIndexChanged( int ) ), recordedPlot, SLOT( loadData() ) );
    connect( ui->plotButton, SIGNAL( clicked() ), recordedPlot, SLOT( plotData() ) );
}

MainWindow::~MainWindow()
{
    delete realTimePlots;
    delete recordedPlot;
    delete ui;
}





