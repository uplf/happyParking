#ifndef __HW_CONF_GENERAL_H
#define __HW_CONF_GENERAL_H

#include "stm32f10x.h"                  // Device header
#include "userSetup.h"
#include "CONFgeneral.h"
#include "Delay.h"
#include "comCONFgeneral.h"


//IIC source
void I2C_writeREG(IIC_group g,uint8_t slaveADDR, uint8_t regADDR,uint8_t data);//δ����
uint8_t readREG(IIC_group g,uint8_t slaveADDR,uint8_t regADDR);//δ����

//���ڵ��Է���
void USARTdebug_init();



#endif
