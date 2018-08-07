#include "configwindow.h"
#include "ui_configwindow.h"

configWindow::configWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configWindow)
{
    ui->setupUi( this );
}

void configWindow::init( Serial_Port *_serial ) {
    serial = _serial;
    config = new Config( ui, serial );
    connect( this->config, SIGNAL( openMainWindow() ), this, SLOT( openMainWindow() ) );
    ui->waitText->setReadOnly( true );
    ui->infoText->setReadOnly( true );
}


configWindow::~configWindow()
{
    delete config;
    delete ui;
}

void configWindow::openMainWindow() {
    this->close();
    w = new MainWindow();
    w->show();
}

void configWindow::closeConfigWindow() {
    this->close();
}
