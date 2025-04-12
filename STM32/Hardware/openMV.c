#include "openMV.h"



void openMV_init(){
	//串口配置
	USART_setMODE(USART1,19200);
	INT_setNVIC(usartINT_set(USART1),1,1,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
	USART_setMODE(USART2,19200);
	INT_setNVIC(usartINT_set(USART2),1,1,ENABLE);
	USART_Cmd(USART2,ENABLE);
}



void USART1_IRQHandler(void)
{

	static uint8_t RxState = 0;		//定义表示当前状态机状态的静态变量
	static uint8_t pRxPacket = 0;	//定义表示当前接收数据位置的静态变量
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{

		uint8_t RxData = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量
		openMV1_mes=RxData;
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//清除标志位

	}
}
void USART2_IRQHandler(void)
{

	static uint8_t RxState = 0;		//定义表示当前状态机状态的静态变量
	static uint8_t pRxPacket = 0;	//定义表示当前接收数据位置的静态变量
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{

		uint8_t RxData = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量
		openMV2_mes=RxData;
		Serial2_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//清除标志位

	}
}
