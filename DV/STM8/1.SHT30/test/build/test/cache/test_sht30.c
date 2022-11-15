#include "src/sht30.h"
#include "build/test/mocks/mock_i2c.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




extern uint8_t Bh1750_Mode;

void bh1750_i2c_Write_test(uint8_t Addr, uint16_t data);

void bh1750_i2c_Read_test(uint8_t Addr, uint8_t* datainput, uint8_t len);

uint8_t bh1750_crate_Checksum(uint8_t *data, int len);



void setUp(void)

{



}



void tearDown(void)

{

}



void test_function_sht30_SetHeater(void)

{

    bh1750_i2c_Write_test(0x44, 0x306D);

    SHT30_SetHeater(0x306D);



    bh1750_i2c_Write_test(0x44, 0x3066);

    SHT30_SetHeater(0x3066);

}



void test_function_sht30_isHeaterEnabled_On(void)

{

    uint8_t datamock_registerStatus[3] ;

    uint16_t register_status_value = 1<<13;



    datamock_registerStatus[0] = ((register_status_value&0xff00)>>8u);

    datamock_registerStatus[1] = ((register_status_value&0xff));

    datamock_registerStatus[2] = bh1750_crate_Checksum(datamock_registerStatus, 2);



    bh1750_i2c_Write_test(0x44, 0xF32D);

    bh1750_i2c_Read_test(0x44, datamock_registerStatus, 3);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((SHT30_isHeaterEnabled())), (UNITY_INT)(UNITY_INT8 )((1)), (

   ((void *)0)

   ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_INT8);

}



void test_function_sht30_isHeaterEnabled_Off(void)

{

    uint8_t datamock_registerStatus[3];

    uint16_t register_status_value = 0;



    datamock_registerStatus[0] = ((register_status_value&0xff00)>>8u);

    datamock_registerStatus[1] = ((register_status_value&0xff));

    datamock_registerStatus[2] = bh1750_crate_Checksum(datamock_registerStatus, 2);



    bh1750_i2c_Write_test(0x44, 0xF32D);

    bh1750_i2c_Read_test(0x44, datamock_registerStatus, 3);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((SHT30_isHeaterEnabled())), (UNITY_INT)(UNITY_INT8 )((0)), (

   ((void *)0)

   ), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_INT8);

}



void test_function_sht32_ReadTempHum(void)

{

    float temp_value, hum_value;

    uint8_t datamock_registerStatus[6];

    uint16_t register_temperature_value = 0x6AF1, register_humidity_value = 0xFC18;



    datamock_registerStatus[0] = ((register_temperature_value&0xff00)>>8u);

    datamock_registerStatus[1] = ((register_temperature_value&0xff));

    datamock_registerStatus[2] = bh1750_crate_Checksum(datamock_registerStatus, 2);



    datamock_registerStatus[3] = ((register_humidity_value&0xff00)>>8u);

    datamock_registerStatus[4] = ((register_humidity_value&0xff));

    datamock_registerStatus[5] = bh1750_crate_Checksum(&datamock_registerStatus[3], 2);



    bh1750_i2c_Write_test(0x44, 0x2C06);

    bh1750_i2c_Read_test(0x44, datamock_registerStatus, 6);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((SHT30_ReadTempHum(&temp_value, &hum_value))), (UNITY_INT)(UNITY_INT8 )((1)), (

   ((void *)0)

   ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_INT8);

    printf("Temp: %f - Hum: %f \n", temp_value, hum_value);

}



void bh1750_i2c_Write_test(uint8_t Addr, uint16_t data)

{

    uint8_t Sendbuffer[2] = {((data&0xff00)>>8u), (data&0xff)};

    I2C_Start_CMockExpect(81);

    I2C_Write_add_CMockExpect(82, Addr<<1, 0x0);

    I2C_Write_CMockExpect(83, Sendbuffer[0]);

    I2C_Write_CMockExpect(84, Sendbuffer[1]);

    I2C_Stop_CMockExpect(85);

}



void bh1750_i2c_Read_test(uint8_t Addr, uint8_t* datainput, uint8_t len)

{

    uint8_t i;

    I2C_Start_CMockExpect(91);

    I2C_Write_add_CMockExpect(92, Addr<<1, 0x1);



    for(i=0; i<len; i++)

    {

        if(i == (len-1))

        {

            I2C_Read_NAK_CMockExpectAndReturn(98, datainput[i]);

        }

        else

        {

            I2C_Read_ACK_CMockExpectAndReturn(102, datainput[i]);

        }

    }

}



uint8_t bh1750_crate_Checksum(uint8_t *data, int len)

{

  const uint8_t POLYNOMIAL = 0x31;

  uint8_t crc = 0xFF;



  for (int j = len; j; --j)

  {

    crc ^= *data++;

    for (int i = 8; i; --i)

    {

      crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);

    }

  }

  return crc;

}
