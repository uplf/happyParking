#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CONFgeneral.h"
#include "comCONFgeneral.h"
#include "drive.h"
#include "key.h"
#include "map.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "userSetup.h"
#include "detCalc.h"
#include "Interrupt.h"
#include "LED.h"
#include "happyTest.h"
#include "openMV.h"
//end of test area



void resetStartAngle();

int8_t wytest=0;

void Setup(void){
	Key_Init();
	reuse_init();
	OLED_Init();
	drive_init();
	//MPU6050_Init();		//MPU6050��ʼ��
	//MPU6050_DMP_Init();
	PIDgroupInit();
	intInit();
	LED_Init();
	openMV_init();
	//W25Q64_Init();

}


float Pitch,Roll,Yaw;								//������Ĭ�ϸ���ֵһ���������ǣ�ƫ����
float StartAngle;
int8_t RunMode;




int main(void)
{
	Setup();
	//openMVTest();
	drive_setDir(-11); 
	openMV1Status=1;
	SERIAL_sendBYTE(USART1,openMV1Status);
	
	while(1)
	{	
		
			
			 drive_setDir(0);
 			 SERIAL_sendBYTE(USART1,1);
					OLED_ShowNum(1,1,1,2);
			 while(!Key_GetNum()){}
					OLED_ShowNum(1,1,2,2);
			 SERIAL_sendBYTE(USART3,1);
			 linePatrol(1,100);//openMV1Ѳ�ߣ�ֱ���յ�2���źţ�1
				 OLED_ShowNum(1,1,3,2);
			 drive_setORI(0);
			 //�׶�2���������
			 SERIAL_sendBYTE(USART3,2);
			 drive_setDir(47);//��Ҫ����
			 drive_setORI(-4);
			 while(openMV2_mes!=2){}
				 OLED_ShowNum(1,1,4,2);
			 //�׶�3������
			 drive_setORI(0);
			 drive_setDir(0);
			 drive_setORI(-5);
			 Delay_ms(1000);			//��Ҫ��
				 
			 //С����ͣ
			 //�׶�4
			 drive_setORI(0);
			 BUZZER_ON();//undefined
			 Delay_ms(1000);
			 BUZZER_OFF();
			 Delay_ms(4000);
				 
			 //��ͷ�����ĳ���׶�1
			 //�׶�5
				 
			 SERIAL_sendBYTE(USART3,2);
			 drive_setDir(0);
			 drive_setORI(5);
				 OLED_ShowNum(1,1,5,2);
			 while(openMV2_mes!=2){};
				 OLED_ShowNum(1,1,6,2);
			 //drive_setORI(0);
				 
			 //�����ת�Ƕȵĳ���׶�2����ʹ��openmv1�����ӳ����ݵĽ���
			 //�׶�6
			 SERIAL_sendBYTE(USART1,1);
			 openMV1_mes=0;
			 drive_setDir(47);
			 drive_setORI(5);
			 Delay_ms(1000);				//��Ҫ��
				 OLED_ShowNum(1,1,7,2);
			 while(!openMV1_mes){}
				 OLED_ShowNum(1,1,8,2);
			 
			 //���⳵�����������Ѳ�ߣ���ʹ��openmv2
			 //�׶�7
			 SERIAL_sendBYTE(USART3,3);
			 linePatrol(1,100);
			 
			 /*
			 
			 //---------------------------------------------
			 //�෽ͣ���߼�
			 //�׶�2-1 ����Ѳ�ߣ�ֱ���յ�2���źţ�1
			 SERIAL_sendBYTE(USART1,1);		//����Ϊ�ֶβ��ԣ��ٴθ�openmv1����1ʹ��Ѳ��
			 while(!Key_GetNum()){}			//���°�ť������openmv2��ģʽ
			 SERIAL_sendBYTE(USART3,3);		//ģʽ3Ϊ���෽�����
			 
			 
			 //��3�д��������ظ�����ע�͵�
				 
			 //�������
			 drive_setORI(0);
			 
			 //�׶�2-2���������
			 SERIAL_sendBYTE(USART3,6);//openmv2��ģʽ��Ҫ��๦�ܣ�����Ϊ�������ṩ�ź�
			 drive_setDir(30);		   //���ε���ĽǶ�2�������
			 drive_setORI(-5);
				 OLED_ShowNum(1,1,9,2);
			 while(openMV2_mes!=2){}	//ֱ��openmv2ʶ�𵽷��飬ִ�ж���ĵڶ���ָ��
				 OLED_ShowNum(1,1,10,2);
			 //�׶�2-3��������
			 drive_setORI(-5);
			 drive_setDir(-35);         //����Ĳ��ԽǶ�2�������
			 Delay_ms(1000);			//������ʽ2�ĵ���ʱ�䣬�����
			 drive_setORI(0);//���ͣ
			
			 //�׶�2-4
			 drive_setORI(0);
			 BUZZER_ON();//undefined
			 Delay_ms(1000);
			 BUZZER_OFF();
			 Delay_ms(4000);			//ͣ����⣬��������1�룬ͣ5��
			 
			 //��ͷ�ĳ���׶�1
			 //�׶�2-5
				 
			 SERIAL_sendBYTE(USART3,2);		//openmv2��ģʽ����Ϊģʽ2������ʶ��ɫ��
			 drive_setDir(-35);				//�������Ƕ�1������ԣ������Ƕ�2��ͬ
			 drive_setORI(5);				
				 OLED_ShowNum(1,1,11,2);
			 while(openMV2_mes!=7){};		//ֱ��ʶ��ɫ�飬���нǶ�2�ĵ���
				 OLED_ShowNum(1,1,12,2);
			 //drive_setORI(0);
				 
			 //�����ת�Ƕȵĳ���׶�2����ʹ��openmv1�����ӳ����ݵĽ���
			 //�׶�2-6
			 SERIAL_sendBYTE(USART1,1);     //ʹ��openmv1��ʹ��Ѳ��
			 openMV1_mes=0;						
			 drive_setDir(3);				//����Ƕ�2��������������Ƕ�1��ͬ
			 drive_setORI(5);				
			 Delay_ms(1000);				//����Ƕ�Ϊ�Ƕ�2��ʱ�������ʱ�䣬�����
			 while(!openMV1_mes){}			//ֱ��ʶ���ߣ�����ѭ��ִ��pid����
			 
			 //���⳵�����������Ѳ�ߣ���ʹ��openmv2
			 //�׶�7
			 SERIAL_sendBYTE(USART3,3);		//ģʽ3Ϊ��������
			 linePatrol(1,100);				//����Ѳ��
			 
			 */
			 
			 
			 
		//���Բ������´���------------------------------
		/*
		//����׶�1��ֱ�г���
		SERIAL_sendBYTE(USART3,0xFF);
		drive_setDir(0);
		drive_setORI(5);
		
				 
		//�����ת�Ƕȵĳ���׶�2����ʹ��openmv1�����ӳ����ݵĽ���
		//�׶�6
		SERIAL_sendBYTE(USART1,1);
		openMV1_mes=0;
		drive_setDir(30);
		drive_setORI(5);
		Delay_ms(1000);
		OLED_ShowNum(1,1,13,2);
		while(!openMV1_mes){}
			OLED_ShowNum(1,1,14,2);
			 
		//���⳵�����������Ѳ�ߣ���ʹ��openmv2
		//�׶�7
		SERIAL_sendBYTE(USART3,3);
			OLED_ShowNum(1,1,15,2);
		linePatrol(1,100);
		*/
		//---------------------------------------------------------
	}
	//openMVTest();
}




void resetStartAngle(){

		TIM_Cmd(TIM3,DISABLE);

	//�Ƕ�PID

	while(!Key_GetNum())
	{
		Delay_ms(5);
		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);
		OLED_ShowSignedNum(1,1,Yaw,5);
		
	}
	StartAngle=Yaw;
	OLED_ShowChar(1,7,'+');
	MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);
	OLED_ShowSignedNum(1,1,Yaw,5);
	OLED_ShowSignedNum(2,1,StartAngle,5);
	TIM_Cmd(TIM3,ENABLE);
}




