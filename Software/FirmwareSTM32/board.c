/**
  ******************************************************************************
  * @file    Board.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/
 #include "stm32f4xx.h"
 #include "board.h"

/************************************************************************
 * Variable definitions
***********************************************************************/



/**********************************************************
 * @brief  Board_init : control board initialisation
 * @param  None
 * @retval None
**********************************************************/
void Board_init(void)
{
  // GPIOA CLK enable
  __GPIOA_CLK_ENABLE();

  // GPIOB CLK enable
  __GPIOB_CLK_ENABLE();

  // GPIOC CLK enable
  __GPIOC_CLK_ENABLE();

  // GPIOD CLK enable
  __GPIOD_CLK_ENABLE();

  // GPIOE CLK enable
  __GPIOE_CLK_ENABLE();

  // Analog digital converter init.
  Adc_init();

  // Battery Tension init.
  BatteryTension_init();


  // Leds 1, 2 and 3 init.
  Leds_init();

  // Switch init.
  Switchs_init();

  // Charge management init.
  ChargeManagement_init();

  // Led activity init
  LedOnOff_init();


  RobotState_init();

}



 // End Of file
