#include "gpio.h"

static void SET_GPIO_PORT_Init(void);
static void GET_GPIO_PORT_Init(void);

void Fn_GPIO_Init(void)
{
	SET_GPIO_PORT_Init();
	GET_GPIO_PORT_Init();
}

void Fn_SET_GPIO_ON(int port)
{
	switch(port)
	{
		case 0:
		{
			GPIO_SetBits(GPIOB, SET_GPIO_PORTB_1);
			break;
		}
		case 1:
		{
			GPIO_SetBits(GPIOB, SET_GPIO_PORTB_2);
			break;			
		}
		case 2:
		{
			GPIO_SetBits(GPIOB, SET_GPIO_PORTB_3);
			break;			
		}
		case 3:
		{
			GPIO_SetBits(GPIOB, SET_GPIO_PORTB_4);
			break;			
		}
		case 4:
		{
			GPIO_SetBits(GPIOA, SET_GPIO_PORTA_5);
			break;			
		}
		case 5:
		{
			GPIO_SetBits(GPIOA, SET_GPIO_PORTA_6);
			break;				
		}
		default:
			break;
	}	
}
void Fn_SET_GPIO_OFF(int port)
{
	switch(port)
	{
		case 0:
		{
			GPIO_ResetBits(GPIOB, SET_GPIO_PORTB_1);
			break;
		}
		case 1:
		{
			GPIO_ResetBits(GPIOB, SET_GPIO_PORTB_2);
			break;			
		}
		case 2:
		{
			GPIO_ResetBits(GPIOB, SET_GPIO_PORTB_3);
			break;			
		}
		case 3:
		{
			GPIO_ResetBits(GPIOB, SET_GPIO_PORTB_4);
			break;			
		}
		case 4:
		{
			GPIO_ResetBits(GPIOA, SET_GPIO_PORTA_5);
			break;			
		}
		case 5:
		{
			GPIO_ResetBits(GPIOA, SET_GPIO_PORTA_6);
			break;				
		}
		default:
			break;
	}
}

static void SET_GPIO_PORT_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin  = SET_GPIO_PORTB_1|SET_GPIO_PORTB_2|SET_GPIO_PORTB_3|SET_GPIO_PORTB_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SET_GPIO_PORTA_5|SET_GPIO_PORTA_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
static void GET_GPIO_PORT_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin   = GET_GPIO_PORTB_ALL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}