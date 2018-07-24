#include "configwindow.h"
#include "ui_configwindow.h"

configWindow::configWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configWindow)
{
    ui->setupUi( this );

    config = new Config( ui );
    connect( this->config, SIGNAL( openMainWindow() ), this, SLOT( openMainWindow() ) );
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
