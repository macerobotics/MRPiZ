/**
  ******************************************************************************
  * @file    usart.c
  * @author  Ac6
  * @version V1.0
  * @date    12/06/2020
  * @brief   usart
  ******************************************************************************
*/
#include <leds.h>
#include <stdio.h>
#include <string.h>

#include "stm32f4xx.h"
#include "Usart.h"
//#include "ComRPI.h"

/************************************************************************
 * Private functions definitions
***********************************************************************/
static void Usart3_GPIO_Init(GPIO_TypeDef  *GPIOx_USART);
static void Uart4_GPIO_Init(GPIO_TypeDef  *GPIOx_USART);


/************************************************************************
 * Variable definitions
***********************************************************************/
UART_HandleTypeDef Uart3_Handle;
UART_HandleTypeDef Uart4_Handle;

static uint8_t counter_usart3 = 0;

/**********************************************************
 * @brief  USART3 interrupt Handler
 * @param  None
 * @retval None
**********************************************************/
char data_rx[10];
void USART3_IRQHandler(void)
{


  // if interrupt was because data is ready to be read.
  if (USART3->SR & USART_SR_RXNE)
  {
      if(counter_usart3 < 10)
      {
        data_rx[counter_usart3] = UART_READ_DATA(USART3);
        counter_usart3++;
      }
      else
      {
    	  counter_usart3 = 0;
      }

  }
}

/**********************************************************
 * @brief  UART4_IRQHandler
 * @param  None
 * @retval None
**********************************************************/
void UART4_IRQHandler(void)
{
  // if interrupt was because data is ready to be read.
  if (UART4->SR & USART_SR_RXNE)
  {

    ComRPI_manage(UART_READ_DATA(UART4));

  }


}


/**********************************************************
 * @brief  Usart init
 * @param  None
 * @retval None
**********************************************************/
void Usart3_init(uint32_t baudrate,
				uint32_t Mode,
				uint32_t Parity,
				uint32_t StopBits,
				uint32_t WordLength)
{



  // init gpio of the Usart3 port D.
  Usart3_GPIO_Init(GPIOB);

  /* Enable USART3 clock */
  __USART3_CLK_ENABLE();

  // Init USART parameter
  Uart3_Handle.Instance        = USART3;
  Uart3_Handle.Init.BaudRate   = baudrate; // init baud rate
  Uart3_Handle.Init.WordLength = WordLength;
  Uart3_Handle.Init.StopBits   = StopBits;
  Uart3_Handle.Init.Parity     = Parity;
  Uart3_Handle.Init.Mode       = Mode;
  Uart3_Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  HAL_UART_Init(&Uart3_Handle);

  // Enable reception irq
  __HAL_UART_ENABLE_IT(&Uart3_Handle, UART_IT_RXNE);

  HAL_NVIC_SetPriority(USART3_IRQn, 0, 1);

  HAL_NVIC_EnableIRQ(USART3_IRQn);


}

/**********************************************************
 * @brief  Uart init
 * @param  None
 * @retval None
**********************************************************/
void Uart4_init(uint32_t baudrate,
				uint32_t Mode,
				uint32_t Parity,
				uint32_t StopBits,
				uint32_t WordLength)
{


  // init gpio of the Uart4 port C.
  Uart4_GPIO_Init(GPIOC);


  /* Enable UART4 clock */
  __UART4_CLK_ENABLE();

  // Init USART parameter
  Uart4_Handle.Instance        = UART4;
  Uart4_Handle.Init.BaudRate   = baudrate; // init baud rate
  Uart4_Handle.Init.WordLength = WordLength;
  Uart4_Handle.Init.StopBits   = StopBits;
  Uart4_Handle.Init.Parity     = Parity;
  Uart4_Handle.Init.Mode       = Mode;
  Uart4_Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  HAL_UART_Init(&Uart4_Handle);

  // Enable reception irq
  __HAL_UART_ENABLE_IT(&Uart4_Handle, UART_IT_RXNE);

  HAL_NVIC_SetPriority(UART4_IRQn, 0, 1);

  HAL_NVIC_EnableIRQ(UART4_IRQn);


}



/**********************************************************
 * @brief  Usart3_GPIO_Init
 * @param  GPIO_TypeDef
 * @retval None
**********************************************************/
static void Usart3_GPIO_Init(GPIO_TypeDef  *GPIOx_USART)
{
GPIO_InitTypeDef  GPIO_InitStruct;


  if( GPIOx_USART == GPIOB )
  {
    // CLK enable
    __GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
  }

  if( GPIOx_USART == GPIOC )
  {
    // CLK enable
    __GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
  }

  // Configure pins
  if( GPIOx_USART == GPIOD )
  {
    // CLK enable
    __GPIOD_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
  }


  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOx_USART, &GPIO_InitStruct);

}

