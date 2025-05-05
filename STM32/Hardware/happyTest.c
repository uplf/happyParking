#include "happyTest.h"

void hardwareTest(){
	int16_t testHelper=0;
	int16_t testHelper2=0;
	reuse_init();
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(1,1,"1/");
	OLED_ShowString(2,1,"OLED_Test");
	OLED_ShowString(3,1,"seeseeme");
	OLED_ShowString(4,1,"AutoContinue-3s");
	Delay_ms(3000);
	OLED_Clear();
	
	Key_Init();
	OLED_ShowString(1,1,"2/");
	OLED_ShowString(2,1,"Key _Test");
	OLED_ShowString(3,1,"");
	OLED_ShowString(4,1,"pressThreeKeys");
	do{
		 testHelper2=Key_GetNum();
		if(testHelper2){
			testHelper2=(1<<testHelper2);
			testHelper=testHelper^testHelper2;
			OLED_ShowBinNum(3,1,testHelper,4);
		}
	}while(testHelper!=14);
	OLED_Clear();
	
	
	LED_Init();
	OLED_ShowString(1,1,"3/");
	OLED_ShowString(2,1,"BUZZER_Test");
	OLED_ShowString(3,1,"loooook ");
	OLED_ShowString(4,1,"pressAnyKey ");
	while(!Key_GetNum()){
		BUZZER_ON();
		Delay_ms(100);
		BUZZER_OFF();
		Delay_ms(100);
	}
	
	drive_init();
	OLED_ShowString(1,1,"4/");
	OLED_ShowString(2,1,"Drive_Test");
	OLED_ShowString(3,1,"gogogochufalou");
	Delay_ms(1000);
	for(testHelper=-6;testHelper<=6;testHelper++){
		drive_setORI(testHelper);
		Delay_ms(500);
	}
	drive_setORI(0);
	for(testHelper=-50;testHelper<=50;testHelper++){
		drive_setDir(testHelper);
		Delay_ms(10);
	}
	OLED_Clear();
	

	OLED_ShowString(1,1,"5/");
	OLED_ShowString(2,1,"MPU_Test");
	OLED_ShowString(4,1,"pressAnyKey ");
	MPU6050_Init();		//MPU6050³õÊ¼»¯
	MPU6050_DMP_Init();
	float Pitch,Roll,Yaw;
	TIM_Cmd(TIM3,DISABLE);
	while(!Key_GetNum())
	{
		Delay_ms(5);
		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);
		OLED_ShowSignedNum(3,1,Yaw,5);
		
	}
	TIM_Cmd(TIM3,ENABLE);
	
	
	PIDgroupInit();
	intInit();
}

void openMVTest(){
	int m=0,n=0;
	openMV_init();
	OLED_ShowString(1,1,"6/openMV_Test");
	//OLED_ShowString(4,1,"pressKey1 ");
	OLED_ShowString(2,1,"rec1:");
	OLED_ShowString(3,1,"rec2:");
	//openMV1_send(TEST_SIG);
	//openMV2_send(TEST_SIG);
	do{
		n=Key_GetNum();
		if(n==2)SERIAL_sendBYTE(USART1,1);
		if(n==3)SERIAL_sendBYTE(USART3,1);
		OLED_ShowNum(2,6,openMV1_mes,8);
		OLED_ShowNum(3,6,openMV2_mes,8);
		OLED_ShowNum(4,1,testFlag,5);
		OLED_ShowNum(4,8,(openMV2_mes==2),1);
		if(n)OLED_ShowNum(4,10,n,1);
		m=!m;
	}while(n!=1);
	OLED_Clear();

}


void ServoScope(){
	int16_t servoIND=0;
	int8_t keyIND=0;
	OLED_ShowString(1,1,"7/Servo_Test");
	while(1){
		keyIND=Key_GetNum();
		switch(keyIND)
		{
			case 0:
				continue;
			case 1:{
				servoIND+=5;
				return;
			}
			case 2:{
				servoIND+=5;
				break;
			}
			case 3:servoIND-=5;
		}
		OLED_ShowNum(1,1,openMV1_mes,5);
		OLED_ShowSignedNum(3,1,servoIND,5);
		drive_setDir(servoIND);
		
	}
}
