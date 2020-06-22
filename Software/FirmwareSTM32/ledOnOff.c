/**
  ******************************************************************************
  * @file    LedOnOff.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    16/11/2015
  * @brief   Led On Off (green led)
  *
 *******************************************************************************/
#include <stdbool.h>
#include "ledOnOff.h"
#include "leds.h"

/************************************************************************
 * Private functions
***********************************************************************/
static void LedOnOff_init_timer(void);

/************************************************************************
 * Variable definitions
***********************************************************************/
TIM_HandleTypeDef TIMER5_InitStruct;


/**********************************************************
 * @brief  LedOnOff_init
 * @param  None
 * @retval None
**********************************************************/
void LedOnOff_init(void)
{

  // Init timer
  LedOnOff_init_timer();
}


/**********************************************************
 * @brief  TIM5_IRQHandler
 * @param  None
 * @retval None
**********************************************************/
void TIM5_IRQHandler(void)
{
static uint8_t state=0;

  if (__HAL_TIM_GET_FLAG(&TIMER5_InitStruct, TIM_FLAG_UPDATE) != RESET)
  {
    if (__HAL_TIM_GET_ITSTATUS(&TIMER5_InitStruct, TIM_IT_UPDATE) != RESET)
	{
	  __HAL_TIM_CLEAR_FLAG(&TIMER5_InitStruct, TIM_FLAG_UPDATE);

      // led ON/OFF  toggle
	  Leds_toggle(LED_ON_OFF);



	  state++;

	   // check the battery (every second)
	   if(state > 1)
	   {
	     // check the battery
	     BatteryTension_check();
		 state = 0;
	   }

	}
  }
}


/**********************************************************
 * @brief  LedOnOff_init_timer
 * @param  None
 * @retval None
**********************************************************/
static void LedOnOff_init_timer(void)
{
  // TIM5 Clock Enable
  __TIM5_CLK_ENABLE();

  // timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)

  // Timer 5 init structure (Timer period = 500ms)
  TIMER5_InitStruct.Instance = TIM5;
  TIMER5_InitStruct.Init.Prescaler = 1999; // SCLK/4 = 42MHz  => Timer_Frequency =  42Mhz/(1999+1) = 21khz
  TIMER5_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
  TIMER5_InitStruct.Init.Period = 20999; //  TIMER_Period = (21Khz)/(1Hz) - 1 = 10500 => 500 ms
  TIMER5_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

  // Init timer
  HAL_TIM_Base_Init(&TIMER5_InitStruct);

  // Start timer interrupt
  HAL_TIM_Base_Start_IT(&TIMER5_InitStruct);

  // Init timer priority
  HAL_NVIC_SetPriority(TIM5_IRQn, 0, 1);

  // Enable interrupt.
  HAL_NVIC_EnableIRQ(TIM5_IRQn);

}

 // End Of file
