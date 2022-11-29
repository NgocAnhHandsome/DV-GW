/*
  ******************************************************************************
  * @file		define.h                                                           *
  * @author	Luu Ngoc Anh                                                       *
  * @date		24/10/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __DEFINE__H
#define __DEFINE__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  // Device header
#include "stm32f10x.h"                  // Device header
#include "uart.h" 
#include "device_command.h"
#include "time_out.h"
	 


#define SET_GPIO_PORTB_1   		GPIO_Pin_12
#define SET_GPIO_PORTB_2   		GPIO_Pin_13
#define SET_GPIO_PORTB_3   		GPIO_Pin_14
#define SET_GPIO_PORTB_4   		GPIO_Pin_15
#define SET_GPIO_PORTA_5   		GPIO_Pin_11
#define SET_GPIO_PORTA_6   		GPIO_Pin_12
#define SET_GPIO_PORTAB_ALL   SET_GPIO_PORTB_1|SET_GPIO_PORTB_2|SET_GPIO_PORTB_3|SET_GPIO_PORTB_4|SET_GPIO_PORTB_5|SET_GPIO_PORTB_6

#define GET_GPIO_CONNECTED		0
#define GET_GPIO_DISCONNECTED	1

#define GET_GPIO_PORTB_1 			GPIO_Pin_5
#define GET_GPIO_PORTB_2 			GPIO_Pin_4
#define GET_GPIO_PORTB_3 			GPIO_Pin_3
#define GET_GPIO_PORTB_4 			GPIO_Pin_0
#define GET_GPIO_PORTB_5 			GPIO_Pin_1
#define GET_GPIO_PORTB_6 			GPIO_Pin_2
#define GET_GPIO_PORTB_ALL    GET_GPIO_PORTB_1|GET_GPIO_PORTB_2|GET_GPIO_PORTB_3|GET_GPIO_PORTB_4|GET_GPIO_PORTB_5|GET_GPIO_PORTB_6



typedef enum
{
	busy,
	free
}status_transmission_t;


void SET_GPIO_PORT_Init(void);
void GET_GPIO_PORT_Init(void);
status_transmission_t Check_busy(void);

void SET_GPIO_ON(int port);
void SET_GPIO_OFF(int port);

void GW_COMM_AskType(int port);
void Scan_Port(void);
//void Show_detect(_comm_data_struct_detect_t detect_test);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/