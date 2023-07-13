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
        packageTv* tmp = this->convertQByteArrayToPackageTv(byteArray);
        if (tmp->packageCode == PACKAGE_TPV_CODE)
            return TPV;
        return TV;
    }
    case sizeof(packageAs):
    {
        packageMode* tmp = this->convertQByteArrayToPackageMode(byteArray);
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

    packageMode* tmp = this->convertQByteArrayToPackageMode(byteArray);

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

    packageLd* tmp = this->converQByteArrayToPackageLd(byteArray);

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

    packageAs* tmp = this->convertQByteArrayToPackageAs(byteArray);

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

    packageTv* tmp = this->convertQByteArrayToPackageTv(byteArray);
    
    result.packageCount = tmp->packageCount;
    result.viewField = tmp->viewFiled;
    result.focus = tmp->focus;

    
    unsigned int bit0 = (tmp->extraParams >> 0) & 1;
    unsigned int bit1 = (tmp->extraParams  >> 1) & 1;
    unsigned int bit2 = (tmp->extraParams  >> 2) & 1;
    result.pzSpeed = (bit0 << 2) | (bit1 << 1) | bit2;

    unsigned int bit3 = (tmp->extraParams >> 3) & 1;
    unsigned int bit4 = (tmp->extraParams >> 4) & 1;
    unsigned int bit5 = (tmp->extraParams >> 5) & 1;

    result.focusSpeed = (bit3 << 2) | (bit4 << 1) | bit5;

    unsigned int bit8 = (tmp->extraParams >> 8) & 1;
    unsigned int bit9 = (tmp->extraParams >> 9) & 1;

    switch ((bit8 << 1) | bit9)
    {
    case 0:
        result.pzCom = PZ_NO_COMMAND;
    case 1:
        result.pzCom = PZ_FIELD_WIDE;
    case 2:
        result.pzCom = PZ_FIELD_NARROW;
    case 3:
        result.pzCom = PZ_STOP;
    }

    unsigned int bit10 = (tmp->extraParams >> 10) & 1;
    unsigned int bit11 = (tmp->extraParams >> 11) & 1;

    switch ((bit10 << 1) | bit11)
    {
    case 0:
        result.focusCom = FOCUS_NO_COMMAND;
    case 1:
        result.focusCom = FOCUS_FAR;
    case 2:
        result.focusCom = FOCUS_CLOSE;
    case 3:
        result.focusCom = FOCUS_STOP;
    }

    unsigned int bit15 = (tmp->extraParams >> 15) & 1;
    if (bit15)
        result.stopFrame = true;
    else
        result.stopFrame = false;

    unsigned int bit16 = (tmp->extraParams >> 16) & 1;
    unsigned int bit17 = (tmp->extraParams >> 17) & 1;
    unsigned int bit18 = (tmp->extraParams >> 18) & 1;
    unsigned int bit19 = (tmp->extraParams >> 19) & 1;
    unsigned int bit20 = (tmp->extraParams >> 20) & 1;
    unsigned int bit21 = (tmp->extraParams >> 21) & 1;
    unsigned int bit22 = (tmp->extraParams >> 22) & 1;
    unsigned int bit23 = (tmp->extraParams >> 23) & 1;

    result.contrast = (bit16 << 7) | (bit17 << 6) | (bit18 << 5) | (bit19 << 4) | (bit20 << 3) | (bit21 << 2) | (bit22 << 1) | bit23;

    unsigned int bit24 = (tmp->extraParams >> 24) & 1;
    if (!bit24)
        result.focusSt = FOCUS_AUTO;
    else
        result.focusSt = FOCUS_MANUAL;
    
    unsigned int bit25 = (tmp->extraParams >> 25) & 1;
    if (bit25)
        result.stabilization = true;
    else 
        result.stabilization = false;

    unsigned int bit26 = (tmp->extraParams >> 26) & 1;
    if (!bit26)
        result.pzM = PZ_FOCUS_VALUE;
    else
        result.pzM = PZ_FOCUS_SPEED;

    unsigned int bit27 = (tmp->extraParams >> 27) & 1;
    if (!bit27)
        result.focusM = PZ_FOCUS_VALUE;
    else
        result.focusM = PZ_FOCUS_SPEED;

    unsigned int bit28 = (tmp->extraParams >> 28) & 1;
    unsigned int bit29 = (tmp->extraParams >> 29) & 1;

    switch ((bit28 << 1) | bit29)
    {
    case 0:
        result.fog = ANTIFOG_OFF;
    case 1:
        result.fog = ANTIFOG_LOW;
    case 2:
        result.fog = ANTIFOG_MID;
    case 3:
        result.fog = ANTIFOG_HIGH;
    }
    
    unsigned int bit30 = (tmp->extraParams >> 30) & 1;
    if (bit30)
        result.highSensivity = true;
    else 
        result.highSensivity = false;
    
    unsigned int bit31 = (tmp->extraParams >> 31) & 1;
    if (bit31)
        result.reset = true;
    else
        result.reset = false;
        

}

