#ifndef __OPENMV_H
#define __OPENMV_H

#include "comCONFgeneral.h"
#include "CONFgeneral.h"
#include "stm32f10x.h"                  // Device header

#define TEST_SIG 0x01
#define TESTEND_SIG 0x02



#define openMV1_send(x)  (SERIAL_sendBYTE(USART1, (x)))
#define openMV2_send(x)  (SERIAL_sendBYTE(USART2, (x)))

void openMV_init();

extern uint8_t openMV1_mes,openMV2_mes;


#endif