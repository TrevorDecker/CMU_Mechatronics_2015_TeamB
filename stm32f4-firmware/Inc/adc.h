#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif


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

#define ADC_MAX_CHANNELS 19


// Structure definitions
volatile uint32_t ADCBuffer[ADC_MAX_CHANNELS];


// Methods
int adc_init(void);
int adc_deinit(void);
uint16_t adc_get_channel(uint32_t scanned_index);


#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */
