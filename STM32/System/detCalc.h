#ifndef __DETCALC_H
#define __DETCALC_H
#include "stm32f10x.h"                  // Device header
#include "userSetup.h"
#include "openMV.h" 
#include "drive.h" 
#include "OLED.h" 

typedef struct{
	float P;
	float I;
	float D;
	
	float LastError;
	float PrevError;
	float IntegralError;
	
	float target;
	float current;
	int8_t circleCalc;
}PIDgroup;

void pidCalc(PIDgroup*,int16_t*);
void PIDgroupInit(void);
//distCal
extern int16_t openMV1_dist;
#define distCal() openMV1_dist=openMV1_mes
//void CirCal
void CirCal(int16_t *);
void CirCalF(float *);
void linePatrol(uint8_t endFlag,uint8_t dist);
void linePatrol22(uint8_t dist);


extern PIDgroup UPPID;


#endif
