#include "recordedplot.h"
#include <QFileDialog>

RecordedPlot::RecordedPlot()
{
}

RecordedPlot::RecordedPlot( QMainWindow *_mainWindow ) :
    mainWindow( _mainWindow )
{
}

RecordedPlot::~RecordedPlot()
{
}

void RecordedPlot::loadFromFile() {
    QString fileName = QFileDialog::getOpenFileName(mainWindow,
           tr("Open data log file"), "",
           tr("Data log file (*.csv);;All Files (*)"));
}

/*void read(QString filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly |
                  QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
        return;
    }

    QTextStream in(&file);
    QString myText = in.readAll();
    qDebug() << myText;

    file.close();
}
*/
