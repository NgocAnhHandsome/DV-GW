/*
  ******************************************************************************
  * @file		sys.h                                                              *
  * @author	Luu Ngoc Anh                                                       *
  * @date		29/11/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __SYS__H
#define __SYS__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  // Device header
#include "define.h"        
#include "gpio.h"
#include "ringbuffer.h"
#include "uart.h"
#include "time_out.h"
#include "device_command.h"

void Fn_Sys_Init(void);
void Fn_Sys_Run(void);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/