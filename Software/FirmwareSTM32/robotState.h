/**
  ******************************************************************************
  * @file    RobotState.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    17/07/2017
  * @brief	 Etat du robot : avance, recule, tourne a  droite, ...
  *
  * Fichier de l'état present et passé du robot.
  *
 *******************************************************************************/

#ifndef _ROBOT_STATE_H
#define _ROBOT_STATE_H

#include "Board.h"

typedef enum
{
ROBOT_STATE_STOP,// etat du robot arret
ROBOT_STATE_FORWARD,// etat avancer en avant
ROBOT_STATE_BACK,// etat reculer
ROBOT_STATE_TURN_LEFT,
ROBOT_STATE_TURN_RIGHT,
ROBOT_STATE_FORWARDC,
ROBOT_STATE_BACKC,
}enum_RobotState;

typedef struct{
enum_RobotState PresentState;// etat actuel
enum_RobotState PastState;// etat passé
uint32_t Speed;// vitesse
float Xrobot;// position x
float Yrobot;
float radOrientation;
uint32_t consigne;
}struct_RobotState;

void RobotState_init(void);

void RobotState_write(enum_RobotState State, uint32_t Speed, uint32_t consigne);

enum_RobotState RobotState_read(void);

 #endif
// End Of File
