#include "goesudp.h"
#include "datastruct.h"

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
}
