#include "userSetup.h"
#include "detCalc.h"

int8_t GREY_INDEX,GREY_ISINDEX=0;
int16_t SpeedR=BASIC_SPEEDRF;
int16_t SpeedL=BASIC_SPEEDLF;

PIDgroup GreyLeft;
PIDgroup GreyRight;

PIDangle AngleLeft;
PIDangle AngleRight;


