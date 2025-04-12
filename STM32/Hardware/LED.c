#include "stm32f10x.h"                  // Device header
#include "LED.h"

/**
  * 函    数：LED初始化
  * 参    数：无
  * 返 回 值：无
  */
void LED_Init(void)
{
	PIN_setMODE(GPIOC,GPIO_Pin_13|GPIO_Pin_14,_OUTPUT);
	PIN_writeBIT(GPIOC,GPIO_Pin_13|GPIO_Pin_14,_LOW);
}

void LED1_ON(void){PIN_writeBIT(GPIOC,GPIO_Pin_13,_HIGH);}
void LED1_OFF(void){PIN_writeBIT(GPIOC,GPIO_Pin_13,_LOW);}
void LED1_Turn(void){PIN_writeBIT(GPIOC,GPIO_Pin_13,!PIN_readBIT(GPIOC,GPIO_Pin_13));}
void LED2_ON(void){PIN_writeBIT(GPIOC,GPIO_Pin_14,_HIGH);}
void LED2_OFF(void){PIN_writeBIT(GPIOC,GPIO_Pin_14,_LOW);}
void LED2_Turn(void){PIN_writeBIT(GPIOC,GPIO_Pin_14,!PIN_readBIT(GPIOC,GPIO_Pin_14));}