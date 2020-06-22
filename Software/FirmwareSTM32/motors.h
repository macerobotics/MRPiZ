/**
  ******************************************************************************
  * @file    Motors.h
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief	Motors
  *
 *******************************************************************************/

#ifndef _MOTORS_H
#define _MOTORS_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/
#define MOTOR_CMD_MAX 100

#define MOTOR_PERIOD_PWM 140 // Period for 20Khz frequency



typedef enum
{
  MOTOR_FORWARD,
  MOTOR_BACK
}MotorDir_TypeDef;


typedef struct{
uint32_t speed;
MotorDir_TypeDef direction;
}struct_motor;



void Motors_init(void); // initialisation of the motors
void Motor_right(MotorDir_TypeDef Motor_Direction, uint32_t Motor_Speed); // direction and speed for the right motor
void Motor_left(MotorDir_TypeDef Motor_Direction, uint32_t Motor_Speed); // direction and speed for the left motor

void Motors_write(MotorDir_TypeDef Motor_DirectionRight, MotorDir_TypeDef Motor_DirectionLeft, uint32_t Motor_SpeedRight, uint32_t Motor_SpeedLeft); // direction and speed for the left motor

void Motors_stop(void);

void Motors_brake(void);

uint32_t MotorRight_speedRead(); // return motor speed
uint32_t MotorLeft_speedRead(); // return motor speed

void MotorRight_speedWrite(uint32_t Motor_Speed);
void MotorLeft_speedWrite(uint32_t Motor_Speed);

void Motors_disable(void);
void Motors_enable(void);

 #endif
// End Of File
