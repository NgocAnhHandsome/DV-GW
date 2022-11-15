#include "src/user/bh1750.h"
#include "build/test/mocks/mock_i2c.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


extern uint8_t Bh1750_Mode;

void bh1750_i2c_Write_test(uint8_t Addr, uint8_t data);

void bh1750_i2c_Read_test(uint8_t Addr, uint8_t* data, uint8_t len);



void setUp(void)

{

}



void tearDown(void)

{

}



void test_function_bh1750_Reset(void)

{

    bh1750_i2c_Write_test(0x23, 0x07);

    BH1750_Reset();

}



void test_function_bh1750_PowerState(void)

{

    bh1750_i2c_Write_test(0x23, 0x01);

    BH1750_PowerState( 0x01);



    bh1750_i2c_Write_test(0x23, 0x00);

    BH1750_PowerState( 0x00);

}



void test_function_bh1750_SetMtreg(void)

{

    uint8_t tmp[2] = {0}, Mtreg;

    Mtreg = 69;

    tmp[0] = (0x40 | (Mtreg >> 5));

    tmp[1] = (0x60 | (Mtreg & 0x1F));



    bh1750_i2c_Write_test(0x23, tmp[0]);

    bh1750_i2c_Write_test(0x23, tmp[1]);

    BH1750_SetMtreg(Mtreg);



    Mtreg = 0;

    bh1750_i2c_Write_test(0x23, tmp[0]);

    bh1750_i2c_Write_test(0x23, tmp[1]);

    BH1750_SetMtreg(Mtreg);



    Mtreg = 255;

    bh1750_i2c_Write_test(0x23, tmp[0]);

    bh1750_i2c_Write_test(0x23, tmp[1]);

    BH1750_SetMtreg(Mtreg);



    Mtreg = 40;

    tmp[0] = (0x40 | (Mtreg >> 5));

    tmp[1] = (0x60 | (Mtreg & 0x1F));

    bh1750_i2c_Write_test(0x23, tmp[0]);

    bh1750_i2c_Write_test(0x23, tmp[1]);

    BH1750_SetMtreg(Mtreg);

}



void test_function_bh1750_SetMode()

{

    bh1750_i2c_Write_test(0x23, 0x10);

    BH1750_SetMode(0x10);



    bh1750_i2c_Write_test(0x23, 0x11);

    BH1750_SetMode(0x11);



    bh1750_i2c_Write_test(0x23, 0x13);

    BH1750_SetMode(0x13);



    bh1750_i2c_Write_test(0x23, 0x20);

    BH1750_SetMode(0x20);



    bh1750_i2c_Write_test(0x23, 0x21);

    BH1750_SetMode(0x21);



    bh1750_i2c_Write_test(0x23, 0x23);

    BH1750_SetMode(0x23);



}



void test_function_bh1750_ReadLight(void)

{

    float Lux;

    Bh1750_Mode = 0x13;

    I2C_Start_CMockExpect(87);

    I2C_Write_add_CMockExpect(88, 0x23<<1, 0x1);

    I2C_Read_ACK_CMockExpectAndReturn(89, 0xff);

    I2C_Read_NAK_CMockExpectAndReturn(90, 0xff);

    BH1750_ReadLight(&Lux);

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01)), (UNITY_FLOAT)((Lux)), (UNITY_FLOAT)((54612.5)), (

   ((void *)0)

   ), (UNITY_UINT)(92));

    printf("Lux: %f \n", Lux);



    Bh1750_Mode = 0x11;

    I2C_Start_CMockExpect(96);

    I2C_Write_add_CMockExpect(97, 0x23<<1, 0x1);

    I2C_Read_ACK_CMockExpectAndReturn(98, 0xff);

    I2C_Read_NAK_CMockExpectAndReturn(99, 0xff);

    BH1750_ReadLight(&Lux);

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01)), (UNITY_FLOAT)((Lux)), (UNITY_FLOAT)((27306.25)), (

   ((void *)0)

   ), (UNITY_UINT)(101));

    printf("Lux: %f \n", Lux);





    Bh1750_Mode = 0x21;

    I2C_Start_CMockExpect(106);

    I2C_Write_add_CMockExpect(107, 0x23<<1, 0x1);

    I2C_Read_ACK_CMockExpectAndReturn(108, 0xff);

    I2C_Read_NAK_CMockExpectAndReturn(109, 0xff);

    BH1750_ReadLight(&Lux);

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01)), (UNITY_FLOAT)((Lux)), (UNITY_FLOAT)((27306.25)), (

   ((void *)0)

   ), (UNITY_UINT)(111));

    printf("Lux: %f \n", Lux);

}



void test_function_bh1750_Init(void)

{

    uint8_t tmp[2] = {0}, Mtreg;

    Mtreg = 69;

    tmp[0] = (0x40 | (Mtreg >> 5));

    tmp[1] = (0x60 | (Mtreg & 0x1F));



    I2C_Init_CMockExpect(122, 100000);

    bh1750_i2c_Write_test(0x23, 0x07);

    bh1750_i2c_Write_test(0x23, tmp[0]);

    bh1750_i2c_Write_test(0x23, tmp[1]);

    bh1750_i2c_Write_test(0x23, 0x01);

    bh1750_i2c_Write_test(0x23, 0x13);



    BH1750_Init(0x13, 0x01);

}



void bh1750_i2c_Write_test(uint8_t Addr, uint8_t data)

{

    I2C_Start_CMockExpect(134);

    I2C_Write_add_CMockExpect(135, Addr<<1, 0x0);

    I2C_Write_CMockExpect(136, data);

    I2C_Stop_CMockExpect(137);

}
