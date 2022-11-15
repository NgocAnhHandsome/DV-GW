#include "stm8s.h"
#include "uart.h"
#include "bh1750.h"
/*
/mnt/h/2.project/2022/thang 8/1.ThietBi_GS/1.Sensor/2.BH1750
*/

//D6-rx
//D5-tx
void delay_ms(int a)
{
  for (int i = 0; i < a; i++)
    for (int index = 0; index < 400; index++);
}

void intTostr(uint32_t data, uint8_t *arr)
{
  uint32_t TempData = 0, count = 0;
  while(data)
  {
    TempData =  (TempData*10)+(data%10);
    data /= 10;
  }
  while(TempData)
  {
    arr[count] =  (TempData%10)+'0';
    TempData /= 10;
    count++;
  }
  arr[count] = 0;
}

void floatTostr(float data, char *arr, uint8_t ndigits)
{
  uint32_t Tempdata1 = 0, Tempdata2 = 0;
  uint8_t i, count1 = 0, count2 = 0;
  if(((uint32_t)data) < 1)
  {
    arr[count2] = '0';
    count2++;
    count1++;
  }
  for(i=0; i<ndigits; i++)
  {
    data *= 10;
  }
  Tempdata1 = (uint32_t)data;
  while(Tempdata1)
  {
    Tempdata2 =  (Tempdata2*10)+(Tempdata1%10);
    Tempdata1 /= 10;
    count1++;
  }
  
  while(Tempdata2)
  {
    if(count2 == (count1 - ndigits))
    {
     arr[count2] =  '.';
    }
    else
    {
      arr[count2] =  (Tempdata2%10)+'0';
      Tempdata2 /= 10;
    }
    count2++;
  }
  arr[count2] = 0;
}

int main( void )
{
  float data;
  char arr[20];
  
  UART_Init(9600);
  BH1750_Init(BH1750_REG_CONT_LOW, BH1750_REG_POWER_ON);
  delay_ms(10000);
  while (1)
  {
    BH1750_ReadLight(&data);
    floatTostr(data, arr, 2);
    UART_Send_String("LUX: ");
    UART_Send_String(arr);
    UART_Send_String("\n");
    delay_ms(1000);
  }
}
