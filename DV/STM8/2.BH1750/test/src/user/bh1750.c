#ifdef TEST
#include "bh1750.h"
#include "i2c.h"

uint8_t Bh1750_Mode;
uint8_t Bh1750_Mtreg;

void delay(int a)
{
  for (int i = 0; i < a; i++)
    for (int index = 0; index < 400; index++);
}

void bh1750_i2c_Write(uint8_t Addr, uint8_t data);
void bh1750_i2c_Read(uint8_t Addr, uint8_t* data, uint8_t len);
void BH1750_Init(uint8_t ModeRead, uint8_t ON_OFF)
{
     I2C_Init(100000);
     delay(100);
     BH1750_Reset();
     delay(100);
     BH1750_SetMtreg(BH1750_DEFAULT_MTREG);
     delay(100);
     BH1750_PowerState(ON_OFF);
     delay(100);
     BH1750_SetMode(ModeRead);
     delay(100);
}

void BH1750_Reset(void)
{
     bh1750_i2c_Write(BH1750_ADDRESS, BH1750_REG_RESET);
}

void BH1750_PowerState(uint8_t PowerOn)
{
     bh1750_i2c_Write(BH1750_ADDRESS, PowerOn);
}

void BH1750_SetMtreg(uint8_t Mtreg)
{
     Bh1750_Mtreg = Mtreg;
     uint8_t tmp[2] = {0};
     if(Mtreg<31||Mtreg>254)
     {
          Mtreg = 69;
     }
     tmp[0] = (0x40 | (Mtreg >> 5));
     tmp[1] = (0x60 | (Mtreg & 0x1F));
     bh1750_i2c_Write(BH1750_ADDRESS, tmp[0]);
     bh1750_i2c_Write(BH1750_ADDRESS, tmp[1]);
}

void BH1750_SetMode(uint8_t Mode)
{
  Bh1750_Mode = Mode;
  bh1750_i2c_Write(BH1750_ADDRESS, Mode);
}

void BH1750_ReadLight(float *Result)
{
  uint8_t tmp[2];
  bh1750_i2c_Read(BH1750_ADDRESS, tmp, 2);
  
  *Result = ((tmp[0]<<8)|(tmp[1]));
  if((Bh1750_Mode == BH1750_REG_ONCE_HIGH2) || (Bh1750_Mode == BH1750_REG_CONT_HIGH2))
  {
    *Result /=2.0;
  }
  *Result /= 1.2;
  
}

void bh1750_i2c_Write(uint8_t Addr, uint8_t data)
{
  I2C_Start();
  I2C_Write_add(Addr<<1, 0);
  I2C_Write(data);
  I2C_Stop();
}

void bh1750_i2c_Read(uint8_t Addr, uint8_t* data, uint8_t len)
{
  uint8_t i;
  I2C_Start();
  I2C_Write_add(Addr<<1, 1);
  for(i=0; i<len; i++)
  {
    if(i==len-1)
    {
      data[i] = I2C_Read_NAK();
    }
    else
    {
      data[i] = I2C_Read_ACK();
    }
  }
}
#endif // TEST