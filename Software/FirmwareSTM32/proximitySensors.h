/**
  ******************************************************************************
  * @file    proximitySensors.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/

#ifndef _PROXIMITY_SENSOR_H
#define _PROXIMITY_SENSOR_H

#include "Board.h"

#define PROXn 5 // Number of prox sensor

#define ADR_PROX1 0x20
#define ADR_PROX2 0x21
#define ADR_PROX3 0x22
#define ADR_PROX4 0x23
#define ADR_PROX5 0x24



typedef enum
{
PROX1 = ADR_PROX1,
PROX2 = ADR_PROX2,
PROX3 = ADR_PROX3,
PROX4 = ADR_PROX4,
PROX5 = ADR_PROX5
}PROX_TypeDef;



//void ProxSensors_init(void);


uint16_t ProxSensors_read(uint8_t Prox);

void ProxSensors_manage(void);

void ProxSensorsVL6180_init(void);

uint8_t ProxSensorsVL6180_presence(uint8_t Prox);

uint16_t ProxSensors_readAmbientLight(uint8_t Prox);

#endif
// End Of File
