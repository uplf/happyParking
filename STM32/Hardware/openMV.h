#ifndef __OPENMV_H
#define __OPENMV_H

#include "comCONFgeneral.h"
#include "CONFgeneral.h"
#include "stm32f10x.h"                  // Device header
#include "detCalc.h"


#define TEST_SIG 0x01
#define TESTEND_SIG 0x02




void openMV_init();

extern uint16_t openMV1_mes,openMV2_mes;
extern int testFlag;


#endif