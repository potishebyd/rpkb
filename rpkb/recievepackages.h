#ifndef RECIEVEPACKAGES_H
#define RECIEVEPACKAGES_H

typedef enum {
    MODE,
    LD,
    AS,
    TV,
    TPV
} complexPackageType;

// GOES modes
typedef enum {
    GOES_WAITING,
    GOES_WORK_CONTROL_U,
    GOES_WORK_CONTROL_C,
    GOES_WORK_CONTROL_A,
    GOES_PROTECT,
    GOES_CONTROL,
    GOES_XP,
    GOES_BIND,
    GOES_COMPENSATION
} goesMode;

typedef struct {
    unsigned int packageCount = 0;
    goesMode mode = GOES_WAITING;
    bool tpv = false;
    bool vu = false;
    float angleY = 0.0;
    float angleZ = 0.0;
    unsigned int speedRate = 5;
} decodedPackageMode;

// LD
typedef enum {
    SINGLE,
    FREQUENCY,
    STOP
} measureLd;

typedef enum {
    LD_BLOCK,
    LD_MEASURE,
    LD_CONTROL,
    LD_BLOCK_TH
} modeLd;

typedef enum {
    HALF,
    ONE,
    ONE_AND_HALF,
    TWO
} frequencyType;

typedef struct {
    unsigned int packageCount = 0;
    modeLd mode = LD_BLOCK;
    measureLd measure = STOP;
    frequencyType frequency = HALF;
} decodedLd;

// AS
typedef enum {
    AS_NO_COMMAND,
    AS_RESET,
    AS_CATCH
} modeAs;

typedef enum {
    TO,
    PO
} targetAs;

typedef enum {
    AK_TV,
    AK_TPV
} akAs;

typedef struct {
    unsigned int packageCount = 0;
    modeAs mode = AS_NO_COMMAND;
    targetAs target = TO;
    int pcSize = 1;
    akAs ak = AK_TV;
    bool sign = false;
    bool cross = false;
    bool pks = false;
    int akIncrease = 1;
} decodedAs;

// TV
typedef enum {
    PZ_NO_COMMAND,
    PZ_FIELD_WIDE,
    PZ_FIELD_NARROW,
    PZ_STOP
} pzCommand;

typedef enum {
    PZ_FOCUS_VALUE,
    PZ_FOCUS_SPEED
} pzFocusMode;

typedef enum {
    FOCUS_NO_COMMAND,
    FOCUS_FAR,
    FOCUS_CLOSE,
    FOCUS_STOP
} focusCommand;

typedef enum {
    FOCUS_AUTO,
    FOCUS_MANUAL
} focusState;

typedef enum {
    ANTIFOG_OFF,
    ANTIFOG_LOW,
    ANTIFOG_MID,
    ANTIFOG_HIGH
} antiFog;

typedef struct {
    unsigned int packageCount = 0;
    int pzSpeed = 3;
    int focusSpeed = 3;
    pzCommand pzCom = PZ_NO_COMMAND;
    focusCommand focusCom = FOCUS_NO_COMMAND;
    bool stopFrame = false;
    int contrast = 50;
    focusState focusSt = FOCUS_AUTO;
    bool stabilization = false;
    pzFocusMode pzM = PZ_FOCUS_VALUE;
    pzFocusMode focusM = PZ_FOCUS_VALUE;
    antiFog fog = ANTIFOG_OFF;
    bool highSensivity = false;
    bool reset = false;
    float viewField = 0.0;
    unsigned int focus = 0;
} decodedTv;

// TPV
typedef enum {
    IMG_NO_IMPROVE,
    IMG_DDE,
    IMG_ZONE_ARU
} imageQuality;

typedef enum {
    CALIBRATION_OFF,
    CALIBRATION_BACKGROUND,
    CALIBRATION_FOCUS,
    CALIBRATION_ROLLER
} calibrationMode;

typedef enum {
    INVERSION_POSITIVE,
    INVERSION_NEGATIVE
} inversionMode;

typedef struct {
    unsigned int packageCount = 0;
    pzCommand pzCom = PZ_NO_COMMAND;
    focusCommand focusCom = FOCUS_NO_COMMAND;
    int pzSpeed = 3;
    int focusSpeed = 3;
    imageQuality img = IMG_NO_IMPROVE;
    calibrationMode calibration = CALIBRATION_OFF;
    bool restart = false;
    pzFocusMode pzFM = PZ_FOCUS_VALUE;
    focusState focusSt = FOCUS_AUTO;
    inversionMode inversion = INVERSION_POSITIVE;
    bool ready = false;
    bool reset = false;
    float viewField = 0.0;
    unsigned int focus = 0.0;
} decodedTpv;

#endif // RECIEVEPACKAGES_H
