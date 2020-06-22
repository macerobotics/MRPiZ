/**
  ******************************************************************************
  * @file    firmwareVersion.c
  * @author  Mace Robotics (www.macerobotics.com)
  * @version V1.0
  * @date    15/06/2020
  * @brief
  *
  *
  * version 1.1: ajouter brake motors (07/11/18)
  *
 *******************************************************************************/

#include "firmwareVersion.h"

const float firmware_version = 1.2;

/**********************************************************
 * @brief  FirmwareVersion_init
 * @param  None
 * @retval None
**********************************************************/
float FirmwareVersion_read(void)
{
  return firmware_version;
}

 // End Of file
