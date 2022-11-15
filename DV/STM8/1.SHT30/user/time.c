#include "time.h"

void TIME4_Init(void)
{
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  TIM4->PSCR = 0x0A
  TIM4->
}