#ifndef SENDPACKAGES_H
#define SENDPACKAGES_H

#define PACKAGE_MODE_CODE 0x10111213
#define PACKAGE_LD_CODE 0x20212223
#define PACKAGE_AS_CODE 0x30313233
#define PACKAGE_TV_CODE 0x41424344
#define PACKAGE_TPV_CODE 0x51525354

#define DEFAULT_SPEED_RATE 0x01400000
//0000 0001 0100 0000 0000 0000 0000 0000
#define DEFAULT_TV_PARAMS 0x6C003200
//0110 1100 0000 0000 0011 0010 0000 0000
#define DEFAULT_TPV_PARAMS 0x001A0000
//0000 0000 0001 1011 0000 0000 0000 0000

typedef struct {
    const unsigned int packageCode = PACKAGE_MODE_CODE;
    const int reserve1[3] = {0, 0, 0};
    unsigned int packageCount = 0;
    unsigned int mode = 0;
    unsigned int forceMask = 0;
    float angleY = 0.0;
    float angleZ = 0.0;
    const int reserve2[6] = {0, 0, 0, 0, 0, 0};
    unsigned int speedRate = DEFAULT_SPEED_RATE;
} packageMode;

typedef struct {
    const unsigned int packageCode = PACKAGE_LD_CODE;
    const int reserve1[3] = {0, 0, 0};
    unsigned int packageCount = 0;
    unsigned int mode = 0;
    unsigned int reserve2 = 0;
} packageLd;

typedef struct {
    const unsigned int packageCode = PACKAGE_AS_CODE;
    const int reserve1[3] = {0, 0, 0};
    unsigned int packageCount = 0;
    unsigned int mode = 1;
    unsigned int reserve2 = 0;
    unsigned int pcSize = 0;
    unsigned int extraParams = 0;
    const int reserve3[7] = {0, 0, 0, 0, 0, 0, 0};
} packageAs;

typedef struct {
    const unsigned int packageCode = PACKAGE_TV_CODE;
    const int reserve1[3] = {0, 0, 0};
    unsigned int packageCount = 0;
    unsigned int extraParams = DEFAULT_TV_PARAMS;
    float viewFiled = 0.0;
    unsigned int focus = 0;
} packageTv;

typedef struct {
    const unsigned int packageCode = PACKAGE_TPV_CODE;
    const int reserve1[3] = {0, 0, 0};
    unsigned int packageCount = 0;
    unsigned int extraParams = DEFAULT_TPV_PARAMS;
    float viewField = 0.0;
    unsigned int focus = 0;
} packageTpv;

#endif // SENDPACKAGES_H
