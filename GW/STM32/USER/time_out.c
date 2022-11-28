#include "time_out.h"

volatile int Time_out = 1;

void TIM2_Out_init(void)
{
	TIM_TimeBaseInitTypeDef timer_init;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	timer_init.TIM_CounterMode = TIM_CounterMode_Up;
	timer_init.TIM_Period = PERIOD - 1;
	timer_init.TIM_ClockDivision = 0;
	timer_init.TIM_RepetitionCounter = 0;
	timer_init.TIM_Prescaler = PRESCALER - 1;
	TIM_TimeBaseInit(TIM2,&timer_init);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET){
		if(UART2_Flag_Receive())
		{
			Time_out = TIME_OUT;
		}
		Time_out--;
   if(Time_out <= 0)
   {
    Time_out = 1;
   }		
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void TIM2_Out_set_value(int __vrTime_out_ms)
{
	Time_out = __vrTime_out_ms;
}

uint8_t TIM2_Out_Flag(void)
{
  if(Time_out <= 1)
    return 1;
  else
    return 0;
}
