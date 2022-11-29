#include "sys.h"

static char Temp_data_get_arr[100];
_status_port_plug_e Arr_port_plug[6] = {GET_GPIO_DISCONNECTED, GET_GPIO_DISCONNECTED, GET_GPIO_DISCONNECTED, GET_GPIO_DISCONNECTED, GET_GPIO_DISCONNECTED, GET_GPIO_DISCONNECTED};
uint16_t GET_GPIO_PORTB_Arr[6]  = {GET_GPIO_PORTB_1, GET_GPIO_PORTB_2, GET_GPIO_PORTB_3, GET_GPIO_PORTB_4, GET_GPIO_PORTB_5, GET_GPIO_PORTB_6};

static void Fn_name_the_gate(int port);
static void Fn_scan_port(void);

void Fn_Sys_Init(void)
{
	INIT_UART_2(9600);
	INIT_UART_1(9600);	
	Fn_TIM2_Timeout_Init();
	Fn_GPIO_Init();
	printf("Chao Ngoc Anh: \n");
}
void Fn_Sys_Run(void)
{
	Fn_scan_port();
}

static void Fn_name_the_gate(int port)
{
		_comm_data_struct_create_t _encode_new;  
		_comm_data_struct_detect_t _decode_new;
	
		_encode_new.type_msg = COMM_AskType;
		_encode_new.port_number = (_comm_port_number_e)port;
		comm_create_command(&_encode_new);
	
		Fn_TIM2_Timeout_SetValue(TIME_OUT); //stm8 
		while(!Fn_TIM2_Timeout_Flag()){}
			
		UART2_SendString(_encode_new.datastr);
		while(!Fn_TIM2_Timeout_Flag()){} // cho time_out
		while(ringbuffer_get_arr(&ringbuffer_Test,Temp_data_get_arr) != Ringbuffer_get_arr_done) // loi treo
		{
			Fn_TIM2_Timeout_SetValue(TIME_OUT);
			if(Fn_TIM2_Timeout_Flag())
			{
				Arr_port_plug[port] = GET_GPIO_DISCONNECTED;
				Fn_SET_GPIO_OFF(port);
				printf("COM_%d ket noi false!\n", port + 1);		
				break;
			}
		}
		comm_detect_command(Temp_data_get_arr, &_decode_new);
		if(_decode_new.port_number == (_comm_port_number_e)port)
		{
		Arr_port_plug[port] = GET_GPIO_CONNECTED;
		printf("COM_%d da ket noi!\n",port + 1);				
		}
		else
		{
			Arr_port_plug[port] = GET_GPIO_DISCONNECTED;
			Fn_SET_GPIO_OFF(port);
			printf("COM_%d ket noi false!\n", port + 1);
		}	
}
static void Fn_scan_port(void)
{
	for(int i = 0; i < 6; i++)
	{
		if(GPIO_ReadInputDataBit(GPIOB, GET_GPIO_PORTB_Arr[i]) == GET_GPIO_CONNECTED)
		{
			if(Arr_port_plug[i] == GET_GPIO_DISCONNECTED)
			{
				Fn_SET_GPIO_ON(i);
				Fn_name_the_gate(i);	
			}
			else
			{
				Arr_port_plug[i] = GET_GPIO_CONNECTED; // da co port
			}
		}
		else
		{
			if(Arr_port_plug[i] == GET_GPIO_DISCONNECTED)
			{
				Arr_port_plug[i] = GET_GPIO_DISCONNECTED;
			}
			else
			{
				Fn_SET_GPIO_OFF(i);
				printf("Port %d: ngat ket noi\n",i+1);
				Arr_port_plug[i] = GET_GPIO_DISCONNECTED;
			}			
		}
	}	
}