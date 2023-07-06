#include "complexudp.h"

ComplexUDP::ComplexUDP(QObject *parent)
    : QObject(parent)
{
    socket = new QUdpSocket(this);
}

void ComplexUDP::sendingData()
{
    QByteArray Data;
    Data.append("Hello from UDP");

    // Sends the datagram datagram
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
    //                      const QHostAddress & host, quint16 port)
    socket->writeDatagram(Data, QHostAddress::LocalHost, 1234);
}
