/**
  ******************************************************************************
  * @file    trajectoryGenerator.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    06/02/2016
  * @brief   trajectory Generator
  *
 *******************************************************************************/

#ifndef _TRAJECTORY_GENERATROR_H
#define _TRAJECTORY_GENERATROR_H

typedef enum{
TRAJ_FORWARD_BACK = 0,
TRAJ_TURN
}enum_trajectoryType;


typedef enum{
STATE_STOP = 0,
STATE_INIT,
STATE_PROCESS,
STATE_FORWARD,
STATE_TURN,
STATE_END
}enum_trajectoryState;

void trajectoryGenerator_forward();

typedef struct{
enum_trajectoryState state;
bool trajectoryForwardEnable;
bool trajectoryForwardFinish;
int32_t consigneX;
int32_t consigneY;
int32_t distance;
int32_t orientation;
enum_trajectoryType type;
}struct_trajectoryGenerator;


void trajectoryGenerator_type(enum_trajectoryType type);
enum_trajectoryType trajectoryGenerator_readType(void);

 #endif
// End Of File
