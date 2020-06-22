/**
  ******************************************************************************
  * @file    scheduler.c
  * @author  Mace Robotics (www.macerobotics.com)
  * @version V1.0
  * @date    30/12/2015
  * @brief
  *
  *
 *******************************************************************************/
#include <stdbool.h>
#include "scheduler.h"

// scheduler functions array
void (*tab_schedulerFunctions[NB_TACHES])(void);

static bool b_schedulerEnable = true;

static bool b_taskEnable = false;
static uint8_t stateScheduler = 0;





/************************************************************************
 * Private functions
***********************************************************************/
static void schedulerInitTimer(void);


/************************************************************************
 * Variable definitions
***********************************************************************/
TIM_HandleTypeDef TIMER6_InitStruct;


/**********************************************************
 * @brief  schedulerInit
 * @param  None
 * @retval None
**********************************************************/
void schedulerInit(void)
{
  // init timer
  schedulerInitTimer();

  // init functions pointer
  tab_schedulerFunctions[0] = task1_scheduler;
  tab_schedulerFunctions[1] = task2_scheduler;
  tab_schedulerFunctions[2] = task3_scheduler;
  tab_schedulerFunctions[3] = task4_scheduler;


}


/**********************************************************
 * @brief  TIM10_IRQHandler
 * @param  None
 * @retval None
**********************************************************/
void TIM6_DAC_IRQHandler(void)
{


  if (__HAL_TIM_GET_FLAG(&TIMER6_InitStruct, TIM_FLAG_UPDATE) != RESET)
  {
    if (__HAL_TIM_GET_ITSTATUS(&TIMER6_InitStruct, TIM_IT_UPDATE) != RESET)
    {
	  __HAL_TIM_CLEAR_FLAG(&TIMER6_InitStruct, TIM_FLAG_UPDATE);


      //
	  if( stateScheduler < (NB_TACHES-1) )
	  {
	    stateScheduler++;
	  }
	  else
	  {
	    stateScheduler = 0;
	  }

	  b_taskEnable = true;


	}
  }
}


/**********************************************************
 * @brief  schedulerManage
 * @param  None
 * @retval None
**********************************************************/
void schedulerManage(void)
{


  if(b_schedulerEnable == true)
  {
	  if(b_taskEnable == true)
	  {

		//
		(*tab_schedulerFunctions[stateScheduler])();

		b_taskEnable = false;
	  }
	  else
	  {

	  }
  }

}


/**********************************************************
 * @brief  task1_scheduler
 * @param  None
 * @retval None
**********************************************************/
void task1_scheduler(void)
{

  // manage position of the robot.
  positionControl();

}


/**********************************************************
 * @brief  task2_scheduler
 * @param  None
 * @retval None
**********************************************************/
uint32_t c_task2 = 0;
void task2_scheduler(void)
{
  c_task2++;

  if(c_task2  == 6)
  {

     trapezoidGenerator_management(); // trapezoid generator management
     c_task2 = 0;
  }

}


/**********************************************************
 * @brief  task3_scheduler
 * @param  None
 * @retval None
**********************************************************/
void task3_scheduler(void)
{

  if(controlState() == true)// TEST 21/11/2017
  {

	    // control position and orientation
	    controlManage( trapezoidGenerator_out(TRAPEZOID_DISTANCE_FORWARD), trapezoidGenerator_out(TRAPEZOID_ORIENTATION_LEFT) );
  }
 // else
  {

  }


}


/**********************************************************
 * @brief  task4_scheduler
 * @param  None
 * @retval None
**********************************************************/
void task4_scheduler(void)
{

}


/**********************************************************
 * @brief  schedulerInitTimer
 * @param  None
 * @retval None
**********************************************************/
static void schedulerInitTimer(void)
{
  // TIM6 Clock Enable
  __TIM6_CLK_ENABLE();

  // timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)

  // Timer 6 init structure (Timer period = 2.5ms)
  TIMER6_InitStruct.Instance = TIM6;
  TIMER6_InitStruct.Init.Prescaler = 1999; //  Timer_Frequency =  42Khz
  TIMER6_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
  TIMER6_InitStruct.Init.Period = 104; //  TIMER_Period = (42Khz)/(400Hz) - 1 = 104
  TIMER6_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

  // Init timer
  HAL_TIM_Base_Init(&TIMER6_InitStruct);

  // Start timer interrupt
  HAL_TIM_Base_Start_IT(&TIMER6_InitStruct);

  // Init timer priority
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 1);

  // Enable interrupt.
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
}


/**********************************************************
 * @brief  schedulerActivate
 * @param  None
 * @retval None
**********************************************************/
void schedulerActivate(bool Activate)
{
  b_schedulerEnable = Activate;
}


 // End Of file
