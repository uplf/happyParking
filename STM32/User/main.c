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


void checkStopFromOpenMV2(void) {
	  OLED_ShowNum(4,1,openMV2_mes,3);
    while (openMV2_mes == 1) {
        drive_setDir(45);   
        drive_setORI(-3);
			  openMV1Status=2;
			  SERIAL_sendBYTE(USART1,openMV1Status);
			  //Delay_ms(3000);
			  //ServoScope();
    }
}



int main(void)
{
	Setup();
	drive_setDir(-11); 
	openMV1Status=1;
	SERIAL_sendBYTE(USART1,openMV1Status);
	
	while(1){			
			 drive_setDir(0);
 			 SERIAL_sendBYTE(USART1,1);
			 while(!Key_GetNum()){}
			 SERIAL_sendBYTE(USART3,1);
			 linePatrol(1,100);//openMV1巡线，直到收到2的信号：1
			 drive_setORI(0);
			 //阶段2，初次入库
			 SERIAL_sendBYTE(USART3,0xFF);
			 drive_setDir(0xFF);
			 drive_setORI(-5);
			 while(openMV2_mes!=0xFF){}
			 //阶段3，回正
			 drive_setORI(0);
			 drive_setDir(0);
			 drive_setORI(-5);
			 Delay_ms(0xFF);
				 
			 //阶段4
			 drive_setORI(0);
			 BUZZER_ON();//undefined
			 Delay_ms(1000);
			 BUZZER_OFF();
				 
			 //阶段5
				 
			 SERIAL_sendBYTE(USART3,0xFF);
			 drive_setDir(0);
			 drive_setORI(5);
			 while(openMV2_mes!=0xFF){};
			 drive_setORI(0);
				 
			 //阶段6
			 SERIAL_sendBYTE(USART1,1);
			 openMV1_mes=0;
			 drive_setDir(0xFF);
			 drive_setORI(5);
			 Delay_ms(1000);
			 while(!openMV1_mes){}
			 //阶段7
			 SERIAL_sendBYTE(USART3,3);
			 linePatrol(1,100);
		
		
		

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




