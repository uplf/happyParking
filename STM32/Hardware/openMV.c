#include "openMV.h"
#include "drive.h"



void openMV_init(){
	//串口配置
	USART_setMODE(USART1,115200);
	INT_setNVIC(usartINT_set(USART1),1,1,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
	USART_setMODE(USART3,115200);
	INT_setNVIC(usartINT_set(USART3),1,1,ENABLE);
	USART_Cmd(USART3,ENABLE);
}


void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{
		//openMV1_mes = atoi((char*)(USART_ReceiveData(USART1)));				//读取数据寄存器，存放在接收的数据变量
		openMV1_mes=USART_ReceiveData(USART1);
		testFlag++;
		Serial_RxFlag = 1;										//置接收标志位变量为1
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//清除USART1的RXNE标志位
																//读取数据寄存器会自动清除此标志位
																//如果已经读取了数据寄存器，也可以不执行此代码
	}
}


void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)		//判断是否是USART3的接收事件触发的中断
	{
		openMV2_mes = USART_ReceiveData(USART3);				//读取数据寄存器，存放在接收的数据变量
		testFlag++;
		Serial2_RxFlag = 1;										//置接收标志位变量为1
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);			//清除USART1的RXNE标志位
																//读取数据寄存器会自动清除此标志位
																//如果已经读取了数据寄存器，也可以不执行此代码
	}
}


