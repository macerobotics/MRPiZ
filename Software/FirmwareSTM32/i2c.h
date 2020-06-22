/**
  ******************************************************************************
  * @file    I2C.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief	I2C
  *
 *******************************************************************************/

#ifndef _I2C_H
#define _I2C_H

#include "board.h"

/************************************************************************
 * Defines
***********************************************************************/
/* Clock values */
#define I2C_CLOCK_100K         100000
#define I2C_CLOCK_400K         400000



typedef enum
{
I2C1_PB6_PB7,
I2C1_PB8_PB9,
I2C1_PB6_PB9,
I2C2_PB10_PB11,
I2C2_PF0_PF1,
I2C3_PC9_PA8
}enum_GpioI2C;


/**
  * @brief I2C
  */
void MR_I2C_init(I2C_TypeDef* I2Cx, enum_GpioI2C GpioI2C, uint32_t clockSpeed);
uint8_t MR_I2C_Write(uint16_t target_address, uint8_t reg, uint8_t data);
uint8_t MR_I2C_Read(uint16_t target_address, uint8_t register_address);
uint16_t MR_I2C_Read16Bit( uint16_t target_address, uint8_t register_address);
uint32_t MR_I2C_Read32Bit( uint16_t target_address, uint8_t register_address);

uint8_t MR_I2C_Write16Bit( uint16_t target_address, uint8_t reg, uint16_t data);
uint8_t MR_I2C_Write32Bit( uint16_t target_address, uint8_t reg, uint32_t data);

uint8_t MR_I2C_Write_VL6180( uint16_t target_address, uint16_t reg, uint8_t data);
uint8_t MR_I2C_Write16Bit_VL6180( uint16_t target_address, uint16_t reg, uint16_t data);

uint8_t MR_I2C_Read_VL6180( uint16_t target_address, uint16_t register_address);

 #endif
// End Of File
