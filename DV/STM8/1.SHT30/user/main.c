#include "stm8s.h"
#include "uart.h"
#include "i2c.h"
#include "sht30.h"
#include "sys.h"
#include "device_command.h"

// D5 TX
// D6 RX

int i,j,k,n;

_comm_type_command_e Type_command_arr[] = {COMM_AskType, COMM_AnswerType, COMM_AskData, COMM_AnswerData};

_comm_port_number_e Port_number_arr[] = {COMM_Port1, COMM_Port2,COMM_Port3,COMM_Port4,
																		COMM_Port5, COMM_Port6,COMM_Port7,COMM_Port8};
_comm_type_sensor_e Type_sensor_arr[] = {Sensor_1,Sensor_2, Sensor_3};

_comm_data_sensor_t sensor = {1.2, 3.5, 2.6, 2.7, 3.6, 7.6, 2.1, 4.4, 5.6, 2.5, 3.7, 1.9, 7.5, 2.1, 5.7};

						
_comm_data_struct_create_t test;
_comm_data_struct_detect_t detect_test;



char Temp_data[100];
void delay(uint16_t i);

void Show_detect(_comm_data_struct_detect_t detect_test);

int main( void )
{
  UART_Init(9600);
  while (1)
  {
      if(ringbuffer_get_arr(&ringbuffer_Test, Temp_data)==Ringbuffer_get_arr_done)
      {
        UART_Send_String(Temp_data);
      }
      else
      {
 //       UART_Send_String("Error\n");
      }
      delay(1000);
  }
}

void delay_ms(int a)
{
  for (int i = 0; i < a; i++)
    for (int index = 0; index < 400; index++);
}