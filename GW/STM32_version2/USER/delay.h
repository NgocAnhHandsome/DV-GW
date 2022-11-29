/*
  ******************************************************************************
  * @file		delay.h                                                              *
  * @author	Luu Ngoc Anh                                                       *
  * @date		18/07/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __DELAY__H
#define __DELAY__H

#ifdef __cplusplus
 extern "C" {
#endif
void Delay_Init(void);
void Delay_Us(unsigned int Time_Us);
void Delay_Ms(unsigned int Time_Ms);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/