#include "stm32f10x.h"
#include "CONFgeneral.h"
#include "detCalc.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "drive.h"
#include "Interrupt.h"
#include "userSetup.h"


//巡线中断

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
			MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);//检测MPU6050并完成角度解算
			AngleLeft.current=Yaw;
			AngleRight.current=Yaw;
		#endif

		
		//控制

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}


