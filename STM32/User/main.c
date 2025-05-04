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



int8_t CHOICE;

void testUSART(){
	while(!Key_GetNum()){
		
	}
}

void Delay_line(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
		Delay_us(UPSampleRate);
	    UPPID.current=openMV1_mes;
		pidCalc(&UPPID,&UPLF_DIR);
		drive_setDir(UPLF_DIR);
	}
}



int main(void)
{
	Setup();
	
	//ServoScope();
	drive_setDir(0); 
	openMV1Status=1;
	
	//while(1){;}

	/*
	//PID testing
	drive_setORI(3);
	linePatrol22(100);
	*/
	
	//SERIAL_sendBYTE(USART1,openMV1Status);
	OLED_ShowNum(1,1,1,2);
	
	while(1)
	{	
		do{
		CHOICE=Key_GetNum();
		//if(CHOICE==2)SERIAL_sendBYTE(USART3,1);
		OLED_ShowString(2,1,"REC1:");
		OLED_ShowString(3,1,"REC2:");
		OLED_ShowNum(2,6,openMV1_mes,8);
		OLED_ShowNum(3,6,openMV2_mes,8);
		}while(CHOICE!=1);
		OLED_Clear();
		 //openMVTest();
			 
			 drive_setDir(0);
		
 			 SERIAL_sendBYTE(USART1,1);
		     OLED_ShowNum(1,1,2,2);
			 openMV1_mes=151;
		     drive_setDir(-10);
			 drive_setORI(3);
		     while(openMV1_mes>150){}
		
		
			 SERIAL_sendBYTE(USART3,1);
			 drive_setORI(3);
			 linePatrol(1,100);//openMV1巡线，直到收到2的信号：1
			 //BUZZER_ON();
		     OLED_ShowNum(3,6,openMV2_mes,8);
			 OLED_ShowNum(1,1,3,2);
			 drive_setORI(0);
				 
			 //阶段2，初次入库
			 //SERIAL_sendBYTE(USART3,2);
			 drive_setDir(43);//需要调试
			 //BUZZER_OFF();
			 drive_setORI(-4);
		     delay_ms(2600);

			 //阶段3，回正
			 drive_setORI(0);
			 drive_setDir(0);
			 drive_setORI(-5);
			 Delay_ms(900);			//需要调
				 
			 //小车暂停
			 //阶段4
			 drive_setORI(0);
			 
			 BUZZER_ON();//开蜂鸣器
		     Delay_ms(500);
		     BUZZER_OFF();
			 
			 Delay_ms(1000);
			 
			 BUZZER_ON();//undefined
		     Delay_ms(500);
		     BUZZER_OFF();

				 
			 //车头摆正的出库阶段1
			 //阶段5
				 
			 //SERIAL_sendBYTE(USART3,2);
			 drive_setDir(0);
			 drive_setORI(5);
			 OLED_ShowNum(1,1,5,2);
			 delay_ms(500);
			 //while(openMV2_mes!=2){};
				 OLED_ShowNum(1,1,6,2);
			 //drive_setORI(0);
				 
			 //舵机旋转角度的出库阶段2，先使能openmv1，再延迟数据的接收
			 //阶段6
			 SERIAL_sendBYTE(USART1,1);
			 openMV1_mes=0;
			 drive_setDir(43);
			 drive_setORI(3);
			 Delay_ms(1500);				//需要调
				 OLED_ShowNum(1,1,7,2);

			 while(!openMV1_mes){}
				 OLED_ShowNum(1,1,8,2);
			 Delay_line(1800);
				 
			 /*
			 Delay_us(UPSampleRate);
			 UPPID.current=openMV1_mes;
			 pidCalc(&UPPID,&UPLF_DIR);
			 drive_setDir(UPLF_DIR);
			 delay_ms(1500);
			*/
			 //出库车身摆正，继续巡线，并使能openmv2
			 //阶段7
			 SERIAL_sendBYTE(USART3,2);
			 drive_setORI(3);
			 linePatrol(1,100);
			 
			// 测试代码
			drive_setDir(0); 
			drive_setORI(0);	
			while(1){
			};
			 
			
	
			 
			 
			 //---------------------------------------------
			 //侧方停车逻辑
			 //阶段2-1 继续巡线，直到收到2的信号：1
			 //SERIAL_sendBYTE(USART1,1);		//可视为分段测试，再次给openmv1发送1使其巡线
			 //while(!Key_GetNum()){}			//按下按钮才运行openmv2的模式
			 //SERIAL_sendBYTE(USART3,3);		//模式3为数侧方库边数
			 
			 
			 //此3行代码与上重复，可注释掉
				 
			 //舵机回正
			 drive_setDir(0); 
			 drive_setORI(3);	
			 delay_ms(570);
			 drive_setDir(45);			//初次入库
			 drive_setORI(-5);
			 delay_ms(1600);
			 
			 drive_setDir(-50);			//舵机左打，二次入库
			 drive_setORI(-5);			//停顿，用于调试
			 delay_ms(1200);
			 drive_setDir(0);			//舵机左打，二次入库
			 drive_setORI(0);			//停顿，用于调试
			 
			 BUZZER_ON();               //undefined//停车
			 Delay_ms(1000);  
			 BUZZER_OFF();
			 Delay_ms(1000);
			 
			 
			 drive_setDir(-50);         //出库
			 drive_setORI(5);
			 delay_ms(600);
			 drive_setDir(45);			
			 drive_setORI(5);
			 delay_ms(750);
			 
			 drive_setDir(0);			//直行
			 drive_setORI(3);
			 delay_ms(800);
			 
			 drive_setDir(0);			//停车
			 drive_setORI(0);

			 /*
			 //--------------------以下代码可删
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
			
			//--------------------以上代码可删
			
			
			
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
			 
			 
	}
	//openMVTest();
}







