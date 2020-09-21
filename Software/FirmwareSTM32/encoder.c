/**
  ******************************************************************************
  * @file    Encoder.c
  * @author  Mace Robotics
  * @version V1.1
  * @date    21/09/2020
  * @brief
  *
  * Modification du 21/09/20 : ajouter TIM_AUTORELOAD_PRELOAD_DISABLE;
  *
  *
 *******************************************************************************/
#include <stdbool.h>
#include "encoder.h"

typedef struct
{
int32_t currentTimer;
int32_t direction;
int32_t oldTimer;
int32_t virtualTimer;
TIM_TypeDef* TIMER;
bool OverFlow;
}struct_Encoder;



static void encoder_iniTimer1(void);
static void encoder_iniTimer8(void);
static int32_t EncoderVirtual(struct_Encoder *Encoder);




struct_Encoder EncoderRight, EncoderLeft;


/**********************************************************
 * @brief  Encoder initialisation
 * @param  None
 * @retval None
**********************************************************/
void encoder_init(void)
{
GPIO_InitTypeDef gpio_initStruct;


  /* Configuration  gpio  encoder 1 */
  gpio_initStruct.Pin = ENCOD1A_PIN | ENCOD1B_PIN; // Pin
  gpio_initStruct.Mode = GPIO_MODE_AF_PP;
  gpio_initStruct.Speed = GPIO_SPEED_HIGH;
  gpio_initStruct.Pull = GPIO_PULLUP;
  gpio_initStruct.Alternate = GPIO_AF3_TIM8;
  HAL_GPIO_Init(ENCOD1A_PORT, &gpio_initStruct);

  /* Configuration  gpio  encoder 2 */
  gpio_initStruct.Pin = ENCOD2A_PIN | ENCOD2B_PIN; // Pin
  gpio_initStruct.Mode = GPIO_MODE_AF_PP;
  gpio_initStruct.Speed = GPIO_SPEED_HIGH;
  gpio_initStruct.Pull = GPIO_PULLUP;
  gpio_initStruct.Alternate = GPIO_AF1_TIM1;
  HAL_GPIO_Init(ENCOD2A_PORT, &gpio_initStruct);

  // Init timer 1
  encoder_iniTimer1();

  // Init timer 8
  encoder_iniTimer8();

  // Init virtual encoder right
  EncoderRight.TIMER = TIM1;
  EncoderRight.OverFlow = false;
  EncoderRight.direction = 0;
  EncoderRight.currentTimer = 0;
  EncoderRight.oldTimer = 0;

  // Init virtual encoder right
  EncoderLeft.TIMER = TIM8;
  EncoderLeft.OverFlow = false;
  EncoderLeft.direction = 0;
  EncoderLeft.currentTimer = 0;
  EncoderLeft.oldTimer = 0;

  // Clear the flag de l'overflow
  (EncoderRight.TIMER)->SR = (EncoderRight.TIMER)->SR & 0xFFFE;
  // Clear the flag de l'overflow
  (EncoderLeft.TIMER)->SR = (EncoderLeft.TIMER)->SR & 0xFFFE;



}




/**********************************************************
 * @brief  read encoder left
 * @param  None
 * @retval None
**********************************************************/
int32_t encodeurLeft(void)
{
int32_t counter = 0;

  EncoderLeft.currentTimer = TIM1->CNT;

  counter = EncoderVirtual(&EncoderLeft);

  return(counter);
}

/**********************************************************
 * @brief  read encoder right
 * @param  None
 * @retval None
**********************************************************/
int32_t encodeurRight(void)
{
int32_t counter = 0;

  // read the counter timer.
  EncoderRight.currentTimer = TIM8->CNT;

  counter = EncoderVirtual(&EncoderRight);

  return(counter);

}


/**********************************************************
 * @brief  encodeur Right reset
 * @param  None
 * @retval None
**********************************************************/
void encodeur_reset(void)
{
  EncoderRight.virtualTimer = 0;
  EncoderLeft.virtualTimer = 0;
  TIM8->CNT = 0;
  TIM1->CNT = 0;
}


