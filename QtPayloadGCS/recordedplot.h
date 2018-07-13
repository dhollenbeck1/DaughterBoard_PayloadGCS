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
    void plotLidar();
    void plotPyranometer();
    void plotWind();

private:
    void config();
    void initData();
    QMainWindow *mainWindow;
    Ui::MainWindow *ui;
    QVector<double> xLidar, yLidar, xWind, yWind, xPyranometer, yPyranometer;
};

#endif // RECORDEDPLOT_H
