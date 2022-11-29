#include "stm32f10x.h"                  // Device header
#include "delay.h"

TIM_TimeBaseInitTypeDef TIM_InitStructure;

void Delay_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 0xffff;
	TIM_InitStructure.TIM_Prescaler = 72 - 1;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2,&TIM_InitStructure);
	TIM_Cmd(TIM2,ENABLE);
}

void Delay_Us(unsigned int Time_Us)
{
	Delay_Init();
	TIM_SetCounter(TIM2,0);
	while(TIM_GetCounter(TIM2) < Time_Us);
	TIM_Cmd(TIM2,DISABLE);
}
void Delay_Ms(unsigned int Time_Ms)
{
	while(Time_Ms --)
	{
		Delay_Us(1000);
	}
}