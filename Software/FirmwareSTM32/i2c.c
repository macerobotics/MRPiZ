/**
  ******************************************************************************
  * @file    I2C.c
  * @author  Mace Robotics
  * @version V1.1
  * @date    27/04/2016
  * @brief
  *
 *******************************************************************************/

#include "i2c.h"
#include "leds.h"



/************************************************************************
 * Private functions definitions
***********************************************************************/
static void MR_I2C_initGpio(enum_GpioI2C GpioI2C);


I2C_HandleTypeDef Handle_I2C;

/**********************************************************
 * @brief  Initializes I2C peripheral
 * @param  None
 * @retval None
**********************************************************/
void MR_I2C_init(I2C_TypeDef* I2Cx, enum_GpioI2C GpioI2C, uint32_t clockSpeed)
{

  Handle_I2C.Instance = I2Cx;
  Handle_I2C.Init.ClockSpeed  = clockSpeed;
  Handle_I2C.Init.DutyCycle   = I2C_DUTYCYCLE_2;
  Handle_I2C.Init.OwnAddress1 = 0x2d;
  Handle_I2C.Init.OwnAddress2 = 0xFE;
  Handle_I2C.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  Handle_I2C.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  Handle_I2C.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
  Handle_I2C.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;

  if (I2Cx == I2C1)
  {
	// Clock enable
	  __I2C1_CLK_ENABLE();
  }

  if (I2Cx == I2C2)
  {
	// Clock enable
	  __I2C2_CLK_ENABLE();
  }

  if (I2Cx == I2C3)
  {
	// Clock enable
	  __I2C3_CLK_ENABLE();
  }

  MR_I2C_initGpio(GpioI2C);

  HAL_I2C_Init(&Handle_I2C);

}


/**********************************************************
 * @brief  Write I2C peripheral
 * @param  target_address
 * @param  register_address
 * @param  data
**********************************************************/
uint8_t MR_I2C_Write( uint16_t target_address, uint8_t reg, uint8_t data)
{
uint8_t data_array[2] = {reg, data};
uint8_t result;

  result = HAL_I2C_Master_Transmit(&Handle_I2C,((target_address<<1)), (uint8_t*)data_array, sizeof(data_array), (uint32_t)1000);

  return(result);
}

/**********************************************************
 * @brief  Write I2C peripheral
 * @param  target_address
 * @param  register_address
 * @param  data
**********************************************************/
uint8_t MR_I2C_Write_VL6180( uint16_t target_address, uint16_t reg, uint8_t data)
{
uint8_t data_array[3] = {(reg >> 8) & 0xff, reg & 0xff, data};
uint8_t result;

  result = HAL_I2C_Master_Transmit(&Handle_I2C,((target_address<<1)), (uint8_t*)data_array, sizeof(data_array), (uint32_t)1000);

  return(result);

}

/**********************************************************
 * @brief  MR_I2C_Write16Bit
 * @param  target_address
 * @param  register_address
 * @param  data
**********************************************************/
uint8_t MR_I2C_Write16Bit( uint16_t target_address, uint8_t reg, uint16_t data)
{
uint8_t data_array[3] = {reg, (data >> 8) & 0xFF, data & 0xFF};
uint8_t result;

  result = HAL_I2C_Master_Transmit(&Handle_I2C,((target_address<<1)), (uint8_t*)data_array, sizeof(data_array), (uint32_t)1000);

  return(result);
}

/**********************************************************
 * @brief  MR_I2C_Write16Bit
 * @param  target_address
 * @param  register_address
 * @param  data
**********************************************************/
uint8_t MR_I2C_Write16Bit_VL6180( uint16_t target_address, uint16_t reg, uint16_t data)
{
uint8_t data_array[4] = {(reg >> 8) & 0xff, reg & 0xff, (data >> 8) & 0xff, data & 0xff };
uint8_t result;

  result = HAL_I2C_Master_Transmit(&Handle_I2C,((target_address<<1)), (uint8_t*)data_array, sizeof(data_array), (uint32_t)1000);

  return(result);
}


