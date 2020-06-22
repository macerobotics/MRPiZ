/**
  ******************************************************************************
  * @file    Usart.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    9/11/2015
  * @brief	Usart
  *
 *******************************************************************************/

#ifndef _USART_H
#define _USART_H

#include "Board.h"


/************************************************************************
 * Defines
***********************************************************************/


#define UART_READ_DATA(USARTx)	        ((USARTx)->DR) // Read data
#define UART_SEND_DATA(USARTx, data)	((USARTx)->DR = (data)) // Write data in the data register.
#define UART_WAIT_READY(USARTx)		while (!((USARTx)->SR & USART_FLAG_TXE)) // Wait for TX empty ready



/************************************************************************
 * Variable definitions
***********************************************************************/
//uint8_t USART3_Buffer[USART_BUFFER_SIZE];



void Usart3_init(uint32_t baudrate,
				uint32_t Mode,
				uint32_t Parity,
				uint32_t StopBits,
				uint32_t WordLength);



void Uart4_init(uint32_t baudrate,
				uint32_t Mode,
				uint32_t Parity,
				uint32_t StopBits,
				uint32_t WordLength);



void Usart_Send_Character(USART_TypeDef* Usart, char c);
void Usart_Send_Buffer(USART_TypeDef* Usart, char *buffer, uint16_t SizeBuffer);
void Usart_Send_String(USART_TypeDef* Usart, char *String);
uint8_t Usart_Read_Character(USART_TypeDef* Usart);

void Usart3_Read_String(char * String);


void Usart_Send_uint(USART_TypeDef* Usart, uint32_t Number);
void Usart_Send_int(USART_TypeDef* Usart, int32_t Number);
void Usart_Send_float(USART_TypeDef* Usart, float Number);


 #endif
// End Of File
