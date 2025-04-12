#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"                  // Device header

extern int status;
extern int16_t Encoder_Count;	
extern FunctionalState OPT_MODE;

void Key_Init(void);
void Opt_Cmd(FunctionalState);
uint8_t Key_GetNum(void);

void Encoder_Init(void);


#endif
