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

    unsigned int extraParams = 123; // Пример значения extraParams

        // Используем побитовое И (&) с маской для получения значения из 0-1 разрядов.
   unsigned int value = extraParams  & 0x00000000 ;

   std::cout << "Значение: " << value << std::endl;


    return a.exec();
}
