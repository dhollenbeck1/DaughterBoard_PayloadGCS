#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include "serialport.h"
#include "realtimeplots.h"
#include "recordedplot.h"
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RealTimePlots *realTimePlots;
    RecordedPlot *recordedPlot;

signals:
    void operate();

};

#endif // MAINWINDOW_H
