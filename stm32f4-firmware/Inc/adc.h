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
typedef struct adc_hw_assign_channel {
  GPIO_TypeDef      *gpio;
  uint32_t           pin;
  uint32_t           adc_channel;
} adc_hw_assign_channel_t;

typedef struct adc_state {
  volatile uint32_t channel_buffer[ADC_MAX_CHANNELS];
  adc_hw_assign_channel_t hw_assign[ADC_MAX_CHANNELS];
  uint32_t active_channel_count;
} adc_state_t;


// Methods
int adc_init(adc_state_t *state,
             adc_hw_assign_channel_t *hw_assign,
             uint32_t active_channel_count);
int adc_deinit(adc_state_t *state);
uint16_t adc_get_channel(adc_state_t *state, uint32_t scanned_index);


#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */
