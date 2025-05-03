#ifndef __DRIVE_H
#define __DRIVE_H

#include "stm32f10x.h"                  // Device header
#include "CONFgeneral.h"
#include "userSetup.h"

#define _ENABLE 1
#define _DISABLE 0

void drive_init(void);
//<following>����ǰ��ת
void drive_setORI(short);//0-stop 1~5forwards -1~-5backwards
void drive_setDirPWM2(int16_t);
void drive_setDir(int16_t);//scope:-50~50


void drive_setPWM3(int16_t);
void drive_setPWM4(int16_t);
//<following>��������ת����
void drive_invPWM3(int8_t);
void drive_invPWM4(int8_t);
//ͬʱ����
void drive_setPWM34(int16_t,int16_t);

void PWM_Init(void);
void PWM_SetCompare2(uint16_t Compare);

#endif
