#ifndef GOESUDP_H
#define GOESUDP_H

#include <QObject>
#include <QUdpSocket>
#include "converter.h"


class GoesUDP : public QObject
{
    Q_OBJECT
public:
    explicit GoesUDP(QObject *parent = 0);
signals:

public slots:
    void readingData();

private:
    QUdpSocket *socket;
    Converter *converter = new Converter();

};


#endif // GOESUDP_H
