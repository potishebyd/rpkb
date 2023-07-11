#ifndef CONVERTER_H
#define CONVERTER_H

#include <iostream>
#include "recievepackages.h"
#include "sendpackages.h"
#include <QObject>

using namespace std;

class Converter
{
public:
    Converter();

    QByteArray convertPackageModeToQByteArray(packageMode& st);

    QByteArray convertPackageLdToQByteArray(packageLd& st);

    QByteArray convertPackageAsToQByteArray(packageAs& st);

    QByteArray convertPackageTvToQByteArray(packageTv& st);

    QByteArray convertPackageTpvToQByteArray(packageTpv& st);

    decodedPackageMode convertByteArrayToDecodedPackageMode(QByteArray& byteArray);

    decodedLd convertByteArrayToDecodedLd(QByteArray& byteArray);

    decodedAs convertByteArrayToDecodedAs(QByteArray& byteArray);

    decodedTv convertByteArrayToDecodedTv(QByteArray& byteArray);

    decodedTpv convertByteArrayToDecodedTpv(QByteArray& byteArray);
};

#endif // CONVERTER_H
