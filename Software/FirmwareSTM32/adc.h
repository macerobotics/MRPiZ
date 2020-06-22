/**
  ******************************************************************************
  * @file    Adc.h
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief	Analog Digital Converter
  *
 *******************************************************************************/

#ifndef _ADC_H
#define _ADC_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/
#define ADC_BUFFER_LENGHT 11 // size of the buffer (ADC -> DMA)

// initialisation of the analog digital converter.
void Adc_init(void);

uint16_t Adc_read(uint8_t Channel);

#endif
// End Of File
