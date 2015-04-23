/**
  ******************************************************************************
  * @file    Src/main.c 
  * @author  CMU Mechatronics 2015 Team B
  * @brief   Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "vnh5019.h"

#define VERSION_STRING "0.1"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef AdcHandle;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
       - Low Level Initialization
     */
  HAL_Init();
  // HAL_Delay(2000);

  /* Configure the System clock to 180 MHz */
  SystemClock_Config();

  // init all the timer and gpio clocks we're using
  __TIM3_CLK_ENABLE();
  __TIM9_CLK_ENABLE();
  __TIM10_CLK_ENABLE();
  // __TIM11_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();

  vnh5019_hw_assign_t motor_hw_assign;
  vnh5019_state_t motor_pivot_l_state;
  vnh5019_state_t motor_pivot_r_state;
  vnh5019_state_t motor_3_state;
  vnh5019_state_t motor_4_state;

  // setup left pivot motor controller
  motor_hw_assign.ina_gpio = GPIOF;
  motor_hw_assign.ina_pin = GPIO_PIN_8;
  motor_hw_assign.inb_gpio = GPIOF;
  motor_hw_assign.inb_pin = GPIO_PIN_9;
  motor_hw_assign.pwm_gpio = GPIOE;
  motor_hw_assign.pwm_pin = GPIO_PIN_5;
  motor_hw_assign.pwm_af = GPIO_AF3_TIM9;
  motor_hw_assign.cs_gpio = 0;
  motor_hw_assign.cs_pin = 0;
  motor_hw_assign.cs_af = 0;
  motor_hw_assign.timer_instance = TIM9;
  motor_hw_assign.timer_channel = TIM_CHANNEL_1;
  if(vnh5019_init(&motor_pivot_l_state, &motor_hw_assign) != 0) {
    Error_Handler();
  }

  // setup right pivot motor controller
  motor_hw_assign.ina_gpio = GPIOE;
  motor_hw_assign.ina_pin = GPIO_PIN_3;
  motor_hw_assign.inb_gpio = GPIOE;
  motor_hw_assign.inb_pin = GPIO_PIN_4;
  motor_hw_assign.pwm_gpio = GPIOE;
  motor_hw_assign.pwm_pin = GPIO_PIN_6;
  motor_hw_assign.pwm_af = GPIO_AF3_TIM9;
  motor_hw_assign.cs_gpio = 0;
  motor_hw_assign.cs_pin = 0;
  motor_hw_assign.cs_af = 0;
  motor_hw_assign.timer_instance = TIM9;
  motor_hw_assign.timer_channel = TIM_CHANNEL_2;
  if(vnh5019_init(&motor_pivot_r_state, &motor_hw_assign) != 0) {
    Error_Handler();
  }

  // setup 3rd motor controller
  motor_hw_assign.ina_gpio = GPIOG;
  motor_hw_assign.ina_pin = GPIO_PIN_2;
  motor_hw_assign.inb_gpio = GPIOG;
  motor_hw_assign.inb_pin = GPIO_PIN_3;
  motor_hw_assign.pwm_gpio = GPIOF;
  motor_hw_assign.pwm_pin = GPIO_PIN_6;
  motor_hw_assign.pwm_af = GPIO_AF3_TIM10;
  motor_hw_assign.cs_gpio = 0;
  motor_hw_assign.cs_pin = 0;
  motor_hw_assign.cs_af = 0;
  motor_hw_assign.timer_instance = TIM10;
  motor_hw_assign.timer_channel = TIM_CHANNEL_1;
  if(vnh5019_init(&motor_3_state, &motor_hw_assign) != 0) {
    Error_Handler();
  }

  // setup 4th motor controller
  motor_hw_assign.ina_gpio = GPIOD;
  motor_hw_assign.ina_pin = GPIO_PIN_4;
  motor_hw_assign.inb_gpio = GPIOD;
  motor_hw_assign.inb_pin = GPIO_PIN_5;
  motor_hw_assign.pwm_gpio = GPIOC;
  motor_hw_assign.pwm_pin = GPIO_PIN_8;
  motor_hw_assign.pwm_af = GPIO_AF2_TIM3;
  motor_hw_assign.cs_gpio = 0;
  motor_hw_assign.cs_pin = 0;
  motor_hw_assign.cs_af = 0;
  motor_hw_assign.timer_instance = TIM3;
  motor_hw_assign.timer_channel = TIM_CHANNEL_3;
  if(vnh5019_init(&motor_4_state, &motor_hw_assign) != 0) {
    Error_Handler();
  }

  GPIO_InitTypeDef gpio_init;

  // set up PA0 for button
  gpio_init.Pin = GPIO_PIN_0;
  gpio_init.Mode = GPIO_MODE_INPUT;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOA, &gpio_init);

  // pin 13 output setup
  gpio_init.Pin = GPIO_PIN_13;
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOG, &gpio_init);

  //////////////////////////////////////////////////////////////////////////////

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

  volatile uint32_t ADCBuffer[6]= {0xAAAA,
                                   0xAAAA,
                                   0xAAAA,
                                   0xAAAA,
                                   0xAAAA,
                                   0xAAAA};

  /*##-1- Configure the ADC peripheral #######################################*/
  AdcHandle.Instance = ADCx;
  
  AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
  AdcHandle.Init.Resolution = ADC_RESOLUTION12b;
  AdcHandle.Init.ScanConvMode = DISABLE;
  AdcHandle.Init.ContinuousConvMode = ENABLE;
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  AdcHandle.Init.NbrOfDiscConversion = 0;
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.NbrOfConversion = 1;
  AdcHandle.Init.DMAContinuousRequests = ENABLE;
  AdcHandle.Init.EOCSelection = DISABLE;
      
  if(HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /*##-2- Configure ADC regular channel ######################################*/  
  ADC_ChannelConfTypeDef sConfig;

  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  sConfig.Offset = 0;
  
  if(HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    /* Channel Configuration Error */
    Error_Handler(); 
  }

  // sConfig.Channel = ADC_CHANNEL_15;
  // sConfig.Rank = 2;
  // sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  // sConfig.Offset = 0;
  
  // if(HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  // {
  //   /* Channel Configuration Error */
  //   Error_Handler(); 
  // }

  /*##-3- Start the conversion process and enable interrupt ##################*/  
  if(HAL_ADC_Start_DMA(&AdcHandle, (uint32_t *)&ADCBuffer, 1) != HAL_OK)
  {
    /* Start Conversation Error */
    Error_Handler(); 
  }

  //////////////////////////////////////////////////////////////////////////////


  // setup lcd log
  LCD_LOG_Init();
  char header_buffer[64];
  sprintf(&header_buffer, "Monkey Bot %s", VERSION_STRING);
  LCD_LOG_SetHeader(&header_buffer);

  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);

  // state variables
  int motor_button_state = 0; // 1 = pressed
  int motor_button_state_last = 0;
  int motor_direction = 1; // 0 = reverse, 1 = off, 2 = forward

  /* Infinite loop */
  while (1)
  {
    // update status
    LCD_LOG_ClearTextZone();
    LCD_UsrLog("Hello world!\n");
    if(motor_direction == 0) {
      LCD_UsrLog("Motor state: reverse\n");
    } else if (motor_direction == 1) {
      LCD_UsrLog("Motor state: off\n");
    } else {
      LCD_UsrLog("Motor state: forward\n");
    }


    char adc_readout_buffer[64];
    sprintf(&adc_readout_buffer, "ADC14: 0x%x\n", ADCBuffer[0]);
    LCD_UsrLog(&adc_readout_buffer);
    sprintf(&adc_readout_buffer, "ADC15: 0x%x\n", ADCBuffer[1]);
    LCD_UsrLog(&adc_readout_buffer);


    motor_button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    if(motor_button_state == 1 && motor_button_state_last == 0) {
      motor_direction = (motor_direction + 1) % 3; // increment with wrap
    }
    motor_button_state_last = motor_button_state;

    // set motor output
    if(motor_direction == 0) {
      vnh5019_set(&motor_pivot_l_state, 10000, FORWARD);
      vnh5019_set(&motor_pivot_r_state, 10000, FORWARD);
      vnh5019_set(&motor_3_state, 10000, FORWARD);
      vnh5019_set(&motor_4_state, 10000, FORWARD);
    } else if (motor_direction == 1) {
      vnh5019_set(&motor_pivot_l_state, 0, FORWARD);
      vnh5019_set(&motor_pivot_r_state, 0, FORWARD);
      vnh5019_set(&motor_3_state, 0, FORWARD);
      vnh5019_set(&motor_4_state, 0, FORWARD);
    } else {
      vnh5019_set(&motor_pivot_l_state, 10000, REVERSE);
      vnh5019_set(&motor_pivot_r_state, 10000, REVERSE);
      vnh5019_set(&motor_3_state, 10000, REVERSE);
      vnh5019_set(&motor_4_state, 10000, REVERSE);
    }

    HAL_Delay(50);
  }
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}


