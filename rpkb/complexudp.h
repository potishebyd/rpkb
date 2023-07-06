#ifndef COMPLEXUDP_H
#define COMPLEXUDP_H


#include <QObject>
#include <QUdpSocket>


class ComplexUDP : public QObject
{
public:
    Q_OBJECT
public:
    explicit ComplexUDP(QObject *parent = 0);
    void sendingData();
signals:

public slots:

private:
    QUdpSocket *socket;
};

#endif // COMPLEXUDP_H
