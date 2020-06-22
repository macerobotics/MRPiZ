/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    12/06/20
  * @brief   motors
  ******************************************************************************
*/


#include <motors.h>
#include "stm32f4xx.h"

struct_motor s_motorRight;
struct_motor s_motorLeft;



TIM_HandleTypeDef TIMER_InitStruct;
TIM_OC_InitTypeDef TIMER_OC_InitStruct;


/**********************************************************
 * @brief  Motors_init : motor initialisation
 * @param
 * @retval None
**********************************************************/
void Motors_init(void)
{
GPIO_InitTypeDef GPIO_DIR_InitStruct;
GPIO_InitTypeDef GPIO_PWM_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOC_CLK_ENABLE();
  __GPIOD_CLK_ENABLE();

  /* GPIOD Configuration: Direction */
  GPIO_DIR_InitStruct.Pin = HBRIDGE_DIR1_PIN | HBRIDGE_DIR2_PIN; // Pin direction
  GPIO_DIR_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_DIR_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_DIR_InitStruct);

  /* GPIOE Configuration: sleep pin */
  GPIO_DIR_InitStruct.Pin = HBRIDGE_SLEEP_PIN; // Pin direction
  GPIO_DIR_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_DIR_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(HBRIDGE_SLEEP_PORT, &GPIO_DIR_InitStruct);

  /* GPIOC PWM Configuration: TIM3 CH3 (PC8) and TIM3 CH4 (PC9) */
  GPIO_PWM_InitStruct.Pin = HBRIDGE_PWM1_PIN | HBRIDGE_PWM2_PIN ;
  GPIO_PWM_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_PWM_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_PWM_InitStruct.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init(GPIOC, &GPIO_PWM_InitStruct);

    /* TIM3 Clock Enable */
  __TIM3_CLK_ENABLE();


  /* TIM3 is connected to APB1 bus : so 42MHz  clock. But PLL double this frequency => 42*2 = 84 Mhz    */
  /* Timer_Frequency = (84Mhz) / (Prescaler +1 )                                                                                                */
  /*  TIMER_Period = (Timer_Frequency) / (PWM_frequency) - 1                                                                    */

  // Init TIMER3 for 20 Khz frequency (PWM motors)
  TIMER_InitStruct.Instance = TIM3;
  TIMER_InitStruct.Init.Prescaler = 0; // Timer_Frequency = 84 Mhz.
  TIMER_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
  TIMER_InitStruct.Init.Period = 4199; //  TIMER_Period = (84M)/(20k) - 1 = 4199


  TIMER_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&TIMER_InitStruct);

  // Output Compare Configuration
  TIMER_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
  TIMER_OC_InitStruct.OCIdleState = TIM_OCIDLESTATE_SET;
  TIMER_OC_InitStruct.Pulse = 0;// PWM 0 %
  TIMER_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
  TIMER_OC_InitStruct.OCFastMode = TIM_OCFAST_ENABLE;



  HAL_TIM_PWM_ConfigChannel(&TIMER_InitStruct, &TIMER_OC_InitStruct, TIM_CHANNEL_3);
  HAL_TIM_PWM_ConfigChannel(&TIMER_InitStruct, &TIMER_OC_InitStruct, TIM_CHANNEL_4);

  HAL_TIM_PWM_Start(&TIMER_InitStruct,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&TIMER_InitStruct,TIM_CHANNEL_4);

  // Enable nsleep
  HAL_GPIO_WritePin(HBRIDGE_SLEEP_PORT, HBRIDGE_SLEEP_PIN, GPIO_PIN_SET);

  s_motorRight.speed = 0;
  s_motorLeft.speed = 0;
  s_motorRight.direction = MOTOR_FORWARD;
  s_motorLeft.direction = MOTOR_FORWARD;

}


/**********************************************************
 * @brief  Motor_right
 * @param  Direction and speed of the motor (0 to 100)
 * @retval None
**********************************************************/
void Motor_right(MotorDir_TypeDef Motor_Direction, uint32_t Motor_Speed)
{
	  s_motorRight.speed = Motor_Speed;
	  s_motorRight.direction = Motor_Direction;

	  // Direction
	  if( Motor_Direction == MOTOR_FORWARD )
	  {
		// State low
		HAL_GPIO_WritePin(HBRIDGE_DIR1_PORT, HBRIDGE_DIR1_PIN, GPIO_PIN_RESET);
	  }
	  else
	  {
		// State high
	    HAL_GPIO_WritePin(HBRIDGE_DIR1_PORT, HBRIDGE_DIR1_PIN, GPIO_PIN_SET);
	  }

	  TIMER_OC_InitStruct.Pulse = (Motor_Speed*TIMER_InitStruct.Init.Period)/100;
	  HAL_TIM_PWM_ConfigChannel(&TIMER_InitStruct, &TIMER_OC_InitStruct, TIM_CHANNEL_3);

	  HAL_TIM_PWM_Start(&TIMER_InitStruct,TIM_CHANNEL_3);


}


