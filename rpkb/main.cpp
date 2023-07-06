#include "mainwindow.h"
#include "goesudp.h"
#include "complexudp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GoesUDP server;
    ComplexUDP client;

    client.sendingData();
    //MainWindow w;
    //w.show();
    return a.exec();
}
