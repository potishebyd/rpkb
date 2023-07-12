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

//    to QByteArray
    QByteArray convertPackageModeToQByteArray(packageMode& st);
    QByteArray convertPackageLdToQByteArray(packageLd& st);
    QByteArray convertPackageAsToQByteArray(packageAs& st);
    QByteArray convertPackageTvToQByteArray(packageTv& st);
    QByteArray convertPackageTpvToQByteArray(packageTpv& st);

//    checkType
    complexPackageType type(QByteArray& byteArray);

//    to ComplexPackages
    decodedPackageMode convertByteArrayToDecodedPackageMode(QByteArray& byteArray);
    decodedLd convertByteArrayToDecodedLd(QByteArray& byteArray);
    decodedAs convertByteArrayToDecodedAs(QByteArray& byteArray);
    decodedTv convertByteArrayToDecodedTv(QByteArray& byteArray);
    decodedTpv convertByteArrayToDecodedTpv(QByteArray& byteArray);


private:
    //    from QByteArray to sendpackages for each package

    packageMode* convertQByteArrayToPackageMode(QByteArray& byteArray);
    packageLd* converQByteArrayToPackageLd(QByteArray& byteArray);
    packageAs* convertQByteArrayToPackageAs(QByteArray& byteArray);
    packageTv* convertQByteArrayToPackageTv(QByteArray& byteArray);
    packageTpv* convertQByteArrayToPackageTpv(QByteArray& byteArray);

};

#endif // CONVERTER_H
