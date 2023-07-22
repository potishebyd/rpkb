#include "goesudp.h"


#include "sendpackages.h"
#include "recievepackages.h"
#include "converter.h"

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

    complexPackageType t = converter->type(buffer);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << t;
    qDebug() << buffer.size();
}
