#include "define.h"

char Temp_data[100];

//_comm_data_struct_create_t _encode_new;
//_comm_data_struct_detect_t _decode_new;

// Bo nho port da ket noi
uint8_t Arr_port[6] = {GET_GPIO_DISCONNECTED, GET_GPIO_DISCONNECTED, GET_GPIO_DISCONNECTED, GET_GPIO_DISCONNECTED, GET_GPIO_DISCONNECTED, GET_GPIO_DISCONNECTED};
uint16_t GET_GPIO_PORTB_Arr[6]  = {GET_GPIO_PORTB_1, GET_GPIO_PORTB_2, GET_GPIO_PORTB_3, GET_GPIO_PORTB_4, GET_GPIO_PORTB_5, GET_GPIO_PORTB_6};

void SET_GPIO_PORT_Init(void)
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
void GET_GPIO_PORT_Init(void)
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

status_transmission_t Check_busy(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4) == 1||UART2_Flag_Receive() == 1 
											|| TIM2_Out_Flag() ==0 )
		{
			return busy;
		}
	else
		{
			return free;
		}
}

void GW_COMM_AskType(int port)
{
		_comm_data_struct_create_t _encode_new;  
		_comm_data_struct_detect_t _decode_new;
	
		_encode_new.type_msg = COMM_AskType;
		_encode_new.port_number = (_comm_port_number_e)port;
		comm_create_command(&_encode_new);
		SET_GPIO_ON(port);
	
		TIM2_Out_set_value(TIME_OUT); //stm8 
		while(!TIM2_Out_Flag()){}
			
		UART2_SendString(_encode_new.datastr);
		while(!TIM2_Out_Flag()){} // cho time_out
		if(ringbuffer_get_arr(&ringbuffer_Test,Temp_data) == Ringbuffer_get_arr_done)
		{
			comm_detect_command(Temp_data, &_decode_new);
			if(_decode_new.port_number == (_comm_port_number_e)port)////////
			{
			Arr_port[port] = GET_GPIO_CONNECTED;
			printf("COM_%d da ket noi!\n",port + 1);				
			}
			else
			{
				Arr_port[port] = GET_GPIO_DISCONNECTED;
				SET_GPIO_OFF(port);
				printf("COM_%d ket noi false!\n", port + 1);
			}
		}
		else
		{
			printf("ringbuffer_get_arr false\n");
			Arr_port[port] = GET_GPIO_DISCONNECTED;
//			SET_GPIO_OFF(port);
		}
}

void SET_GPIO_ON(int port)
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
void SET_GPIO_OFF(int port)
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

void Scan_Port(void)
{
	for(int i = 0; i < 6; i++)
	{
		if(GPIO_ReadInputDataBit(GPIOB, GET_GPIO_PORTB_Arr[i]) == GET_GPIO_CONNECTED)
		{
			if(Arr_port[i] == GET_GPIO_DISCONNECTED)
			{
				GW_COMM_AskType(i);	
			}
			else
			{
				Arr_port[i] = GET_GPIO_CONNECTED; // da co port
			}
		}
		else
		{
			if(Arr_port[i] == GET_GPIO_DISCONNECTED)
			{
				Arr_port[i] = GET_GPIO_DISCONNECTED;
			}
			else
			{
				SET_GPIO_OFF(i);
				printf("Port %d: ngat ket noi\n",i+1);
				Arr_port[i] = GET_GPIO_DISCONNECTED;
			}			
		}
	}
}

//void Show_detect(_comm_data_struct_detect_t detect_test)
//{
//	switch(detect_test.type_msg)
//	{
//		case COMM_AskType:
//			UART1_SendString("COMM_AskType\n");
//			break;
//		case COMM_AnswerType:
//			UART1_SendString("COMM_AnswerType\n");
//			break;	
//		case COMM_AskData:
//			UART1_SendString("COMM_AskData\n");
//			break;		
//		case COMM_AnswerData:
//			UART1_SendString("COMM_AnswerData\n");
//			break;
//		default:
//			break;
//		
//	switch(detect_test.port_number)
//	{
//		case COMM_Port1:
//			UART1_SendString("COMM_Port1\n");
//			break;
//		case COMM_Port2:
//			UART1_SendString("COMM_Port2\n");
//			break;
//		case COMM_Port3:
//			UART1_SendString("COMM_Port3\n");
//			break;
//		case COMM_Port4:
//			UART1_SendString("COMM_Port4\n");
//			break;
//		case COMM_Port5:
//			UART1_SendString("COMM_Port5\n");
//			break;
//		case COMM_Port6:
//			UART1_SendString("COMM_Port6\n");
//			break;
//		case COMM_Port7:
//			UART1_SendString("COMM_Port7\n");
//			break;
//		case COMM_Port8:
//			UART1_SendString("COMM_Port8\n");
//			break;
//		default:
//			break;
//	}
//	switch(detect_test.type_sensor)
//	{
//		case Sensor_1:
//			UART1_SendString("Sensor_1\n");
//			break;
//		case Sensor_2:
//			UART1_SendString("Sensor_2\n");
//			break;
//		case Sensor_3:
//			UART1_SendString("Sensor_3\n");
//			break;
//		default:
//			break;
//	}
//	char s[10];
//	sprintf(s,"Sensor_1: %f\n", detect_test.Sensor.Sensor_1);
//	UART1_SendString(s);
////	sprintf(s,"Sensor_2: %f\n", detect_test.Sensor.Sensor_2);
////	UART2_SendString(s);
////	sprintf(s,"Sensor_3: %f\n", detect_test.Sensor.Sensor_3);
////	UART2_SendString(s);
////	sprintf(s,"Sensor_4: %f\n", detect_test.Sensor.Sensor_4);
////	UART2_SendString(s);
////	sprintf(s,"Sensor_5: %f\n", detect_test.Sensor.Sensor_5);
////	UART2_SendString(s);
////	sprintf(s,"Sensor_5: %f\n", detect_test.Sensor.Sensor_6);
////	UART2_SendString(s);
////	sprintf(s,"Sensor_7: %f\n", detect_test.Sensor.Sensor_7);
////	UART2_SendString(s);
////	sprintf(s,"Sensor_8: %f\n", detect_test.Sensor.Sensor_8);
////	UART2_SendString(s);
////	sprintf(s,"Sensor_9: %f\n", detect_test.Sensor.Sensor_9);
////	UART2_SendString(s);
////	sprintf(s,"Sensor_10:%f\n", detect_test.Sensor.Sensor_10);
////	UART2_SendString(s);
////	sprintf(s,"Sensor_11:%f\n", detect_test.Sensor.Sensor_11);
////	UART2_SendString(s);	
////	sprintf(s,"Sensor_12:%f\n", detect_test.Sensor.Sensor_12);
////	UART2_SendString(s);	
////	sprintf(s,"Sensor_13:%f\n", detect_test.Sensor.Sensor_13);
////	UART2_SendString(s);
////	sprintf(s,"Sensor_14:%f\n", detect_test.Sensor.Sensor_14);
////	UART2_SendString(s);	
////	sprintf(s,"Sensor_15:%f\n", detect_test.Sensor.Sensor_15);
////	UART2_SendString(s);		
//}

////		if(Flag2_Receive)
////		{
////			UART1_SendString("Start: \n");
////			Flag2_Receive = 0;
////			if(ringbuffer_get_arr(&ringbuffer_Test, Temp_data) == Ringbuffer_get_arr_done)
////			{
////				UART1_SendString(Temp_data);
////				UART1_SendString("\n");
////				comm_detect_command(Temp_data, &detect_test);
////				Show_detect(detect_test);
////			}			
//}	