decodedTpv Converter::convertByteArrayToDecodedTpv(QByteArray& byteArray)
{
    decodedTpv result;

    packageTpv* tmp = this->convertQByteArrayToPackageTpv(byteArray);

    result.packageCount = tmp->packageCount;
    result.viewField = tmp->viewField;
    result.focus = tmp->focus;

    unsigned int bit6 = (tmp->extraParams >> 6) & 1;
    unsigned int bit7 = (tmp->extraParams >> 7) & 1;
    switch ((bit6 << 1) | bit7)
    {
    case 0:
        result.pzCom = PZ_NO_COMMAND;
    case 1:
        result.pzCom = PZ_FIELD_WIDE;
    case 2:
        result.pzCom = PZ_FIELD_NARROW;
    case 3:
        result.pzCom = PZ_STOP;
    }

    unsigned int bit8 = (tmp->extraParams >> 8) & 1;
    unsigned int bit9 = (tmp->extraParams >> 9) & 1;
        
    switch ((bit8 << 1) | bit9)
    {
    case 0:
        result.focusCom = FOCUS_NO_COMMAND;
    case 1:
        result.focusCom = FOCUS_FAR;
    case 2:
        result.focusCom = FOCUS_CLOSE;
    case 3:
        result.focusCom = FOCUS_STOP;
    }

    unsigned int bit10 = (tmp->extraParams >> 10) & 1;
    unsigned int bit11 = (tmp->extraParams  >> 11) & 1;
    unsigned int bit12 = (tmp->extraParams  >> 12) & 1;
    result.pzSpeed = (bit10 << 2) | (bit11 << 1) | bit12;

    unsigned int bit13 = (tmp->extraParams >> 13) & 1;
    unsigned int bit14 = (tmp->extraParams >> 14) & 1;
    unsigned int bit15 = (tmp->extraParams >> 15) & 1;
    result.focusSpeed = (bit13 << 2) | (bit14 << 1) | bit15;

    unsigned int bit16 = (tmp->extraParams >> 16) & 1;
    unsigned int bit17 = (tmp->extraParams >> 17) & 1;
    switch ((bit16 << 1) | bit17)
    {
    case 0:
        result.img = IMG_NO_IMPROVE;
    case 1:
        result.img = IMG_DDE;
    case 2:
        result.img = IMG_ZONE_ARU;
    }

    unsigned int bit18 = (tmp->extraParams >> 18) & 1;
    unsigned int bit19 = (tmp->extraParams >> 19) & 1;
    switch ((bit18 << 1) | bit19)
    {
    case 0:
        result.calibration = CALIBRATION_OFF;
    case 1:
        result.calibration = CALIBRATION_BACKGROUND;
    case 2:
        result.calibration = CALIBRATION_FOCUS;
    case 3:
        result.calibration = CALIBRATION_ROLLER;
    }

    unsigned int bit20 = (tmp->extraParams >> 20) & 1;
    if (bit20)
        result.restart = true;
    else
        result.restart = false; 

    unsigned int bit21 = (tmp->extraParams >> 21) & 1;
    if (!bit21)
        result.pzFM = PZ_FOCUS_VALUE;
    else
        result.pzFM = PZ_FOCUS_SPEED;
    
    unsigned int bit24 = (tmp->extraParams >> 24) & 1;
    if (bit24)
        result.focusSt = FOCUS_AUTO;
    else
        result.focusSt = FOCUS_MANUAL;
    
    unsigned int bit25 = (tmp->extraParams >> 25) & 1;
    if (bit25)
        result.inversion = INVERSION_NEGATIVE;
    else
        result.inversion = INVERSION_POSITIVE;

    unsigned int bit30 = (tmp->extraParams >> 30) & 1;
    if (!bit30)
        result.ready = true;
    else
        result.ready = false;

    unsigned int bit31 = (tmp->extraParams >> 31) & 1;
    if (bit31)
        result.reset = true;
    else
        result.reset = false;

   return result;
    
}

packageMode* Converter::convertQByteArrayToPackageMode(QByteArray& byteArray)
{
    packageMode* result = reinterpret_cast<packageMode*>(byteArray.data());
    return result;
}
packageLd* Converter::converQByteArrayToPackageLd(QByteArray& byteArray)
{
    packageLd* result = reinterpret_cast<packageLd*>(byteArray.data());
    return result;
}
packageAs* Converter::convertQByteArrayToPackageAs(QByteArray& byteArray)
{
    packageAs* result = reinterpret_cast<packageAs*>(byteArray.data());
    return result;
}
packageTv* Converter::convertQByteArrayToPackageTv(QByteArray& byteArray)
{
    packageTv* result = reinterpret_cast<packageTv*>(byteArray.data());
    return result;
}
packageTpv* Converter::convertQByteArrayToPackageTpv(QByteArray& byteArray)
{
    packageTpv* result = reinterpret_cast<packageTpv*>(byteArray.data());
    return result;
}
