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
	//MPU6050_Init();		//MPU6050初始化
	//MPU6050_DMP_Init();
	PIDgroupInit();
	intInit();
	LED_Init();
	openMV_init();
	//W25Q64_Init();

}


float Pitch,Roll,Yaw;								//俯仰角默认跟中值一样，翻滚角，偏航角
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
		 openMVTest();
			/*
			 drive_setDir(0);
 			 SERIAL_sendBYTE(USART1,1);
					OLED_ShowNum(1,1,1,2);
			 while(!Key_GetNum()){}
					OLED_ShowNum(1,1,2,2);
			 SERIAL_sendBYTE(USART3,1);
			 linePatrol(1,100);//openMV1巡线，直到收到2的信号：1
				 OLED_ShowNum(1,1,3,2);
			 drive_setORI(0);
			 //阶段2，初次入库
			 SERIAL_sendBYTE(USART3,4);
			 drive_setDir(3);
			 drive_setORI(-5);
			 while(openMV2_mes!=4){}
				 OLED_ShowNum(1,1,4,2);
			 //阶段3，回正
			 drive_setORI(0);
			 drive_setDir(0);
			 drive_setORI(-5);
			 Delay_ms(1000);
				 
			 //小车暂停
			 //阶段4
			 drive_setORI(0);
			 BUZZER_ON();//undefined
			 Delay_ms(1000);
			 BUZZER_OFF();
				
			 //车头摆正的出库阶段1
			 //阶段5
				 
			 SERIAL_sendBYTE(USART3,5);
			 drive_setDir(0);
			 drive_setORI(5);
				 OLED_ShowNum(1,1,5,2);
			 while(openMV2_mes!=5){};
				 OLED_ShowNum(1,1,6,2);
			 drive_setORI(0);
				 
			 //舵机旋转角度的出库阶段2，先使能openmv1，再延迟数据的接收
			 //阶段6
			 SERIAL_sendBYTE(USART1,1);
			 openMV1_mes=0;
			 drive_setDir(3);
			 drive_setORI(5);
			 Delay_ms(1000);
				 OLED_ShowNum(1,1,7,2);
			 while(!openMV1_mes){}
				 OLED_ShowNum(1,1,8,2);
			 
			 //出库车身摆正，继续巡线，并使能openmv2
			 //阶段7
			 SERIAL_sendBYTE(USART3,3);
			 linePatrol(1,100);
			 
			 
			 
			 //---------------------------------------------
			 //侧方停车逻辑
			 //阶段2-1 继续巡线，直到收到2的信号：1
			 SERIAL_sendBYTE(USART1,1);
			 while(!Key_GetNum()){}
			 SERIAL_sendBYTE(USART3,1);
			 //舵机回正
			 drive_setORI(0);
			 
			 //阶段2-2，初次入库
			 SERIAL_sendBYTE(USART3,6);//openmv2的模式需要测距功能，用于为舵机左打提供信号
			 drive_setDir(3);
			 drive_setORI(-5);
				 OLED_ShowNum(1,1,9,2);
			 while(openMV2_mes!=6){}
				 OLED_ShowNum(1,1,10,2);
			 //阶段2-3，舵机左打
			 drive_setORI(-5);
			 drive_setDir(3);
			 Delay_ms(1000);
			 drive_setORI(0);//电机停
			
			 //阶段2-4
			 drive_setORI(0);
			 BUZZER_ON();//undefined
			 Delay_ms(1000);
			 BUZZER_OFF();
				
			 //车头的出库阶段1
			 //阶段2-5
				 
			 SERIAL_sendBYTE(USART3,7);
			 drive_setDir(0);
			 drive_setORI(5);
				 OLED_ShowNum(1,1,11,2);
			 while(openMV2_mes!=7){};
				 OLED_ShowNum(1,1,12,2);
			 drive_setORI(0);
				 
			 //舵机旋转角度的出库阶段2，先使能openmv1，再延迟数据的接收
			 //阶段2-6
			 SERIAL_sendBYTE(USART1,1);
			 openMV1_mes=0;
			 drive_setDir(3);
			 drive_setORI(5);
			 Delay_ms(1000);
			 while(!openMV1_mes){}
			 
			 //出库车身摆正，继续巡线，并使能openmv2
			 //阶段7
			 SERIAL_sendBYTE(USART3,3);
			 linePatrol(1,100);
			 
		
		
		//出库阶段1，直行出库
		SERIAL_sendBYTE(USART3,0xFF);
		drive_setDir(0);
		drive_setORI(5);
		
				 
		//舵机旋转角度的出库阶段2，先使能openmv1，再延迟数据的接收
		//阶段6
		SERIAL_sendBYTE(USART1,1);
		openMV1_mes=0;
		drive_setDir(30);
		drive_setORI(5);
		Delay_ms(1000);
		OLED_ShowNum(1,1,13,2);
		while(!openMV1_mes){}
			OLED_ShowNum(1,1,14,2);
			 
		//出库车身摆正，继续巡线，并使能openmv2
		//阶段7
		SERIAL_sendBYTE(USART3,3);
			OLED_ShowNum(1,1,15,2);
		linePatrol(1,100);
		*/
	}
	//openMVTest();
}




void resetStartAngle(){

		TIM_Cmd(TIM3,DISABLE);

	//角度PID

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