/**********************************************************
 * @brief  Motor_left
 * @param  Direction and speed of the motor (0 to 100)
 * @retval None
**********************************************************/
void Motor_left(MotorDir_TypeDef Motor_Direction, uint32_t Motor_Speed)
{
	  s_motorLeft.speed = Motor_Speed;
	  s_motorLeft.direction = Motor_Direction;

	  if( Motor_Direction == MOTOR_FORWARD )
	  {
		// State low
		HAL_GPIO_WritePin(HBRIDGE_DIR2_PORT, HBRIDGE_DIR2_PIN, GPIO_PIN_RESET);
	  }
	  else
	  {
		// State high
	    HAL_GPIO_WritePin(HBRIDGE_DIR2_PORT, HBRIDGE_DIR2_PIN, GPIO_PIN_SET);
	  }


	  TIMER_OC_InitStruct.Pulse = (Motor_Speed*TIMER_InitStruct.Init.Period)/100;
	  HAL_TIM_PWM_ConfigChannel(&TIMER_InitStruct, &TIMER_OC_InitStruct, TIM_CHANNEL_4);

	  HAL_TIM_PWM_Start(&TIMER_InitStruct,TIM_CHANNEL_4);

}


/**********************************************************
 * @brief  Motors_write
 * @param  Direction and speed of the motor (0 to 100)
 * @retval None
**********************************************************/
void Motors_write(MotorDir_TypeDef Motor_DirectionRight,
		          MotorDir_TypeDef Motor_DirectionLeft,
		          uint32_t Motor_SpeedRight,
		          uint32_t Motor_SpeedLeft)
{

  Motor_right(Motor_DirectionRight, Motor_SpeedRight);
  Motor_left(Motor_DirectionLeft, Motor_SpeedLeft);

}


/**********************************************************
 * @brief  Motors_stop
 * @param  Direction and speed of the motor (0 to 100)
 * @retval None
**********************************************************/
void Motors_stop(void)
{
	  TIMER_OC_InitStruct.Pulse = 0;
	  HAL_TIM_PWM_ConfigChannel(&TIMER_InitStruct, &TIMER_OC_InitStruct, TIM_CHANNEL_3);
	  HAL_TIM_PWM_ConfigChannel(&TIMER_InitStruct, &TIMER_OC_InitStruct, TIM_CHANNEL_4);

	  HAL_TIM_PWM_Start(&TIMER_InitStruct,TIM_CHANNEL_3);
	  HAL_TIM_PWM_Start(&TIMER_InitStruct,TIM_CHANNEL_4);

	  s_motorRight.speed = 0;
	  s_motorLeft.speed = 0;

}


/**********************************************************
 * @brief  MotorRight_speed
 * @param  None
 * @retval speed
**********************************************************/
uint32_t MotorRight_speedRead()
{
  return(s_motorRight.speed);
}


/**********************************************************
 * @brief  MotorLeft_speed
 * @param  None
 * @retval speed
**********************************************************/
uint32_t MotorLeft_speedRead()
{
	return(s_motorLeft.speed);
}


/**********************************************************
 * @brief  MotorRight_speedWrite
 * @param  None
 * @retval speed
**********************************************************/
void MotorRight_speedWrite(uint32_t Motor_Speed)
{
  s_motorRight.speed = Motor_Speed;

  Motor_right(s_motorRight.direction, s_motorRight.speed);
}


/**********************************************************
 * @brief  MotorLeft_speedWrite
 * @param  None
 * @retval speed
**********************************************************/
void MotorLeft_speedWrite(uint32_t Motor_Speed)
{
  s_motorLeft.speed = Motor_Speed;

  Motor_left(s_motorLeft.direction, s_motorLeft.speed);
}

/**********************************************************
 * @brief  Motors_disable
 * @param  None
 * @retval speed
**********************************************************/
void Motors_disable(void)
{
  HAL_GPIO_WritePin(HBRIDGE_SLEEP_PORT, HBRIDGE_SLEEP_PIN, GPIO_PIN_RESET);
}

/**********************************************************
 * @brief  Motors_disable
 * @param  None
 * @retval speed
**********************************************************/
void Motors_enable(void)
{
	  HAL_GPIO_WritePin(HBRIDGE_SLEEP_PORT, HBRIDGE_SLEEP_PIN, GPIO_PIN_SET);
}

/**********************************************************
 * @brief  Motors_brake
 * @param  None
 * @retval none
**********************************************************/
void Motors_brake(void)
{
	HAL_GPIO_WritePin(HBRIDGE_PWM1_PORT, HBRIDGE_PWM1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HBRIDGE_PWM2_PORT, HBRIDGE_PWM2_PIN, GPIO_PIN_RESET);
}




 // End Of file
