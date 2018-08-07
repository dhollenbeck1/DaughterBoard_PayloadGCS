#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include "mainwindow.h"
#include "ui_configwindow.h"
#include "serialport.h"
#include "config.h"


namespace Ui {
class configWindow;
}

class configWindow : public QDialog
{
    Q_OBJECT

public:
    explicit configWindow(QWidget *parent = nullptr);
    ~configWindow();
    void init( Serial_Port *_serial );

private slots:
    void openMainWindow();
    void closeConfigWindow();

private:
    Ui::configWindow *ui;
    MainWindow *w;
    Config *config;
    Serial_Port *serial;
};


#endif // CONFIGWINDOW_H
