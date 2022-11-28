#include "stm8s.h"
#include "uart.h"
#include "i2c.h"
#include "sht30.h"
#include "sys.h"
#include "device_command.h"
#include "time.h"

// D5 TX
// D6 RX

						
_comm_data_struct_create_t _encode_new;
_comm_data_struct_detect_t _decode_new;

char Temp_data[100];
void delay(uint16_t i);

void Receive_Port(void);

void Show_detect(_comm_data_struct_detect_t detect_test);

int main( void )
{
//  delay(10);
  UART_Init(9600);
  TIME4_Init();
  while (1)
  {
    Receive_Port();
  }
}

void Receive_Port(void)
{
    if(ringbuffer_get_arr(&ringbuffer_Test, Temp_data) == Ringbuffer_get_arr_done)
    {
     comm_detect_command(Temp_data, &_decode_new);
     _encode_new.type_msg = COMM_AnswerType;
     _encode_new.port_number = _decode_new.port_number;
     _encode_new.type_sensor = Sensor_1;
     comm_create_command(&_encode_new);
     UART_Send_String(_encode_new.datastr);
    }
}

