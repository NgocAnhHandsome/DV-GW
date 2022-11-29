/**
  ********************************************************************************
  * @file    time.h
  * @author  Luu Ngoc Anh
  * @version 
  * @date    
  * @brief   
  *******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIME_H
#define __TIME_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "uart.h"

#define TIME_OUT 100
    
void TIME4_Init(void);
uint8_t Check_time_out(void);
void TIM4_Out_set_value(int __vrTime_out_ms);

#endif /* __STM8S_UART1_H */