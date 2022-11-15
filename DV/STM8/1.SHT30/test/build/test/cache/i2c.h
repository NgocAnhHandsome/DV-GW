#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


void I2C_Init(uint32_t Speed);



void I2C_Start(void);

void I2C_Stop(void);

void I2C_Write(uint8_t data);

void I2C_Write_add(uint8_t data, uint8_t mode);

uint8_t I2C_Read_NAK(void);

uint8_t I2C_Read_ACK(void);

uint16_t I2C_Read_arr(void);
