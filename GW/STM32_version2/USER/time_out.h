/*
  ******************************************************************************
  * @file		time_out.h                                                         *
  * @author	Luu Ngoc Anh                                                       *
  * @date		29/11/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __TIME_OUT__H
#define __TIME_OUT__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "uart.h"

#define PERIOD 1000
#define PRESCALER 72
#define TIME_OUT 100

void Fn_TIM2_Timeout_Init(void);
uint8_t Fn_TIM2_Timeout_Flag(void);
void Fn_TIM2_Timeout_SetValue(unsigned int _vrui_Time);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/