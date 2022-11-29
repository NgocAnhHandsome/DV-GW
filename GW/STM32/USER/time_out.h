
/*
  ******************************************************************************
  * @file		time_out.h                                                         *
  * @author	Luu Ngoc Anh                                                       *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef __TIME_OUT__H
#define __TIME_OUT__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  // Device header
#include "uart.h"

#define PERIOD 1000
#define PRESCALER 72
#define TIME_OUT  500

void TIM2_Out_init(void);
void TIM2_Out_set_value(int __vrTime_out_ms);
uint8_t TIM2_Out_Flag(void);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/