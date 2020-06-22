/**
  ******************************************************************************
  * @file    ChargeManagement.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    16/11/2015
  * @brief  Charge Battery Management
  *
 *******************************************************************************/

#include "ChargeManagement.h"


/**********************************************************
 * @brief  ChargeManagement_init : charge management initialisation
 * @param  None
 * @retval None
**********************************************************/
void ChargeManagement_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;
GPIO_InitTypeDef  VUSB_InitStruct;

  /* Configuration  gpio */
  GPIO_InitStruct.Pin =  USB_PRESENT_PIN; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // GPIO mode input
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

 /* Configuration  gpio */
 GPIO_InitStruct.Pin =  USB_CURRENT_PIN; // Pin
 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
 HAL_GPIO_Init(USB_CURRENT_PORT, &GPIO_InitStruct);


  // Configure VUSB pin as analog input
  VUSB_InitStruct.Pin = USB_VOLTAGE_PIN;
  VUSB_InitStruct.Mode = GPIO_MODE_ANALOG; // Analog mode
  VUSB_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_VOLTAGE_PORT, &VUSB_InitStruct);

}


/**********************************************************
 * @brief  ChargeManagement_Put500mACharge
 * @param  None
 * @retval None
**********************************************************/
void ChargeManagement_Put500mACharge(void)
{

  HAL_GPIO_WritePin(USB_CURRENT_PORT, USB_CURRENT_PIN, GPIO_PIN_RESET);

}


/**********************************************************
 * @brief  ChargeManagement_readVUSB
 * @param  None
 * @retval None
**********************************************************/
float ChargeManagement_readVUSB(void)
{
float Vusb_tension = 0;

  // Tension = ADC value *3.3 x 2
  Vusb_tension = (float)Adc_read(10); // Read adc value.

  Vusb_tension = (Vusb_tension*6.6)/(4095);

  return(Vusb_tension);

}


 // End Of file
