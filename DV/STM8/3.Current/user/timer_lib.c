#include "timer_lib.h"

void Time4_Init(void)
{
  TIM4->PSCR = TIM4_PRESCALER_128;
  TIM4->ARR = 125;
  TIM4->IER = 0x01;
  TIM4->CR1 = 0x01;
  enableInterrupts();
}
