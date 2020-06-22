/**
  ******************************************************************************
  * @file    MoveRobot.h
  * @author  Mace Robotics
  * @version V1.1
  * @date    26/06/2017
  * @brief	MoveRobot
  *
 *******************************************************************************/

#ifndef _MoveRobot_H
#define _MoveRobot_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/

void MoveRobot_init(void);
void MoveRobot_forward(uint32_t Speed);
void MoveRobot_back(uint32_t Speed);
void MoveRobot_turn_right(uint32_t Speed);
void MoveRobot_turn_left(uint32_t Speed);
void MoveRobot_stop(void);
void MoveRobot_Go(uint32_t Speed, uint32_t coord_X, uint32_t coord_Y);
void MoveRobot_turn(uint32_t Speed, uint32_t Angle);


 #endif
// End Of File
