/**
  ******************************************************************************
  * @file    Switchs.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/

#include "Switchs.h"

/**********************************************************
 * @brief  Switchs_init
 * @param  None
 * @retval None
**********************************************************/
void Switchs_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

  // Congiguration GPIO
  GPIO_InitStruct.Pin = SWITCH1_PIN; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(SWITCH1_PORT, &GPIO_InitStruct);
}


/**********************************************************
 * @brief  Switchs_read
 * @param  None
 * @retval None
**********************************************************/
bool Switchs_read(void)
{
GPIO_PinState State;

  State = HAL_GPIO_ReadPin(SWITCH1_PORT, SWITCH1_PIN);

  if(State == GPIO_PIN_RESET)
  {
     return (false);
  }
  else
  {
    return (true);
  }

}


 // End Of file
