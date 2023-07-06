#include "complexudp.h"

ComplexUDP::ComplexUDP(QObject *parent)
    : QObject(parent)
{
    socket = new QUdpSocket(this);
}

void ComplexUDP::sendingData(QByteArray &data)
{
    socket->writeDatagram(data, QHostAddress::LocalHost, 1234);
}
