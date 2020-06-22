/**
  ******************************************************************************
  * @file    comRPI.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    16/11/2015
  * @brief	 communication between Raspberry Pi and STM32
  *
 *******************************************************************************/

#ifndef _ComRPI_H
#define _ComRPI_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/

#define SIZE_COMMAND 5

/************************************************************************
 * enumeration
***********************************************************************/
typedef enum
{
COM_BAT,           // Get battery tension
COM_MF,            // Move robot forward
COM_MB,            // Move robot back
COM_TR,            // turn right
COM_TL,            // turn left
COM_STP,           // stop
COM_FV,            // read firmware version
COM_PROX,          // read proximity sensor
COM_MOTR,          // motor right
COM_MOTL,          // motor left
COM_MOTS,          // motors left & right
COM_SW,            // read switch
COM_SMR,           // speed motor right
COM_SML,           // speed motor left
COM_MFC,           //  Move robot forward with control
COM_MBC,           //  Move robot back with control
COM_TRC,           //  turn robot right with control
COM_TLC,           //  turn robot left with control
COM_TGS,           //  trapezoid generator state
COM_EDR,           //  read encoder right
COM_EDL,           //  read encoder left
COM_CRE,           //  Control robot enable
COM_CRD,           //  Control robot disable
COM_RST,           //  Reset
COM_POX,           //  Position robot axe X
COM_POY,           //  Position robot axe Y
COM_POO,           //  Position robot Orientation
COM_MRS,           //  motors right speed
COM_MLS,           //  motors left speed
COM_STA,           //  Robot state
COM_VUSB,          //  Voltage USB
COM_AL,            //  Ambiant light
COM_MDI,           //  motor disable
COM_MEN,           //  motor enable
COM_BRK,           //  brake motors
COM_NONE           // No Command
}enum_NameComdRPi;

#define NUMBER_COMMAND COM_NONE




typedef struct
{
  char Command[SIZE_COMMAND];
  char Parameter1[10];
  char Parameter2[10];
  uint8_t SizeCommand;
  uint8_t SizeParameter1;
  uint8_t SizeParameter2;
}struct_ComRPI;

typedef enum
{
WAIT_START_COM,  // Wait start command '#'
READ_COM_RPI,    // Read comman
READ_P1_RPI,     // Read parameter 1
READ_P2_RPI      // Read parameter 2
}enum_ComRPI;





/**
  * @brief ComRPI
  */
void ComRPI_init(void);

void ComRPI_ReadCommand(void);

void ComRPI_manage(char cara);




 #endif
// End Of File
