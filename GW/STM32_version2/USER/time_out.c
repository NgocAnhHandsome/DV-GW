#include "time_out.h"

volatile uint8_t _vruc_Flag_TimeOut;

void Fn_TIM2_Timeout_Init(void)
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

uint8_t Fn_TIM2_Timeout_Flag(void)
{
	if(_vruc_Flag_TimeOut == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Fn_TIM2_Timeout_SetValue(unsigned int _vrui_Time)
{
	_vruc_Flag_TimeOut = _vrui_Time;
}

void TIM2_IRQHandler(){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET){
		if(UART2_Flag_Receive())
		{
			_vruc_Flag_TimeOut = TIME_OUT;
		}
		if(_vruc_Flag_TimeOut != 0)
		{
			_vruc_Flag_TimeOut--;
		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}