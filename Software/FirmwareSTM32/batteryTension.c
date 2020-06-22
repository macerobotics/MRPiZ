/**
  ******************************************************************************
  * @file    BatteryTension.c
  * @author  Mace Robotics
  * @version V1.1
  * @date    29/10/2017
  * @brief  Read battery tension
  *
 *******************************************************************************/

#include "batteryTension.h"


/**********************************************************
 * @brief  BatteryTension_init
 * @param  None
 * @retval None
**********************************************************/
void BatteryTension_init(void)
{
GPIO_InitTypeDef  Batt_InitStruct;

  // Configure Battery tension pin as analog input
  Batt_InitStruct.Pin = BATT_PIN;
  Batt_InitStruct.Mode = GPIO_MODE_ANALOG; // Analog mode
  Batt_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BATT_PORT, &Batt_InitStruct);
}


/**********************************************************
 * @brief  Get the battery tension
 * @param  None
 * @retval tension of the battery
**********************************************************/
float BatteryTension_get(void)
{
float BatteryTension = 0;
static float old_tension[2] = {4.2, 4.2};

  // Tension = ADC value *3.3 x 2
  BatteryTension = (float)Adc_read(BATTERY_TENSION_CHANNEL); // Read adc value.

  // ADC (12 bits)
  old_tension[0] = old_tension[1];

  BatteryTension = (BatteryTension*6.6)/(4095);
  BatteryTension = (BatteryTension + old_tension[0] + old_tension[1])/3;
  old_tension[1] = BatteryTension;


  return BatteryTension;
}


/**********************************************************
 * @brief  Battery Tension_get
 * @param  None
 * @retval None
**********************************************************/
void BatteryTension_check(void)
{
float tension1;

  // read battery tension
  tension1 = BatteryTension_get();

  // battery to low
  if(tension1 < 3.5)// 3.5V pour Li-ion
  {

	  while(1)
	  {
		  Leds_off(LED_ON_OFF); // led ON/OFF
		  Leds_on(LED_LOW_BATT); // LOW battery
		  MoveRobot_stop();// stop

	  }
  }

}


 // End Of file