/**********************************************************
 * @brief  Usart4_GPIO_Init
 * @param  GPIO_TypeDef
 * @retval None
**********************************************************/
static void Uart4_GPIO_Init(GPIO_TypeDef  *GPIOx_USART)
{
GPIO_InitTypeDef  GPIO_InitStruct;

    // CLK enable
    __GPIOC_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(GPIOx_USART, &GPIO_InitStruct);

}


/**********************************************************
 * @brief  Send character from internal USART buffer
 * @param  USARTx
 * @param  caractere (exemple : Usart_Send_Character(UART4, 'D');
 * @retval None
**********************************************************/
void Usart_Send_Character(USART_TypeDef* Usart, char cara)
{
  // Wait to be ready, buffer empty
  UART_WAIT_READY(Usart);

  UART_SEND_DATA(Usart, cara);

  // Wait to be ready, buffer empty
  UART_WAIT_READY(Usart);

}


/**********************************************************
 * @brief  Send character from internal USART buffer
 * @param  USARTx
 * @param  caractere (exemple : Usart_Send_Character(UART4, 'D');
 * @retval None
**********************************************************/
void Usart3_Read_String(char * String)
{
  // copy string
  strcpy(String, data_rx);

  // Reset string
  memset(data_rx, 0, sizeof(data_rx));
  counter_usart3 = 0;

}


/**********************************************************
 * @brief  Read character from internal USART buffer
 * @param  USART, cara
 * @retval None
**********************************************************/
uint8_t Usart_Read_Character(USART_TypeDef* Usart)
{
uint8_t cara;


  cara = UART_READ_DATA(Usart);

  return cara;

  //return cara;
}


/**********************************************************
 * @brief  Send buffer character from internal USART buffer
 * @param  USART, cara
 * @retval None
**********************************************************/
void Usart_Send_Buffer(USART_TypeDef* Usart, char *buffer, uint16_t SizeBuffer)
{
  while(SizeBuffer--)
  {
	UART_WAIT_READY(Usart);

	UART_SEND_DATA(Usart, (uint16_t)(*buffer++));

	UART_WAIT_READY(Usart);
  }

}


/**********************************************************
 * @brief  Usart_Send_String
 * @param  USART number (UART1, UART2, ...) , string
 * @retval None
**********************************************************/
void Usart_Send_String(USART_TypeDef* Usart, char *String)
{

  while(*String)
  {
	  UART_WAIT_READY(Usart);

	  UART_SEND_DATA(Usart, (uint16_t)(*String++));

	  UART_WAIT_READY(Usart);
  }
}


/**********************************************************
 * @brief  Usart_Send_uint
 * @param  USART number (UART1, UART2, ...) , unsigned number
 * @retval None
**********************************************************/
void Usart_Send_uint(USART_TypeDef* Usart, uint32_t Number)
{
char string_number[12]={'c','c','c','c','c','c','c','c','c','c','c','c'};
uint32_t size = 0, Count = 0;
char cara='.';

  // convert number to string
  sprintf(string_number, "%lu", Number);

  while((cara != 'c')&&(size < 12))
  {
    cara = string_number[size];
	size++;
  }

  for(Count=0; Count < (size-2); Count++)// Size - (caracter end string)
  {
    Usart_Send_Character(Usart, string_number[Count]);
  }

}


/**********************************************************
 * @brief  Usart_Send_int
 * @param  USART number (UART1, UART2, ...) , signed number
 * @retval None
**********************************************************/
void Usart_Send_int(USART_TypeDef* Usart, int32_t Number)
{
char string_number[12]={'c','c','c','c','c','c','c','c','c','c','c','c'};
uint32_t size = 0, Count = 0;
char cara='.';

  // convert number to string
  sprintf(string_number, "%li", Number);

  while((cara != 'c')&&(size < 12))
  {
    cara = string_number[size];
	size++;
  }

  for(Count=0; Count < (size-2); Count++)// Size - (caracter end string)
  {
    Usart_Send_Character(Usart, string_number[Count]);
  }

}




/**********************************************************
 * @brief  Usart_Send_float
 * @param  USART
 * @param  float Number
 * @retval None
**********************************************************/
void Usart_Send_float(USART_TypeDef* Usart, float Number)
{
char string_number_f[12]={'c','c','c','c','c','c','c','c','c','c','c','c'};
uint32_t size = 0, Count = 0;
char cara='.';

	// convert number to string
	sprintf(string_number_f, "%f", Number);

	while((cara != 'c')&&(size < 12))
	{
		cara = string_number_f[size];
		size++;
	}

	for(Count=0; Count < (size-2); Count++)// Size - (caracter end string)
	{
		Usart_Send_Character(Usart, string_number_f[Count]);
	}
}



 // End Of file
