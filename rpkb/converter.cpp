#include "converter.h"

Converter::Converter()
{

}

QByteArray Converter::convertPackageModeToQByteArray(packageMode& st)
{
    QByteArray data(reinterpret_cast<const char*>(&st), sizeof(packageMode));

    return data;
}

QByteArray Converter::convertPackageLdToQByteArray(packageLd& st)
{
    QByteArray data(reinterpret_cast<const char*>(&st), sizeof(packageLd));

    return data;
}

QByteArray Converter::convertPackageAsToQByteArray(packageAs& st)
{
    QByteArray data(reinterpret_cast<const char*>(&st), sizeof(packageAs));

    return data;
}

QByteArray Converter::convertPackageTvToQByteArray(packageTv& st)
{
    QByteArray data(reinterpret_cast<const char*>(&st), sizeof(packageTv));

    return data;
}

QByteArray Converter::convertPackageTpvToQByteArray(packageTpv& st)
{
    QByteArray data(reinterpret_cast<const char*>(&st), sizeof(packageTpv));

    return data;
}

complexPackageType Converter::type(QByteArray& byteArray)
{
    // надо проверить возвращает ли size такой же размер, как и размер структуры
    switch (byteArray.size()) {
    case sizeof(packageLd):
        return LD;
    case sizeof(packageTv):
    {
        packageTv* tmp = reinterpret_cast<packageTv*>(byteArray.data()); // заменить на приватные методы
        if (tmp->packageCode == PACKAGE_TPV_CODE)
            return TPV;
        return TV;
    }
    case sizeof(packageAs):
    {
        packageMode* tmp = reinterpret_cast<packageMode*>(byteArray.data()); // заменить на приватные методы
        if (tmp->packageCode == PACKAGE_MODE_CODE)
            return MODE;
    }
    default:
        return AS;
    }
}

decodedPackageMode Converter::convertByteArrayToDecodedPackageMode(QByteArray& byteArray)
{
    decodedPackageMode result;

    packageMode* tmp = reinterpret_cast<packageMode*>(byteArray.data()); // заменить на приватные методы

    switch (tmp->mode)
    {
    case 0:
        result.mode = GOES_WAITING;
    case 16:
        result.mode = GOES_WORK_CONTROL_U;
    case 17:
        result.mode = GOES_WORK_CONTROL_C;
    case 18:
        result.mode = GOES_WORK_CONTROL_A;
    case 32:
        result.mode = GOES_PROTECT;
    case 40:
        result.mode = GOES_CONTROL;
    case 64:
        result.mode = GOES_XP;
    case 65:
        result.mode = GOES_BIND;
    case 127:
        result.mode = GOES_COMPENSATION;
    }

    unsigned int first_bit = (tmp->forceMask >> 0) & 1;
    unsigned int third_bit = (tmp->forceMask  >> 2) & 1;

    if (first_bit == 1)
        result.tpv = true;

    if (third_bit == 1)
        result.vu = true;

    result.packageCount = tmp->packageCount;
    result.angleY = tmp->angleY;
    result.angleZ = tmp->angleZ;
    result.speedRate = tmp->speedRate;

    return result;
}



decodedLd Converter::convertByteArrayToDecodedLd(QByteArray& byteArray)
{
    decodedLd result;

    packageLd* tmp = reinterpret_cast<packageLd*>(byteArray.data());

    result.packageCount = tmp->packageCount;

    switch (tmp->mode)
    {
    case 18:
        result.measure = FREQUENCY;
    case 34:
        result.measure = FREQUENCY;
    case 50:
        result.measure = FREQUENCY;
    case 66:
        result.measure = FREQUENCY;
    case 0:
        result.measure = STOP;
    case 1:
        result.measure = SINGLE;
    }

    switch (tmp->mode)
    {
    case 0:
        result.mode = LD_BLOCK;
    case 1:
        result.mode = LD_MEASURE;
    case 2:
        result.mode = LD_CONTROL;
    case 6:
        result.mode = LD_BLOCK_TH;
    }


}

decodedAs Converter::convertByteArrayToDecodedAs(QByteArray& byteArray)
{
    decodedAs result;

    packageAs* tmp = reinterpret_cast<packageAs*>(byteArray.data());

    result.packageCount = tmp->packageCount;
    result.pcSize = tmp->pcSize;
        
    switch (tmp->mode)
    {
    case 0:
        result.mode = AS_NO_COMMAND;
    case 1:
        result.mode = AS_RESET;
    case 2:
        result.mode = AS_CATCH;
    }

    if (((tmp->extraParams >> 23) & 1) == 1)
        result.pks = true;

    if (((tmp->extraParams >> 20) & 1) == 1)
        result.cross = true;

    if (((tmp->extraParams >> 9) & 1) == 1)
        result.sign = true;

    if (((tmp->extraParams >> 0) & 1) == 1)
        result.ak = AK_TV;

    if (((tmp->extraParams >> 1) & 1) == 1)
        result.ak = AK_TPV;

    
}

decodedTv Converter::convertByteArrayToDecodedTv(QByteArray& byteArray)
{
    decodedTv result;

    packageTv* tmp = reinterpret_cast<packageTv*>(byteArray.data());
    
    result.packageCount = tmp->packageCount;
    result.viewField = tmp->viewFiled;
    result.focus = tmp->focus;




}

decodedTpv Converter::convertByteArrayToDecodedTpv(QByteArray& byteArray)
{
    decodedTpv result;

    packageTpv* tmp = reinterpret_cast<packageTpv*>(byteArray.data());

    result.packageCount = tmp->packageCount;
    result.viewField = tmp->viewField;
    result.focus = tmp->focus;
}
