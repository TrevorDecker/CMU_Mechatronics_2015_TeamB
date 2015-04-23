/**
  ******************************************************************************
  * @file    Inc/main.h 
  * @author  CMU Mechatronics 2015 Team B
  * @brief   Header for main.c module
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "lcd_log.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

extern ADC_HandleTypeDef AdcHandle;

/* Definition for ADCx clock resources */
#define ADCx                            ADC2
#define ADCx_CLK_ENABLE()               __ADC2_CLK_ENABLE()
#define DMAx_CLK_ENABLE()               __DMA2_CLK_ENABLE()

/* Definition for ADCx's DMA */
/* See reference manual table 42/43 for DMA event mapping. */
#define ADCx_DMA_CHANNEL                DMA_CHANNEL_1
#define ADCx_DMA_STREAM                 DMA2_Stream2

/* Definition for ADCx's NVIC */
#define ADCx_DMA_IRQn                   DMA2_Stream2_IRQn
#define ADCx_DMA_IRQHandler             DMA2_Stream2_IRQHandler

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */
