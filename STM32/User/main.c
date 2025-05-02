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
	//MPU6050_Init();		//MPU6050³õÊ¼»¯
	//MPU6050_DMP_Init();
	PIDgroupInit();
	intInit();
	LED_Init();
	openMV_init();
	//W25Q64_Init();

}


float Pitch,Roll,Yaw;								//¸©Ñö½ÇÄ¬ÈÏ¸úÖÐÖµÒ»Ñù£¬·­¹ö½Ç£¬Æ«º½½Ç
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
		/*
		ServoScope();
		drive_setDir(0); 
		Delay_ms(1000);
		drive_setDir(50); 
		Delay_ms(1000);
		drive_setDir(-50);
		Delay_ms(1000); */
		Delay_ms(50);
		Delay_ms(UPSampleRate);
		linepatrol_openmv1();
		
		checkStopFromOpenMV2();
		
		

	}
	//openMVTest();
}




void resetStartAngle(){

		TIM_Cmd(TIM3,DISABLE);

	//½Ç¶ÈPID

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




