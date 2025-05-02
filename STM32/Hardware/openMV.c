#include "openMV.h"
#include "drive.h"



void openMV_init(){
	//��������
	USART_setMODE(USART1,115200);
	INT_setNVIC(usartINT_set(USART1),1,1,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
	USART_setMODE(USART3,115200);
	INT_setNVIC(usartINT_set(USART3),1,1,ENABLE);
	USART_Cmd(USART3,ENABLE);
}


void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//�ж��Ƿ���USART1�Ľ����¼��������ж�
	{
		//openMV1_mes = atoi((char*)(USART_ReceiveData(USART1)));				//��ȡ���ݼĴ���������ڽ��յ����ݱ���
		openMV1_mes=USART_ReceiveData(USART1);
		testFlag++;
		Serial_RxFlag = 1;										//�ý��ձ�־λ����Ϊ1
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//���USART1��RXNE��־λ
																//��ȡ���ݼĴ������Զ�����˱�־λ
																//����Ѿ���ȡ�����ݼĴ�����Ҳ���Բ�ִ�д˴���
	}
}


void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)		//�ж��Ƿ���USART3�Ľ����¼��������ж�
	{
		openMV2_mes = USART_ReceiveData(USART3);				//��ȡ���ݼĴ���������ڽ��յ����ݱ���
		testFlag++;
		Serial2_RxFlag = 1;										//�ý��ձ�־λ����Ϊ1
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);			//���USART1��RXNE��־λ
																//��ȡ���ݼĴ������Զ�����˱�־λ
																//����Ѿ���ȡ�����ݼĴ�����Ҳ���Բ�ִ�д˴���
	}
}


