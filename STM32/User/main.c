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
			 SERIAL_sendBYTE(USART3,2);
			 drive_setDir(47);//需要调试
			 drive_setORI(-4);
			 while(openMV2_mes!=2){}
				 OLED_ShowNum(1,1,4,2);
			 //阶段3，回正
			 drive_setORI(0);
			 drive_setDir(0);
			 drive_setORI(-5);
			 Delay_ms(1000);			//需要调
				 
			 //小车暂停
			 //阶段4
			 drive_setORI(0);
			 BUZZER_ON();//undefined
			 Delay_ms(1000);
			 BUZZER_OFF();
			 Delay_ms(4000);
				 
			 //车头摆正的出库阶段1
			 //阶段5
				 
			 SERIAL_sendBYTE(USART3,2);
			 drive_setDir(0);
			 drive_setORI(5);
				 OLED_ShowNum(1,1,5,2);
			 while(openMV2_mes!=2){};
				 OLED_ShowNum(1,1,6,2);
			 //drive_setORI(0);
				 
			 //舵机旋转角度的出库阶段2，先使能openmv1，再延迟数据的接收
			 //阶段6
			 SERIAL_sendBYTE(USART1,1);
			 openMV1_mes=0;
			 drive_setDir(47);
			 drive_setORI(5);
			 Delay_ms(1000);				//需要调
				 OLED_ShowNum(1,1,7,2);
			 while(!openMV1_mes){}
				 OLED_ShowNum(1,1,8,2);
			 
			 //出库车身摆正，继续巡线，并使能openmv2
			 //阶段7
			 SERIAL_sendBYTE(USART3,3);
			 linePatrol(1,100);
			 
			 /*
			 
			 //---------------------------------------------
			 //侧方停车逻辑
			 //阶段2-1 继续巡线，直到收到2的信号：1
			 SERIAL_sendBYTE(USART1,1);		//可视为分段测试，再次给openmv1发送1使其巡线
			 while(!Key_GetNum()){}			//按下按钮才运行openmv2的模式
			 SERIAL_sendBYTE(USART3,3);		//模式3为数侧方库边数
			 
			 
			 //此3行代码与上重复，可注释掉
				 
			 //舵机回正
			 drive_setORI(0);
			 
			 //阶段2-2，初次入库
			 SERIAL_sendBYTE(USART3,6);//openmv2的模式需要测距功能，用于为舵机左打提供信号
			 drive_setDir(30);		   //初次倒库的角度2，需调节
			 drive_setORI(-5);
				 OLED_ShowNum(1,1,9,2);
			 while(openMV2_mes!=2){}	//直到openmv2识别到方块，执行舵机的第二条指令
				 OLED_ShowNum(1,1,10,2);
			 //阶段2-3，舵机左打
			 drive_setORI(-5);
			 drive_setDir(-35);         //舵机的测试角度2，需调节
			 Delay_ms(1000);			//倒车方式2的倒车时间，需测量
			 drive_setORI(0);//电机停
			
			 //阶段2-4
			 drive_setORI(0);
			 BUZZER_ON();//undefined
			 Delay_ms(1000);
			 BUZZER_OFF();
			 Delay_ms(4000);			//停车入库，蜂鸣器响1秒，停5秒
			 
			 //车头的出库阶段1
			 //阶段2-5
				 
			 SERIAL_sendBYTE(USART3,2);		//openmv2的模式设置为模式2，用于识别色块
			 drive_setDir(-35);				//舵机出库角度1，需测试，与入库角度2相同
			 drive_setORI(5);				
				 OLED_ShowNum(1,1,11,2);
			 while(openMV2_mes!=7){};		//直到识别到色块，进行角度2的调节
				 OLED_ShowNum(1,1,12,2);
			 //drive_setORI(0);
				 
			 //舵机旋转角度的出库阶段2，先使能openmv1，再延迟数据的接收
			 //阶段2-6
			 SERIAL_sendBYTE(USART1,1);     //使能openmv1，使其巡线
			 openMV1_mes=0;						
			 drive_setDir(3);				//出库角度2，需测量，与入库角度1相同
			 drive_setORI(5);				
			 Delay_ms(1000);				//出库角度为角度2的时候的运行时间，需测量
			 while(!openMV1_mes){}			//直到识别到线，跳出循环执行pid计算
			 
			 //出库车身摆正，继续巡线，并使能openmv2
			 //阶段7
			 SERIAL_sendBYTE(USART3,3);		//模式3为继续计数
			 linePatrol(1,100);				//继续巡线
			 
			 */
			 
			 
			 
		//可以不管以下代码------------------------------
		/*
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
		//---------------------------------------------------------
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




