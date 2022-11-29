/*
  ******************************************************************************
  * @file		gpio.h                                                     	       *
  * @author	Luu Ngoc Anh                                                       *
  * @date		30/11/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __GPIO__H
#define __GPIO__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "define.h"

typedef enum
{
	GET_GPIO_CONNECTED = 0,
	GET_GPIO_DISCONNECTED
}_status_port_plug_e;

void Fn_GPIO_Init(void);
void Fn_SET_GPIO_ON(int port);
void Fn_SET_GPIO_OFF(int port);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/