/**********************************************************
 * @brief  MR_I2C_Write32Bit
 * @param  target_address
 * @param  register_address
 * @param  data
**********************************************************/
uint8_t MR_I2C_Write32Bit( uint16_t target_address, uint8_t reg, uint32_t data)
{
uint8_t data_array[5] = {reg, (data >> 24) & 0xFF, (data >> 16) & 0xFF, (data >> 8) & 0xFF, data & 0xFF};
uint8_t result;

  result = HAL_I2C_Master_Transmit(&Handle_I2C,((target_address<<1)), (uint8_t*)data_array, sizeof(data_array), (uint32_t)1000);

  return(result);
}



/**********************************************************
 * @brief  MR_I2C_Read : read I2C register
 * @param  target_address
 * @param  register_address
 * @param  pointer where data will be stored
**********************************************************/
uint8_t MR_I2C_Read( uint16_t target_address, uint8_t register_address)
{
uint8_t data[5];


  HAL_I2C_Master_Transmit(&Handle_I2C, ((target_address<<1)), &register_address, 1, 1000);

  HAL_I2C_Master_Receive(&Handle_I2C, ((target_address<<1)), data, 1, 1000);


   return data[0];


}

/**********************************************************
 * @brief  MR_I2C_Read : read I2C register
 * @param  target_address
 * @param  register_address
 * @param  pointer where data will be stored
**********************************************************/
uint8_t MR_I2C_Read_VL6180( uint16_t target_address, uint16_t register_address)
{
uint8_t data[5];
uint8_t dataReg[2] = {(register_address >> 8) & 0xff, register_address & 0xff};


  HAL_I2C_Master_Transmit(&Handle_I2C, ((target_address<<1)), (uint8_t*)dataReg, sizeof(dataReg), 1000);

  HAL_I2C_Master_Receive(&Handle_I2C, ((target_address<<1)), data, 1, 1000);


   return data[0];


}



/**********************************************************
 * @brief  MR_I2C_Read16Bit : read I2C register
 * @param  target_address
 * @param  register_address
 * @param  pointer where data will be stored
**********************************************************/
uint16_t MR_I2C_Read16Bit( uint16_t target_address, uint8_t register_address)
{
uint8_t data[5];
uint16_t data_read=0;

  HAL_I2C_Master_Transmit(&Handle_I2C, ((target_address<<1)), &register_address, 1, 1000);

  HAL_I2C_Master_Receive(&Handle_I2C, ((target_address<<1)), data, 2, 1000);

  data_read = (uint16_t)(data[0] << 8);
  data_read |= data[1];

  return data_read;
}

/**********************************************************
 * @brief  MR_I2C_Read32Bit : read I2C register
 * @param  target_address
 * @param  register_address
 * @param  pointer where data will be stored
**********************************************************/
uint32_t MR_I2C_Read32Bit( uint16_t target_address, uint8_t register_address)
{
uint8_t data[5];
uint32_t data_read=0;

  HAL_I2C_Master_Transmit(&Handle_I2C, ((target_address<<1)), &register_address, 1, 1000);

  HAL_I2C_Master_Receive(&Handle_I2C, ((target_address<<1)), data, 4, 1000);

  data_read = (uint32_t)(data[0] << 24);
  data_read |= (uint32_t)(data[1] << 16);
  data_read |= (uint32_t)(data[2] << 8);
  data_read |= data[3];

  return data_read;

}




