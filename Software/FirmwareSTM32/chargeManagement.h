/**
  ******************************************************************************
  * @file    ChargeManagement.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    16/11/2015
  * @brief	Charge Battery Management
  *
 *******************************************************************************/

#ifndef _CHARGEMANAGEMENT_H
#define _CHARGEMANAGEMENT_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/


/**
  * @brief ChargeManagement
  */
void ChargeManagement_init(void);

void ChargeManagement_Put500mACharge(void);

float ChargeManagement_readVUSB(void);



 #endif
// End Of File
