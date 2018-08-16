#include "mainwindow.h"
#include "configwindow.h"
#include "communicationerror.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Serial_Port serial( "/dev/ttyUSB0", 38400 );
    CommunicationError ew;
    configWindow cw;
    if( serial.start() != EXIT_SUCCESS ) {
        ew.show();
    } else {
        cw.init( &serial );
        cw.show();
    }

    return a.exec();
}