/**********************************************************
 * @brief  Initializes I2C peripheral
 * @param  None
 * @retval None
**********************************************************/
static void MR_I2C_initGpio(enum_GpioI2C GpioI2C)
{
GPIO_InitTypeDef  GPIO_InitStruct_Pin1;
GPIO_InitTypeDef  GPIO_InitStruct_Pin2;
GPIO_TypeDef *GPIO_Type_Pin1, *GPIO_Type_Pin2;


  // init pin
  switch(GpioI2C)
  {
    case I2C1_PB6_PB7 :
      // CLK enable
      __GPIOB_CLK_ENABLE();

      GPIO_InitStruct_Pin1.Pin = GPIO_PIN_6;
      GPIO_InitStruct_Pin2.Pin = GPIO_PIN_7;


      GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C1;
      GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C1;

      GPIO_Type_Pin1 = GPIOB;
      GPIO_Type_Pin2 = GPIOB;

    break;

    case I2C1_PB8_PB9 :
        // CLK enable
        __GPIOB_CLK_ENABLE();

        GPIO_InitStruct_Pin1.Pin = GPIO_PIN_8;
        GPIO_InitStruct_Pin2.Pin = GPIO_PIN_9;

        GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C1;
        GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C1;

        GPIO_Type_Pin1 = GPIOB;
        GPIO_Type_Pin2 = GPIOB;

    break;

    case I2C1_PB6_PB9 :
      // CLK enable
      __GPIOB_CLK_ENABLE();

      GPIO_InitStruct_Pin1.Pin = GPIO_PIN_6;
      GPIO_InitStruct_Pin2.Pin = GPIO_PIN_9;

      GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C1;
      GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C1;

      GPIO_Type_Pin1 = GPIOB;
      GPIO_Type_Pin2 = GPIOB;

    break;

    case I2C2_PB10_PB11 :
      // CLK enable
      __GPIOB_CLK_ENABLE();

      GPIO_InitStruct_Pin1.Pin = GPIO_PIN_10;
      GPIO_InitStruct_Pin2.Pin = GPIO_PIN_11;

      GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C2;
      GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C2;

      GPIO_Type_Pin1 = GPIOB;
      GPIO_Type_Pin2 = GPIOB;

    break;

    case I2C2_PF0_PF1 :
      // CLK enable
      __GPIOF_CLK_ENABLE();

      GPIO_InitStruct_Pin1.Pin = GPIO_PIN_0;
      GPIO_InitStruct_Pin2.Pin = GPIO_PIN_1;

      GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C2;
      GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C2;

      GPIO_Type_Pin1 = GPIOF;
      GPIO_Type_Pin2 = GPIOF;
    break;

    case I2C3_PC9_PA8 :
      // CLK enable
      __GPIOC_CLK_ENABLE();

      GPIO_InitStruct_Pin1.Pin = GPIO_PIN_9;
      GPIO_InitStruct_Pin2.Pin = GPIO_PIN_8;

      GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C3;
      GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C3;

      GPIO_Type_Pin1 = GPIOC;
      GPIO_Type_Pin2 = GPIOA;

    break;

    default:
        // CLK enable
        __GPIOB_CLK_ENABLE();

        GPIO_InitStruct_Pin1.Pin = GPIO_PIN_6;
        GPIO_InitStruct_Pin2.Pin = GPIO_PIN_7;


        GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C1;
        GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C1;

        GPIO_Type_Pin1 = GPIOB;
        GPIO_Type_Pin2 = GPIOB;
    break;

  }

  // init mode
  GPIO_InitStruct_Pin1.Mode = GPIO_MODE_AF_OD; // Open Drain Mode
  GPIO_InitStruct_Pin2.Mode = GPIO_MODE_AF_OD;// Open drain-mode

  // init speed
  GPIO_InitStruct_Pin1.Speed = GPIO_SPEED_LOW;
  GPIO_InitStruct_Pin2.Speed = GPIO_SPEED_LOW;

  // Init hal gpio
  HAL_GPIO_Init(GPIO_Type_Pin1, &GPIO_InitStruct_Pin1);
  HAL_GPIO_Init(GPIO_Type_Pin2, &GPIO_InitStruct_Pin2);

}



 // End Of file
