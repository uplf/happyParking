#include "userSetup.h"
#include "detCalc.h"
#include "openMV.h"
#include "happyTest.h"


int16_t SpeedR=BASIC_SPEEDRF;
int16_t SpeedL=BASIC_SPEEDLF;



uint16_t openMV1_mes=0;
int16_t openMV1_dist=0;
uint16_t openMV2_mes=0;

int16_t UPLF_DIR=0;


int testFlag=0;

PIDgroup UPPID;

int8_t openMV1Status;
