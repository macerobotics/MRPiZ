/**
  ******************************************************************************
  * @file    led.c
  * @author  Ac6
  * @version V1.0
  * @date    12/06/2020
  * @brief   led
  ******************************************************************************
*/

 #include <leds.h>
#include "board.h"


/**********************************************************
 * @brief  Leds_init : led initialisation
 * @param  None
 * @retval None
**********************************************************/
void Leds_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;


	// configuration en sortie
	GPIO_InitStruct.Pin = LED1_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED1_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);


}


/**********************************************************
 * @brief  Leds_on : leds on
 * @param  None
 * @retval None
**********************************************************/
void Leds_on(Led_TypeDef Led)
{
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);
}

/**********************************************************
 * @brief  Leds_off : leds off
 * @param  None
 * @retval None
**********************************************************/
void Leds_off(Led_TypeDef Led)
{
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
}


/**********************************************************
 * @brief  Leds_Write
 * @param  None
 * @retval None
**********************************************************/
void Leds_Write(Led_TypeDef Led,LedState State)
{

}


/**********************************************************
 * @brief  Leds_toggle
 * @param  None
 * @retval None
**********************************************************/
void Leds_toggle(Led_TypeDef Led)
{
	HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
}

// end of file


