#include "stm32f10x.h"                  // Device header
#include "LED.h"

/**
  * 函    数：LED初始化
  * 参    数：无
  * 返 回 值：无
  */
void LED_Init(void)
{
	PIN_setMODE(GPIOC,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15,_OUTPUT);
	PIN_writeBIT(GPIOC,GPIO_Pin_13|GPIO_Pin_14,_HIGH);
	PIN_writeBIT(GPIOC,GPIO_Pin_15,_LOW);
}
void BUZZER_ON(void){
	PIN_writeBIT(GPIOC,GPIO_Pin_14,_LOW);
}
void BUZZER_OFF(void){
	PIN_writeBIT(GPIOC,GPIO_Pin_14,_HIGH);
}
