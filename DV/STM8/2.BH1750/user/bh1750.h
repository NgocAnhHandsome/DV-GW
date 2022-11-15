/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BH1750_H__
#define __BH1750_H__

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

#define BH1750_ADDRESS_HIGH                       0x5C
#define BH1750_ADDRESS_LOW                        0x23
#define BH1750_ADDRESS                            BH1750_ADDRESS_LOW

#define BH1750_REG_POWER_ON                       0x01
#define BH1750_REG_POWER_OFF                      0x00
#define BH1750_REG_RESET                          0x07
#define BH1750_REG_CONT_HIGH                      0x10
#define BH1750_REG_CONT_HIGH2                     0x11
#define BH1750_REG_CONT_LOW                       0x13
#define BH1750_REG_ONCE_HIGH                      0x20
#define BH1750_REG_ONCE_HIGH2                     0x21
#define BH1750_REG_ONCE_LOW                       0x23
#define BH1750_DEFAULT_MTREG	                    69

#define BH1750_MODE_LOW                           0x00
#define BH1750_MODE_HIGH                          0x01
#define BH1750_MODE_HIGH2                         0x02

void BH1750_Init(uint8_t ModeRead, uint8_t ON_OFF);
void BH1750_Reset(void);
void BH1750_PowerState(uint8_t PowerOn);
void BH1750_SetMtreg(uint8_t Mtreg);
void BH1750_SetMode(uint8_t Mode);
void BH1750_ReadLight(float *Result);

#endif