/**
  * @brief ADC MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  // GPIO_InitTypeDef          GPIO_InitStruct;
  static DMA_HandleTypeDef  hdma_adc;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO clock */
  // ADCx_CHANNEL_GPIO_CLK_ENABLE();
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
  __HAL_LINKDMA(hadc, DMA_Handle, hdma_adc);

  /*##-4- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(ADCx_DMA_IRQn, 0, 0);   
  HAL_NVIC_EnableIRQ(ADCx_DMA_IRQn);
}


/**
  * @brief ADC MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO to their default state
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  static DMA_HandleTypeDef  hdma_adc;
  
  /*##-1- Reset peripherals ##################################################*/
  __ADC_FORCE_RESET();
  __ADC_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks ################################*/
  /* De-initialize the ADC3 Channel8 GPIO pin */
  // HAL_GPIO_DeInit(ADCx_CHANNEL_GPIO_PORT, ADCx_CHANNEL_PIN);
  
  /*##-3- Disable the DMA Streams ############################################*/
  /* De-Initialize the DMA Stream associate to transmission process */
  HAL_DMA_DeInit(&hdma_adc); 
    
  /*##-4- Disable the NVIC for DMA ###########################################*/
  HAL_NVIC_DisableIRQ(ADCx_DMA_IRQn);
}


/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  AdcHandle : AdcHandle handle
  * @note   This example shows a simple way to report end of conversion, and 
  *         you can add your own implementation.    
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
  /* Turn LED1 on: Transfer process is correct */
  // HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  // turn the on board LED on to indicate error
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
  while(1)
  {
  }
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
