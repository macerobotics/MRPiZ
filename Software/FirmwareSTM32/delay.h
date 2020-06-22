/**
  ******************************************************************************
  * @file    Delay.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    17/07/2017
  * @brief
  *
  *
  *
 *******************************************************************************/

#ifndef _DELAY_H
#define _DELAY_H

#include "Board.h"

void Delay_init(void);
void TIM2_IRQHandler(void);

uint32_t millis(void);

void delay_ms(void);

#endif
// End Of File
