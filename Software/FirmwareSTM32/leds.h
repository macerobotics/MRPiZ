/**
  ******************************************************************************
  * @file    led.c
  * @author  Ac6
  * @version V1.0
  * @date    12/06/2020
  * @brief   led
  ******************************************************************************
*/

#ifndef _LEDS_H
#define _LEDS_H


/************************************************************************
 * Defines
***********************************************************************/
#define LEDn 5 // Number of leds

typedef enum
{
  LED_ON_OFF = 0,
  LED_LOW_BATT = 1,
}Led_TypeDef;

typedef enum
{
  LED_OFF = 0,
  LED_ON = 1
}LedState;

/**
  * @brief LEDS
  */
void Leds_init(void);

void Leds_on(Led_TypeDef Led);

void Leds_Write(Led_TypeDef Led,LedState State);

void Leds_off(Led_TypeDef Led);

void Leds_toggle(Led_TypeDef Led);


#endif
// End Of File
