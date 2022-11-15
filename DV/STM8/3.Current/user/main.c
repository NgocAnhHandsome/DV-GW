#include "stm8s.h"
#include "uart.h"
#include "DELAY.H"
#include "adc_lib.h"
#include "timer_lib.h"

uint32_t count_time = 0;

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void delay_ms(int a)
{
  for (int i = 0; i < a; i++)
    for (int index = 0; index < 400; index++);
}

int main( void )
{
  UART_Init(9600);
  Time4_Init();
  while (1)
  {
    if (UART_Flag())
    {
      UART_Send_Array_RX();
    }
    
      UART_Send_Number(Adc_AIN3_Data);
      Fn_Delayms(100);
      UART_Send_String("\n");
    /*
      UART_Send_Number(ADC_Read(3,100));
      Fn_Delayms(100);
      UART_Send_String("--");
      UART_Send_Number(ADC_Read(4,100));
      Fn_Delayms(100);
      UART_Send_String("\n");
    */
  }
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{
  TIM4->SR1 = 0;

  if (count_time >= 10)
  {
    Adc_AIN3_Data = ADC_Kalman_Filter(ADC_Read(3,0), &Kalman_Var_AIN3);
    count_time = 0;
  }
  else
  {
    count_time++;
  }
}