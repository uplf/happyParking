#include "openMV.h"



void openMV_init(){
	//��������
	USART_setMODE(USART1,19200);
	INT_setNVIC(usartINT_set(USART1),1,1,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
	USART_setMODE(USART2,19200);
	INT_setNVIC(usartINT_set(USART2),1,1,ENABLE);
	USART_Cmd(USART2,ENABLE);
}



void USART1_IRQHandler(void)
{

	static uint8_t RxState = 0;		//�����ʾ��ǰ״̬��״̬�ľ�̬����
	static uint8_t pRxPacket = 0;	//�����ʾ��ǰ��������λ�õľ�̬����
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//�ж��Ƿ���USART1�Ľ����¼��������ж�
	{

		uint8_t RxData = USART_ReceiveData(USART1);				//��ȡ���ݼĴ���������ڽ��յ����ݱ���
		openMV1_mes=RxData;
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//�����־λ

	}
}
void USART2_IRQHandler(void)
{

	static uint8_t RxState = 0;		//�����ʾ��ǰ״̬��״̬�ľ�̬����
	static uint8_t pRxPacket = 0;	//�����ʾ��ǰ��������λ�õľ�̬����
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//�ж��Ƿ���USART1�Ľ����¼��������ж�
	{

		uint8_t RxData = USART_ReceiveData(USART1);				//��ȡ���ݼĴ���������ڽ��յ����ݱ���
		openMV2_mes=RxData;
		Serial2_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//�����־λ

	}
}
