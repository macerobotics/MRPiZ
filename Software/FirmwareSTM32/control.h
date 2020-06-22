/**
  ******************************************************************************
  * @file    control.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    29/12/2015
  * @brief	control
  *
 *******************************************************************************/

#ifndef _CONTROL_H
#define _CONTROL_H

#include "Board.h"

typedef enum{
CONTROL_ENABLE = 0,
CONTROL_DISABLE
}enum_Control;

// gain correct

#define GAIN_P_DISTANCE (float)(110)
#define GAIN_I_DISTANCE (float)(0)
#define GAIN_P_ORIENTATION (float)(300)//255
#define GAIN_COM (float)(100)




void controlManage(int32_t distanceCommand, int32_t orientationCommand );

void controlWrite(int32_t distanceCommand );

void controlEnable(bool state);
bool controlState(void);




 #endif
// End Of File
