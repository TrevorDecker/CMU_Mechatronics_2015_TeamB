/**
  ******************************************************************************
  * @file    Src/main.c 
  * @author  CMU Mechatronics 2015 Team B
  * @brief   Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define VERSION_STRING "0.1"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

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

  /* Configure the System clock to 180 MHz */
  SystemClock_Config();

  // setup to generate a fixed PWM signal
  TIM_HandleTypeDef TimHandle;
  /*##-1- Configure the TIM peripheral #######################################*/ 
  /* Initialize TIMx peripheral as follow:
       + Prescaler = (SystemCoreClock/2)/2000
       + Period = 65535
       + ClockDivision = 0
       + Counter direction = Up
  */
  __TIM3_CLK_ENABLE();
  TimHandle.Instance = TIM3;
  TimHandle.Init.Period        = 65535;
  TimHandle.Init.Prescaler     = 2;
  TimHandle.Init.ClockDivision = 0;
  TimHandle.Init.CounterMode   = TIM_COUNTERMODE_UP;
  if(HAL_TIM_OC_Init(&TimHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  /*##-2- Configure the Output Compare channels #########################################*/ 
  /* Common configuration for all channels */
  TIM_OC_InitTypeDef sConfig;
  sConfig.OCMode     = TIM_OCMODE_PWM1;
  sConfig.OCPolarity = TIM_OCPOLARITY_LOW;
  /* Set the pulse (delay1)  value for channel 1 */
  sConfig.Pulse = 20000;  
  if(HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }
  /*##-4- Start signals generation ###########################################*/ 
  /* Start channel 1 in Output compare mode */
  if(HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }

  // put Timer 3 Channel 1 on PB4
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef gpiob_init;
  gpiob_init.Pin = GPIO_PIN_4;
  gpiob_init.Mode = GPIO_MODE_AF_PP;
  gpiob_init.Pull = GPIO_NOPULL;
  gpiob_init.Speed = GPIO_SPEED_FAST;
  gpiob_init.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init(GPIOB, &gpiob_init);

  // pin 13 output setup
  __HAL_RCC_GPIOG_CLK_ENABLE();
  GPIO_InitTypeDef gpiog_init;
  gpiog_init.Pin = GPIO_PIN_13;
  gpiog_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpiog_init.Pull = GPIO_NOPULL;
  gpiog_init.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOG, &gpiog_init);

  // setup lcd log
  LCD_LOG_Init();
  char header_buffer[64];
  sprintf(&header_buffer, "Monkey Bot %s", VERSION_STRING);
  LCD_LOG_SetHeader(&header_buffer);

  uint32_t blink_count = 0;

  /* Infinite loop */
  while (1)
  {
    // update status
    LCD_LOG_ClearTextZone();
    LCD_UsrLog("Hello world!\n");
    LCD_UsrLog("Blink count: %d\n", blink_count);
    LCD_UsrLog("TIM5->CNT: %d\n", TIM5->CNT);
    LCD_UsrLog("TIM5->CCR3: %d\n", TIM5->CCR1);

    // toggle pin 13
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_Delay(1000);

    blink_count++;
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
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
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
