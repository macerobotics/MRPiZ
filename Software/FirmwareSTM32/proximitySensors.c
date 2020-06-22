/**
  ******************************************************************************
  * @file    ProxSensors.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    18/11/2017
  * @brief
  *
 *******************************************************************************/
#include <stdbool.h>
#include <vl6180x/vl6180x.h>
#include "stm32f4xx.h"
#include "ProximitySensors.h"
#include "Board.h"

/************************************************************************
 * Private functions
***********************************************************************/


/************************************************************************
 * Variable definitions
***********************************************************************/
GPIO_TypeDef* XSHUT_PORT[PROXn] = {PROX1_XSHUT_PORT, PROX1_XSHUT_PORT, PROX1_XSHUT_PORT, PROX1_XSHUT_PORT, PROX1_XSHUT_PORT};

const uint16_t XSHUT_PIN[PROXn] = {PROX1_XSHUT_PIN, PROX2_XSHUT_PIN, PROX3_XSHUT_PIN, PROX4_XSHUT_PIN, PROX5_XSHUT_PIN};

uint16_t tab_proxSensors[PROXn];

uint8_t tab_proxSensorsEnable[PROXn];





/**********************************************************
 * @brief  ProxSensorsVL6180_init
 * @param  None
 * @retval None
**********************************************************/
void ProxSensorsVL6180_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;
GPIO_InitTypeDef GPIO_InitStruct2;
uint8_t presence_sensor, c=0;


  // Configuration  gpio of the XSHUT
  GPIO_InitStruct.Pin = PROX1_XSHUT_PIN | PROX2_XSHUT_PIN; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = PROX3_XSHUT_PIN | PROX4_XSHUT_PIN; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = PROX5_XSHUT_PIN; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  delay_ms();


  // mise en reset
  HAL_GPIO_WritePin(XSHUT_PORT[0], XSHUT_PIN[0], GPIO_PIN_RESET);
  HAL_GPIO_WritePin(XSHUT_PORT[1], XSHUT_PIN[1], GPIO_PIN_RESET);
  HAL_GPIO_WritePin(XSHUT_PORT[2], XSHUT_PIN[2], GPIO_PIN_RESET);
  HAL_GPIO_WritePin(XSHUT_PORT[3], XSHUT_PIN[3], GPIO_PIN_RESET);
  HAL_GPIO_WritePin(XSHUT_PORT[4], XSHUT_PIN[4], GPIO_PIN_RESET);

  delay_ms();

  // configuration en entrée PROX1
  HAL_GPIO_DeInit(GPIOA,PROX1_XSHUT_PIN);
  GPIO_InitStruct2.Pin = PROX1_XSHUT_PIN; // Pin
  GPIO_InitStruct2.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct2);

  delay_ms();

  VL6180X_init();

  VL6180X_configureDefault();

  presence_sensor = VL6180X_setAddress(ADDRESS_DEFAULT_VL6180X, ADR_PROX1);
  tab_proxSensorsEnable[0] = presence_sensor;// presence ou non du capteur dans le connecteur 7 pins




  /////////////// FIN CONFIG PROX1

  // configuration en entrée PROX2
  HAL_GPIO_DeInit(GPIOA,PROX2_XSHUT_PIN);
  GPIO_InitStruct2.Pin = PROX2_XSHUT_PIN; // Pin
  GPIO_InitStruct2.Mode = GPIO_MODE_INPUT; // GPIO mode output
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct2);

  delay_ms();

  VL6180X_init();
  VL6180X_configureDefault();
  presence_sensor = VL6180X_setAddress(ADDRESS_DEFAULT_VL6180X, ADR_PROX2);
  tab_proxSensorsEnable[1] = presence_sensor;// presence ou non du capteur dans le connecteur 7 pins

  /////////////// FIN CONFIG PROX2

  // confiuguration en entrée PROX3
  HAL_GPIO_DeInit(GPIOD,PROX3_XSHUT_PIN);
  GPIO_InitStruct2.Pin = PROX3_XSHUT_PIN; // Pin
  GPIO_InitStruct2.Mode = GPIO_MODE_INPUT; // GPIO mode output
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct2);

  delay_ms();


  VL6180X_init();
  VL6180X_configureDefault();
  presence_sensor = VL6180X_setAddress(ADDRESS_DEFAULT_VL6180X, ADR_PROX3);
  tab_proxSensorsEnable[2] = presence_sensor;// presence ou non du capteur dans le connecteur 7 pins

  /////////////// FIN CONFIG PROX3

  // configuration en entrée PROX4
  HAL_GPIO_DeInit(GPIOD,PROX4_XSHUT_PIN);
  GPIO_InitStruct2.Pin = PROX4_XSHUT_PIN; // Pin
  GPIO_InitStruct2.Mode = GPIO_MODE_INPUT; // GPIO mode output
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct2);

   delay_ms();

   VL6180X_init();
   VL6180X_configureDefault();
   presence_sensor = VL6180X_setAddress(ADDRESS_DEFAULT_VL6180X, ADR_PROX4);
   tab_proxSensorsEnable[3] = presence_sensor;// presence ou non du capteur dans le connecteur 7 pins

   /////////////// FIN CONFIG PROX4

   // configuration en entrée PROX5
   HAL_GPIO_DeInit(GPIOE,PROX5_XSHUT_PIN);
   GPIO_InitStruct2.Pin = PROX5_XSHUT_PIN; // Pin
   GPIO_InitStruct2.Mode = GPIO_MODE_INPUT; // GPIO mode output
   HAL_GPIO_Init(GPIOE, &GPIO_InitStruct2);

   delay_ms();

   VL6180X_init();
   VL6180X_configureDefault();
   presence_sensor = VL6180X_setAddress(ADDRESS_DEFAULT_VL6180X, ADR_PROX5);
   tab_proxSensorsEnable[4] = presence_sensor;// presence ou non du capteur dans le connecteur 7 pins

   /////////////// FIN CONFIG PROX5



   // Lecture de la présence des capteurs
   for(c=0; c < PROXn; c++)
   {
	   if( tab_proxSensorsEnable[c] != 0)
	   {
	     tab_proxSensorsEnable[c] = 0; // capteur non présent
	   }
	   else
	   {
         tab_proxSensorsEnable[c] = 1; // capteur présent
	   }
   }


}



/**********************************************************
 * @brief  ProxSensors_read
 * @param  proximity sensor
 * @retval None
**********************************************************/
uint16_t ProxSensors_read(uint8_t Prox)
{
  return(tab_proxSensors[Prox]);
}


/**********************************************************
 * @brief  ProxSensors_readAmbientLight
 * @param  proximity sensor
 * @retval None
**********************************************************/
uint16_t ProxSensors_readAmbientLight(uint8_t Prox)
{
  return(VL6180X_readAmbientContinuous(Prox));
}


/**********************************************************
 * @brief  ProxSensors_manage
 * @param  proximity sensor
 * @retval None
**********************************************************/
void ProxSensors_manage(void)
{
}


/**********************************************************
 * @brief  ProxSensorsVL6180_presence : renvoie si le capteur est présent
 * @param  nom du capteur
 * @retval None
**********************************************************/
uint8_t ProxSensorsVL6180_presence(uint8_t Prox)
{
  return tab_proxSensorsEnable[Prox];
}





 // End Of file
