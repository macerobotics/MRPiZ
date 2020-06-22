/**
  ******************************************************************************
  * @file    LedOnOff.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    12/06/20
  * @brief	led on/off
  *
 *******************************************************************************/

#ifndef _LEDONOFF_H
#define _LEDONOFF_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/


/**
  * @brief LedOnOff
  */
void LedOnOff_init(void);

void TIM5_IRQHandler(void);



#endif
// End Of File
