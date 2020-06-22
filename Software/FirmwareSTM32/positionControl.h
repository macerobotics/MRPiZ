/**
  ******************************************************************************
  * @file    positionControl.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    29/12/2015
  * @brief	control position robot
  *
 *******************************************************************************/

#ifndef _POSITION_CONTROL_H
#define _POSITION_CONTROL_H

#include "Board.h"

#define PI (float)(3.1415926)

/*****************************************/
/* Mecanic Robot MRPi1 *******************/
#define PERIMETER_ROBOT_MM 273 // Robot perimeter (mm)
#define PERIMETER_WHEEL (float)(100.053) // wheels permimeter (mm)
//#define ENCODEURS_RESOLUTION 3576 // tick pour 1 tour de roue.
#define ENCODEURS_RESOLUTION 400 // tick pour 1 tour de roue.
/*****************************************/

// Coef angle radian =
// (PI/2)/((TAILLE_ESSIEU_MM*RESOLUTION_ENCODEURS)/(PERIMETRE_ROUE))/2.0
#define COEFF_ANGLE_RADIAN (float)((PI/2)/(((PERIMETER_ROBOT_MM*ENCODEURS_RESOLUTION)/(PERIMETER_WHEEL))/2.0))


typedef struct{
float stepDistance; // step distance of the robot
float old_stepDistance;
float stepOrientation; // step orientation of the robot
float stepSpeed_distance;
float stepSpeed_orientation;
float Xrobot;
float Yrobot;
float radOrientation;
float speedMotorRight;
float speedMotorLeft;
}struct_postionRobot;


void positionControl_init(void);

void positionControl(void);

int32_t positionControl_stepDistance(void);
int32_t positionControl_stepSpeedDistance(void);

int32_t positionControl_stepOrientation(void);

float positionControl_Orientation(void);// radian
int32_t positionControl_stepSpeedOrientation(void);


float positionControl_stepX(void);
float positionControl_stepY(void);

void positionControl_Reset(void);

float positionControl_speedLeft(void);
float positionControl_speedRight(void);

 #endif
// End Of File
