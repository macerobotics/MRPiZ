/**
  ******************************************************************************
  * @file    SCHEDULER.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    29/12/2015
  * @brief	SCHEDULER
  *
 *******************************************************************************/

#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <stdbool.h>
#include "board.h"

typedef enum{
TACHE_1 = 0,
TACHE_2,
TACHE_3,
TACHE_4,
NB_TACHES
}enum_scheduler;





void schedulerInit(void);
void TIM6_DAC_IRQHandler(void);

void schedulerManage(void);

void schedulerActivate(bool Activate);

void task1_scheduler(void);
void task2_scheduler(void);
void task3_scheduler(void);
void task4_scheduler(void);

 #endif
// End Of File
