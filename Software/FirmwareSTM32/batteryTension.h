/**
  ******************************************************************************
  * @file    BatteryTension.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    16/11/2015
  * @brief	 Read the battery tension
  *
 *******************************************************************************/

#ifndef _BATTERY_TENSION_H
#define _BATTERY_TENSION_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/
#define BATTERY_TENSION_CHANNEL 0 // Adc PA0

/**
  * @brief BatteryTension
  */
void BatteryTension_init(void);

// to get analog value of battery Tension
float BatteryTension_get(void);

void BatteryTension_check(void);


 #endif
// End Of File
