#include "define.h"

void delay(uint16_t i);
void Config(void);

int main()
{
	Config();
	while(1)
	{
		Scan_Port();
 	}
} 


void Config(void)
{
	INIT_UART_2(9600);
	INIT_UART_1(9600);
	TIM2_Out_init();
	SET_GPIO_PORT_Init();	
	GET_GPIO_PORT_Init();	
}

void delay(uint16_t i)
{
	while(i--)
	{
		for(uint16_t j = 0; j < 0x2aff; j++);
	}
}

