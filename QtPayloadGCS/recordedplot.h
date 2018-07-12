#ifndef RECORDEDPLOT_H
#define RECORDEDPLOT_H

#include <QObject>
#include <QMainWindow>


class RecordedPlot : public QObject
{
    Q_OBJECT

public:
    RecordedPlot();
    RecordedPlot( QMainWindow *_mainWindow );
    ~RecordedPlot();

private slots:
    void loadFromFile();

private:
    QMainWindow *mainWindow;
};

#endif // RECORDEDPLOT_H
