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

private:
    Ui::configWindow *ui;
    MainWindow *w;
    Config *config;

private slots:
    void openMainWindow();
};

#endif // CONFIGWINDOW_H
