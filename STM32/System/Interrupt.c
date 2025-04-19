#include "stm32f10x.h"
#include "CONFgeneral.h"
#include "detCalc.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "drive.h"
#include "Interrupt.h"
#include "userSetup.h"


//Ѳ���ж�

void intInit(){

}

void TIM3_IRQHandler(void)
{
	
	//MPU6050 scan->mpuINDEX
	//grey scan->greyINDEX
	//runMode->1 ;->2 ;->0
	
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		#ifdef USING_MPU6050
			MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);//���MPU6050����ɽǶȽ���
			AngleLeft.current=Yaw;
			AngleRight.current=Yaw;
		#endif

		
		//����

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}


