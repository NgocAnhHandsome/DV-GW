
#ifndef __TIMER_H__
#define __TIMER_H__

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

typedef enum
{
  TIM4_PRESCALER_1  = ((uint8_t)0x00),
  TIM4_PRESCALER_2    = ((uint8_t)0x01),
  TIM4_PRESCALER_4    = ((uint8_t)0x02),
  TIM4_PRESCALER_8     = ((uint8_t)0x03),
  TIM4_PRESCALER_16   = ((uint8_t)0x04),
  TIM4_PRESCALER_32     = ((uint8_t)0x05),
  TIM4_PRESCALER_64    = ((uint8_t)0x06),
  TIM4_PRESCALER_128   = ((uint8_t)0x07)
} TIM4_Prescaler_TypeDef;


void Time4_Init(void);

#endif /* __STM8S_UART1_H */
