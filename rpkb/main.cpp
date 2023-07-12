#include "mainwindow.h"
#include "goesudp.h"
#include "complexudp.h"
#include "converter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.show();

    GoesUDP server;
    ComplexUDP client;

    QByteArray data = w.getFormData();
    client.sendingData(data);

    return a.exec();
}
