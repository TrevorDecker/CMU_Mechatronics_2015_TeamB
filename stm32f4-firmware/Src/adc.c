/*
 * Driver for the STM32 ADCs. Uses a DMA and the ADC scan function to always
 * always scan the selected ADC channels in the background and plop the results
 * into a defined area of memory.
 */ 

#include "adc.h"


int adc_init() {
  // clear memory
  for(int i = 0; i < ADC_MAX_CHANNELS; i++) {
    ADCBuffer[i] = 0xAAAA;
  }

  GPIO_InitTypeDef gpio_init;

  // set up PC4 as ADC14 in
  gpio_init.Pin = GPIO_PIN_4;
  gpio_init.Mode = GPIO_MODE_ANALOG;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOC, &gpio_init);

  // set up PC5 as ADC15 in
  gpio_init.Pin = GPIO_PIN_5;
  gpio_init.Mode = GPIO_MODE_ANALOG;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOC, &gpio_init);

  /*##-1- Configure the ADC peripheral #######################################*/
  AdcHandle.Instance = ADCx;
  
  AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
  AdcHandle.Init.Resolution = ADC_RESOLUTION12b;
  AdcHandle.Init.ScanConvMode = ENABLE;
  AdcHandle.Init.ContinuousConvMode = ENABLE;
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  AdcHandle.Init.NbrOfDiscConversion = 0;
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.NbrOfConversion = 2;
  AdcHandle.Init.DMAContinuousRequests = ENABLE;
  AdcHandle.Init.EOCSelection = DISABLE;

  /* ADC3 Periph clock enable */
  ADCx_CLK_ENABLE();
  /* Enable DMA2 clock */
  DMAx_CLK_ENABLE(); 
  
  /*##-2- Configure peripheral GPIO ##########################################*/ 
  /* ADC3 Channel8 GPIO pin configuration */
  // GPIO_InitStruct.Pin = ADCx_CHANNEL_PIN;
  // GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  // GPIO_InitStruct.Pull = GPIO_NOPULL;
  // HAL_GPIO_Init(ADCx_CHANNEL_GPIO_PORT, &GPIO_InitStruct);
  
  /*##-3- Configure the DMA streams ##########################################*/
  /* Set the parameters to be configured */
  static DMA_HandleTypeDef  hdma_adc;
  hdma_adc.Instance = ADCx_DMA_STREAM;
  
  hdma_adc.Init.Channel  = ADCx_DMA_CHANNEL;
  hdma_adc.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_adc.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_adc.Init.MemInc = DMA_MINC_ENABLE;
  hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_adc.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_adc.Init.Mode = DMA_CIRCULAR;
  hdma_adc.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_adc.Init.FIFOMode = DMA_FIFOMODE_DISABLE;         
  hdma_adc.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
  hdma_adc.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_adc.Init.PeriphBurst = DMA_PBURST_SINGLE; 

  HAL_DMA_Init(&hdma_adc);
    
  /* Associate the initialized DMA handle to the the ADC handle */
  AdcHandle.DMA_Handle = &hdma_adc;
      
  if(HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    /* Initialization Error */
    return -1;
  }
  
  /*##-2- Configure ADC regular channel ######################################*/  
  ADC_ChannelConfTypeDef sConfig;

  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  sConfig.Offset = 0;
  
  if(HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    /* Channel Configuration Error */
    return -1;
  }

  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = 2;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  sConfig.Offset = 0;
  
  if(HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    /* Channel Configuration Error */
    return -1;
  }

  /*##-3- Start the conversion process and enable interrupt ##################*/  
  if(HAL_ADC_Start_DMA(&AdcHandle, (uint32_t *)&ADCBuffer, 2) != HAL_OK)
  {
    /* Start Conversation Error */
    return -1;
  }

  return 0;
}


int adc_deinit() {
  return 0;
}


uint16_t adc_get_channel(uint32_t scanned_index) {
  return ADCBuffer[scanned_index];
}


/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
*/
void ADCx_DMA_IRQHandler(void)
{
  HAL_DMA_IRQHandler(AdcHandle.DMA_Handle);
}
