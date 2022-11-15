#ifdef TEST
#include "unity.h"
#include "mock_i2c.h"
#include "bh1750.h"
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
    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_RESET);
    BH1750_Reset();
}

void test_function_bh1750_PowerState(void)
{
    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_POWER_ON);
    BH1750_PowerState( BH1750_REG_POWER_ON);

    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_POWER_OFF);
    BH1750_PowerState( BH1750_REG_POWER_OFF);
}

void test_function_bh1750_SetMtreg(void)
{
    uint8_t tmp[2] = {0}, Mtreg;
    Mtreg = BH1750_DEFAULT_MTREG;
    tmp[0] = (0x40 | (Mtreg >> 5));
    tmp[1] = (0x60 | (Mtreg & 0x1F));

    bh1750_i2c_Write_test(BH1750_ADDRESS, tmp[0]);
    bh1750_i2c_Write_test(BH1750_ADDRESS, tmp[1]);
    BH1750_SetMtreg(Mtreg);

    Mtreg = 0;
    bh1750_i2c_Write_test(BH1750_ADDRESS, tmp[0]);
    bh1750_i2c_Write_test(BH1750_ADDRESS, tmp[1]);
    BH1750_SetMtreg(Mtreg);

    Mtreg = 255;
    bh1750_i2c_Write_test(BH1750_ADDRESS, tmp[0]);
    bh1750_i2c_Write_test(BH1750_ADDRESS, tmp[1]);
    BH1750_SetMtreg(Mtreg);

    Mtreg = 40;
    tmp[0] = (0x40 | (Mtreg >> 5));
    tmp[1] = (0x60 | (Mtreg & 0x1F));
    bh1750_i2c_Write_test(BH1750_ADDRESS, tmp[0]);
    bh1750_i2c_Write_test(BH1750_ADDRESS, tmp[1]);
    BH1750_SetMtreg(Mtreg);
}

void test_function_bh1750_SetMode()
{
    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_CONT_HIGH);
    BH1750_SetMode(BH1750_REG_CONT_HIGH);

    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_CONT_HIGH2);
    BH1750_SetMode(BH1750_REG_CONT_HIGH2);

    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_CONT_LOW);
    BH1750_SetMode(BH1750_REG_CONT_LOW);

    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_ONCE_HIGH);
    BH1750_SetMode(BH1750_REG_ONCE_HIGH);

    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_ONCE_HIGH2);
    BH1750_SetMode(BH1750_REG_ONCE_HIGH2);

    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_ONCE_LOW);
    BH1750_SetMode(BH1750_REG_ONCE_LOW);

}

void test_function_bh1750_ReadLight(void)
{
    float Lux;
    Bh1750_Mode = BH1750_REG_CONT_LOW;
    I2C_Start_Expect();
    I2C_Write_add_Expect(BH1750_ADDRESS<<1, 0x1);
    I2C_Read_ACK_ExpectAndReturn(0xff);
    I2C_Read_NAK_ExpectAndReturn(0xff);
    BH1750_ReadLight(&Lux);
    TEST_ASSERT_FLOAT_WITHIN(0.01,Lux, 54612.5);
    printf("Lux: %f \n", Lux);

    Bh1750_Mode = BH1750_REG_CONT_HIGH2;
    I2C_Start_Expect();
    I2C_Write_add_Expect(BH1750_ADDRESS<<1, 0x1);
    I2C_Read_ACK_ExpectAndReturn(0xff);
    I2C_Read_NAK_ExpectAndReturn(0xff);
    BH1750_ReadLight(&Lux);
    TEST_ASSERT_FLOAT_WITHIN(0.01,Lux, 27306.25);
    printf("Lux: %f \n", Lux);

    
    Bh1750_Mode = BH1750_REG_ONCE_HIGH2;
    I2C_Start_Expect();
    I2C_Write_add_Expect(BH1750_ADDRESS<<1, 0x1);
    I2C_Read_ACK_ExpectAndReturn(0xff);
    I2C_Read_NAK_ExpectAndReturn(0xff);
    BH1750_ReadLight(&Lux);
    TEST_ASSERT_FLOAT_WITHIN(0.01,Lux, 27306.25);
    printf("Lux: %f \n", Lux);
}

void test_function_bh1750_Init(void)
{
    uint8_t tmp[2] = {0}, Mtreg;
    Mtreg = BH1750_DEFAULT_MTREG;
    tmp[0] = (0x40 | (Mtreg >> 5));
    tmp[1] = (0x60 | (Mtreg & 0x1F));

    I2C_Init_Expect(100000);
    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_RESET);
    bh1750_i2c_Write_test(BH1750_ADDRESS, tmp[0]);
    bh1750_i2c_Write_test(BH1750_ADDRESS, tmp[1]);
    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_POWER_ON);
    bh1750_i2c_Write_test(BH1750_ADDRESS, BH1750_REG_CONT_LOW);

    BH1750_Init(BH1750_REG_CONT_LOW, BH1750_REG_POWER_ON);
}

void bh1750_i2c_Write_test(uint8_t Addr, uint8_t data)
{
    I2C_Start_Expect();
    I2C_Write_add_Expect(Addr<<1, 0x0);
    I2C_Write_Expect(data);
    I2C_Stop_Expect();
}

#endif // TEST

