#ifndef RECORDEDPLOT_H
#define RECORDEDPLOT_H

#include <QObject>
#include <QDebug>
#include <QMainWindow>
#include <iostream>
#include <QTextStream>
#include <QFile>
#include "ui_mainwindow.h"


class RecordedPlot : public QObject
{
    Q_OBJECT

public:
    RecordedPlot();
    RecordedPlot( QMainWindow *_mainWindow, Ui::MainWindow *ui );
    ~RecordedPlot();

private slots:
    void loadFromFile();
    void plotData();
    void loadData();

private:
    void config();
    void initData();
    void plotLidar();
    void plotPyranometer();
    void plotWindAngle();
    void plotWindSpeed();
    void plotTemperature();
    void plotMethane();
    void plotEthane();

    QMainWindow *mainWindow;
    Ui::MainWindow *ui;
    QVector<double> xLidar, yLidar, xWindSpeed, yWindSpeed,
                    xWindAngle, yWindAngle, xTemperature, yTemperature,
                    xPyranometer, yPyranometer, xMethane, yMethane,
                    xEthane, yEthane;
};

#endif // RECORDEDPLOT_H
