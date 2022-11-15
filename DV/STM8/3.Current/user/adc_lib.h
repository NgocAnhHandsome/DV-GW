
#ifndef __ADC_H__
#define __ADC_H__

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

typedef struct
{
	float ADC_OLD_Value;
	float P_k1_k1;

	float Q;
	float R; 
	float Kg;
	float P_k_k1;
	float kalman_adc_old;
	
	uint8_t init_data;
}_adc_kalman_filter_t_;
extern _adc_kalman_filter_t_ Kalman_Var_AIN3;

extern volatile uint16_t Adc_AIN3_Data;

uint16_t ADC_Read(const uint8_t channel, uint8_t number_read);
uint16_t ADC_Kalman_Filter(unsigned long ADC_Value, _adc_kalman_filter_t_ *_adc_kalman_);

#endif /* __STM8S_UART1_H */
