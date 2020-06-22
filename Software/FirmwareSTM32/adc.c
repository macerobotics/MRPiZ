/**
  ******************************************************************************
  * @file    Adc.c
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/
 #include "stm32f4xx.h"
 #include "adc.h"

/************************************************************************
 * Private Functions definitions
***********************************************************************/
static void Configure_DMA2_Adc(void);

/************************************************************************
 * Variable definitions
***********************************************************************/
ADC_HandleTypeDef Hadc1;
DMA_HandleTypeDef  Dma2_Handle;

__IO uint16_t adc_Buffer_Data[ADC_BUFFER_LENGHT];



/**********************************************************
 * @brief  Adc_init : Analog converter initialisation
 * @param  None
 * @retval None
**********************************************************/
void Adc_init(void)
{
ADC_ChannelConfTypeDef ADC_Channel;

  // Clock enable
  __ADC1_CLK_ENABLE();

  /* Configure the ADC1   */
  Hadc1.Instance = ADC1;
  Hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
  Hadc1.Init.Resolution = ADC_RESOLUTION12b;
  Hadc1.Init.ScanConvMode = ENABLE;
  Hadc1.Init.ContinuousConvMode = ENABLE;
  Hadc1.Init.DiscontinuousConvMode = DISABLE;
  Hadc1.Init.NbrOfDiscConversion = 0;
  Hadc1.Init.DMAContinuousRequests = ENABLE;
  Hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  Hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  Hadc1.Init.NbrOfConversion = ADC_BUFFER_LENGHT;
  Hadc1.Init.EOCSelection = DISABLE;
  HAL_ADC_Init(&Hadc1);

  ADC_Channel.Channel = ADC_CHANNEL_0; // PA0
  ADC_Channel.Rank = 1;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  ADC_Channel.Channel = ADC_CHANNEL_6; // PA6
  ADC_Channel.Rank = 2;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  ADC_Channel.Channel = ADC_CHANNEL_2; //PA2
  ADC_Channel.Rank = 3;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  ADC_Channel.Channel = ADC_CHANNEL_9; // PB1
  ADC_Channel.Rank = 4;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  ADC_Channel.Channel = ADC_CHANNEL_10; // PC0
  ADC_Channel.Rank = 5;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  ADC_Channel.Channel = ADC_CHANNEL_11; // PC1
  ADC_Channel.Rank = 6;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  ADC_Channel.Channel = ADC_CHANNEL_12; // PC2
  ADC_Channel.Rank = 7;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  ADC_Channel.Channel = ADC_CHANNEL_13; // PC3
  ADC_Channel.Rank = 8;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  ADC_Channel.Channel = ADC_CHANNEL_8; // PB0
  ADC_Channel.Rank = 9;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  ADC_Channel.Channel = ADC_CHANNEL_4; // PA4
  ADC_Channel.Rank = 10;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  ADC_Channel.Channel = ADC_CHANNEL_1; // PA1
  ADC_Channel.Rank = 11;
  ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  ADC_Channel.Offset = 0;
  HAL_ADC_ConfigChannel(&Hadc1, &ADC_Channel);

  Configure_DMA2_Adc();
}


/**********************************************************
 * @brief  Adc_read : read Analog converter
 * @param  Channel number
 * @retval None
**********************************************************/
uint16_t Adc_read(uint8_t Channel)
{
uint16_t data;

  if(Channel > ADC_BUFFER_LENGHT)
  {
    assert_param(false);
  }


  data = adc_Buffer_Data[Channel];


  return( data );
}


/**********************************************************
 * @brief  Configure_DMA2_Adc : configure DMA n°2
 * @param  Channel number
 * @retval None
**********************************************************/
static void Configure_DMA2_Adc(void)
{

  // Enable DMA 2 clock.
  __DMA2_CLK_ENABLE();

  // Init DMA2
  Dma2_Handle.Instance = DMA2_Stream0;
  Dma2_Handle.Init.Channel  = DMA_CHANNEL_0;
  Dma2_Handle.Init.Direction = DMA_PERIPH_TO_MEMORY; // transfer from ADC to memory.
  Dma2_Handle.Init.PeriphInc = DMA_PINC_DISABLE;
  Dma2_Handle.Init.MemInc = DMA_MINC_ENABLE;
  Dma2_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; // Peripheral data size : Half-word (16-bit)
  Dma2_Handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;    // Memory data size : Half-word (16-bit)
  Dma2_Handle.Init.Mode = DMA_CIRCULAR;
  Dma2_Handle.Init.Priority = DMA_PRIORITY_HIGH; // Priority level
  Dma2_Handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  Dma2_Handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
  Dma2_Handle.Init.MemBurst = DMA_MBURST_SINGLE;
  Dma2_Handle.Init.PeriphBurst = DMA_PBURST_SINGLE;
  HAL_DMA_Init(&Dma2_Handle);


  __HAL_LINKDMA(&Hadc1, DMA_Handle,Dma2_Handle);

  // Enables ADC DMA request after last transfer
  HAL_ADC_Start_DMA(&Hadc1, (uint32_t*)adc_Buffer_Data, ADC_BUFFER_LENGHT);

}

 // End Of file
