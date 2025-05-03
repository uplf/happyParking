#ifndef __USER_SETUP_H
#define __USER_SETUP_H
#include "stm32f10x.h"                  // Device header



/*******Section0:ATTENTION
1.<PIN>SPI communication is fixed attached to the following pins, which means these pins can't
	be assigned to other usage once SPI is activated
	PA4 PA5 PA6 PA7
*/

/*******Section1:basic hardware Setup

*/

//1.OLED_PINS
#define OLED_W_SCL_Pin GPIO_Pin_4
#define OLED_W_SDA_Pin GPIO_Pin_3
#define OLED_W_Port GPIOB

//2.TB6612 conf_PINS
//#define USING_TB6612
#define USING_WIT

#define DRIVE_AIN1_GROUP GPIOB
#define DRIVE_AIN2_GROUP GPIOB
#define DRIVE_BIN1_GROUP GPIOB
#define DRIVE_BIN2_GROUP GPIOB
#define DRIVE_AIN1_PIN GPIO_Pin_14
#define DRIVE_AIN2_PIN GPIO_Pin_15
#define DRIVE_BIN1_PIN GPIO_Pin_13
#define DRIVE_BIN2_PIN GPIO_Pin_12



//3.CONFIG
#define REUSE_INIT 1

//4.CTRL_PINS
//head to <key.h->to alter key_PIN_CONFIG
#define KEY_1_Port GPIOA
#define KEY_1_PIN GPIO_Pin_11
#define KEY_2_Port GPIOA
#define KEY_2_PIN GPIO_Pin_12
#define KEY_3_Port GPIOA
#define KEY_3_PIN GPIO_Pin_15

//head to <key.h->to alter encoder_PIN_CONFIG
#define ENCODER_Port GPIOB
#define ENCODERa_PIN GPIO_Pin_1
#define ENCODERb_PIN GPIO_Pin_5




//6.MPU6050_CONFIG
#define MPU_Port GPIOB
#define MPU_SDA_PIN GPIO_Pin_11
#define MPU_SCL_PIN GPIO_Pin_10
//<MPU6050_I2C.h 12-15>to be altered
#define WIT_Port GPIOB
#define WIT_SDA_PIN GPIO_Pin_11
#define WIT_SCL_PIN GPIO_Pin_10

//7.grey_CONFIG <!disabled!>
#define GREY_Port GPIOB
#define GREY_SDA_PIN GPIO_Pin_11
#define GREY_SCL_PIN GPIO_Pin_10




/*******Section2:index Setup
1.Speed*/
#define BASIC_SPEEDLF 82
#define BASIC_SPEEDRF 82
//#define BASIC_SPEEDRF 100
#define BASIC_SPEEDLB 52
#define BASIC_SPEEDRB 52
#define BASIC_TOWARDS 1450
//1-100
#define ALTER_UNIT 1
#define INV_ABLE 1

//
#define UPSampleRate 1000

/********Section3:全局变量
*/

extern int16_t UPLF_DIR;
extern int8_t openMV1Status;


#endif