/**********************************************************
 * @brief  virtual 32 bit encoder
 * @param  None
 * @retval None
**********************************************************/
static int32_t EncoderVirtual(struct_Encoder *Encoder)
{
int16_t Difference = 0;

  // Calcul de la différence par rapport à l'ancienne valeur.
  if(Encoder->oldTimer < Encoder->currentTimer)
  {
    Difference = Encoder->currentTimer - Encoder->oldTimer;
  }
  else
  {
    Difference = (65536 - Encoder->oldTimer) + Encoder->currentTimer;
  }

  Encoder->virtualTimer = Encoder->virtualTimer + Difference;

  Encoder->oldTimer = Encoder->virtualTimer;

  //return(-Encoder->virtualTimer);
  return(-Encoder->virtualTimer/7); // pour moteur avec encodeur de 2800

}


/**********************************************************
 * @brief  Encoder init timer 1
 * @param  None
 * @retval None
**********************************************************/
static void encoder_iniTimer1(void)
{
TIM_HandleTypeDef timer1_initStruct;
TIM_Encoder_InitTypeDef t1Encod_initStruct;

  // TIM1 Clock Enable
  __TIM1_CLK_ENABLE();

  // Timer 1 init structure
  timer1_initStruct.Instance = TIM1;
  timer1_initStruct.Init.Prescaler = 0;
  timer1_initStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
  timer1_initStruct.Init.Period = 0xFFFF;
  timer1_initStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  timer1_initStruct.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  t1Encod_initStruct.EncoderMode = TIM_ENCODERMODE_TI12;

  t1Encod_initStruct.IC1Polarity = TIM_INPUTCHANNELPOLARITY_RISING;
  t1Encod_initStruct.IC2Polarity = TIM_INPUTCHANNELPOLARITY_RISING;

  t1Encod_initStruct.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  t1Encod_initStruct.IC2Selection = TIM_ICSELECTION_DIRECTTI;

  t1Encod_initStruct.IC1Prescaler = TIM_ICPSC_DIV1;
  t1Encod_initStruct.IC2Prescaler = TIM_ICPSC_DIV1;

   t1Encod_initStruct.IC1Filter = 8;// digital filter
   t1Encod_initStruct.IC2Filter = 8;// digital filter

  // Init timer
  HAL_TIM_Encoder_Init(&timer1_initStruct,&t1Encod_initStruct);

  __HAL_TIM_SetCounter(&timer1_initStruct,0);

  HAL_TIM_Encoder_Start(&timer1_initStruct, TIM_CHANNEL_1 | TIM_CHANNEL_2);

}

/**********************************************************
 * @brief  Encoder init timer 8
 * @param  None
 * @retval None
**********************************************************/
static void encoder_iniTimer8(void)
{
TIM_HandleTypeDef timer8_initStruct;
TIM_Encoder_InitTypeDef t8Encod_initStruct;

  // TIM8 Clock Enable
  __TIM8_CLK_ENABLE();

  // Timer 8 init structure
  timer8_initStruct.Instance = TIM8;
  timer8_initStruct.Init.Prescaler = 0;
  timer8_initStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
  timer8_initStruct.Init.Period = 0xFFFF;
  timer8_initStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  timer8_initStruct.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  t8Encod_initStruct.EncoderMode = TIM_ENCODERMODE_TI12;

  t8Encod_initStruct.IC1Polarity = TIM_INPUTCHANNELPOLARITY_RISING;
  t8Encod_initStruct.IC2Polarity = TIM_INPUTCHANNELPOLARITY_RISING;

  t8Encod_initStruct.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  t8Encod_initStruct.IC2Selection = TIM_ICSELECTION_DIRECTTI;

  t8Encod_initStruct.IC1Prescaler = TIM_ICPSC_DIV1;
  t8Encod_initStruct.IC2Prescaler = TIM_ICPSC_DIV1;

  t8Encod_initStruct.IC1Filter = 8;// digital filter
  t8Encod_initStruct.IC2Filter = 8;// digital filter


  // Init timer
  HAL_TIM_Encoder_Init(&timer8_initStruct,&t8Encod_initStruct);

  __HAL_TIM_SetCounter(&timer8_initStruct,0);

  HAL_TIM_Encoder_Start(&timer8_initStruct, TIM_CHANNEL_1 | TIM_CHANNEL_2);

}


 // End Of file
