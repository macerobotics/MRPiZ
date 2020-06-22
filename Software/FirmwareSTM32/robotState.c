/**
  ******************************************************************************
  * @file    RobotState.c
  * @author  Mace Robotics (www.macerobotics.com)
  * @version V1.0
  * @date    26/06/2017
  * @brief
  *
  *
 *******************************************************************************/
#include "robotState.h"

static struct_RobotState RobotState;


/**********************************************************
 * @brief  RobotState_init
 * @param
 * @retval None
**********************************************************/
void RobotState_init(void)
{
  RobotState.PresentState = ROBOT_STATE_STOP;
  RobotState.PastState = ROBOT_STATE_STOP;
  RobotState.Speed = 0;
  RobotState.consigne = 0;
}

/**********************************************************
 * @brief  RobotState_write
 * @param
 * @retval None
**********************************************************/
void RobotState_write(enum_RobotState State, uint32_t Speed, uint32_t consigne)
{
  if(State != RobotState.PresentState)
  {
    RobotState.PastState = RobotState.PresentState;
    RobotState.PresentState = State;

    if(RobotState.PresentState != ROBOT_STATE_STOP)
      RobotState.Speed = Speed;

    if(RobotState.PresentState == ROBOT_STATE_FORWARDC)
      RobotState.consigne = consigne;
  }

  RobotState.Xrobot = positionControl_stepX();
  RobotState.Xrobot = positionControl_stepY();

}


/**********************************************************
 * @brief  RobotState_read
 * @param  None
 * @retval Robot State (Stop, forward, ...)
**********************************************************/
enum_RobotState RobotState_read(void)
{
  return(RobotState.PresentState);

}

 // End Of file
