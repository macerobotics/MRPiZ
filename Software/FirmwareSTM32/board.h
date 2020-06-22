/**
  ******************************************************************************
  * @file    Board.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    12/06/2020
  * @brief	 Definition of the I/O
  *
 *******************************************************************************/
#ifndef _BOARD_H
#define _BOARD_H


#include <math.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "leds.h"
#include "batteryTension.h"
#include "encoder.h"
#include "motors.h"
#include "firmwareVersion.h"
#include "ledOnOff.h"
#include "proximitySensors.h"
#include "trapezoidGenerator.h"
#include "robotState.h"
#include "scheduler.h"
#include "moveRobot.h"
#include "positionControl.h"
#include "delay.h"
#include "vl6180x.h"
#include "i2c.h"
#include "adc.h"
#include "switchs.h"
#include "chargeManagement.h"
#include "usart.h"
#include "comRPI.h"
#include "control.h"

/**
  * @brief LEDS
  */
#define LED1_PORT GPIOA // LED ON/OFF
#define LED1_PIN  GPIO_PIN_5

#define LED2_PORT GPIOE       // LOW BATTERY
#define LED2_PIN  GPIO_PIN_8



/**
  * @brief Proximity XSHUT
  */
#define PROX1_XSHUT_PORT GPIOA
#define PROX1_XSHUT_PIN  GPIO_PIN_13

#define PROX2_XSHUT_PORT GPIOA
#define PROX2_XSHUT_PIN  GPIO_PIN_14

#define PROX3_XSHUT_PORT GPIOD
#define PROX3_XSHUT_PIN  GPIO_PIN_6

#define PROX4_XSHUT_PORT GPIOD
#define PROX4_XSHUT_PIN  GPIO_PIN_7

#define PROX5_XSHUT_PORT GPIOE
#define PROX5_XSHUT_PIN  GPIO_PIN_2



/**
  * @brief I2C BUS
  */
#define I2C_SDA_PORT GPIOB
#define I2C_SDA_PIN  GPIO_PIN_7

#define I2C_SCL_PORT GPIOB
#define I2C_SCL_PIN  GPIO_PIN_6

/**
  * @brief SPI BUS
  */
#define SPI_SCK_PORT GPIOB
#define SPI_SCK_PIN  GPIO_PIN_3

#define SPI_MISO_PORT GPIOB
#define SPI_MISO_PIN  GPIO_PIN_4

#define SPI_MOSI_PORT GPIOB
#define SPI_MOSI_PIN  GPIO_PIN_5

#define SPI_CS1_PORT GPIOA
#define SPI_CS1_PIN  GPIO_PIN_15


/**
  * @brief Battery Tension
  */
#define BATT_PORT GPIOA
#define BATT_PIN  GPIO_PIN_0

/**
  * @brief H-Bridge DC Motor
  */
#define HBRIDGE_DIR1_PORT GPIOD
#define HBRIDGE_DIR1_PIN  GPIO_PIN_14

#define HBRIDGE_DIR2_PORT GPIOD
#define HBRIDGE_DIR2_PIN  GPIO_PIN_15

#define HBRIDGE_PWM1_PORT GPIOC
#define HBRIDGE_PWM1_PIN  GPIO_PIN_8

#define HBRIDGE_PWM2_PORT GPIOC
#define HBRIDGE_PWM2_PIN  GPIO_PIN_9

#define HBRIDGE_SLEEP_PORT GPIOB
#define HBRIDGE_SLEEP_PIN  GPIO_PIN_15

/**
  * @brief USB  management
  */
#define USB_CURRENT_PORT GPIOA
#define USB_CURRENT_PIN  GPIO_PIN_3

#define USB_PRESENT_PORT GPIOA
#define USB_PRESENT_PIN  GPIO_PIN_7

#define USB_VOLTAGE_PORT GPIOA
#define USB_VOLTAGE_PIN  GPIO_PIN_1


/**
  * @brief Switchs
  */
#define SWITCH1_PORT GPIOD
#define SWITCH1_PIN  GPIO_PIN_4



/**
  * @brief Encoder
  */
#define ENCOD1A_PORT GPIOC
#define ENCOD1A_PIN  GPIO_PIN_6

#define ENCOD1B_PORT GPIOC
#define ENCOD1B_PIN  GPIO_PIN_7

#define ENCOD2A_PORT GPIOE
#define ENCOD2A_PIN  GPIO_PIN_9

#define ENCOD2B_PORT GPIOE
#define ENCOD2B_PIN  GPIO_PIN_11


void Board_init(void);

#endif
// End Of File
