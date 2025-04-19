#include "openMV.h"



void openMV_init(){
	//串口配置
	USART_setMODE(USART1,115200);
	INT_setNVIC(usartINT_set(USART1),1,1,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
	USART_setMODE(USART2,115200);
	INT_setNVIC(usartINT_set(USART2),1,2,ENABLE);
	USART_Cmd(USART2,ENABLE);
}






void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{
		openMV1_mes = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量
		testFlag++;
		Serial_RxFlag = 1;										//置接收标志位变量为1
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//清除USART1的RXNE标志位
																//读取数据寄存器会自动清除此标志位
																//如果已经读取了数据寄存器，也可以不执行此代码
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


