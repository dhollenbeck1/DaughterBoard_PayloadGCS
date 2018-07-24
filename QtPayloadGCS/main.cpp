#include "mainwindow.h"
#include "configwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    configWindow cw;
    cw.show();

    return a.exec();
}
