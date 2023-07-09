#include "goesudp.h"


#include "sendpackages.h"
#include "recievepackages.h"

GoesUDP::GoesUDP(QObject *parent)
    : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readingData()));
}

void GoesUDP::readingData()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);

    data_t* a = reinterpret_cast<data_t*>(buffer.data());

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: model -" << a->model << ", id -" << a->id;

//    packageMode mode;
//    int temp = PACKAGE_MODE_CODE;
//    qDebug() << mode.packageCode;
//    qDebug() << temp;
//    qDebug() << mode.packageCount;
//    mode.packageCount = 10;
//    qDebug() << mode.packageCount;
//    qDebug() << sizeof(packageMode);
    decodedPackageMode p;
    qDebug() << p.mode;
}
