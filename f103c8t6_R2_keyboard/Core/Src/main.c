/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can_bsp.h"
#include "intereaction.h"
#include "utils.h"
#include "ws2812.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN_Init();
  MX_TIM2_Init();
//  MX_TIM4_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  CAN_Init();
  delay_us_init();
  ws2812_set_color_1(128/3,224/3,0, 1);
  ws2812_send_buffer1();
  HAL_TIM_Base_Start_IT(&htim1);

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == STOP_Pin || GPIO_Pin == STOP_2_Pin) {
    if (switches.stop) {
      start_count = 30;
      ack.chassis_config_ack = false;
      HAL_TIM_Base_Start_IT(&htim4);
    } else if (switches.start) {
      stop_count = 30;
      HAL_TIM_Base_Start_IT(&htim4);
    }
  }
  // if (GPIO_Pin == STOP_2_Pin) {
  //   if (switches.stop_2) {
  //     HAL_TIM_Base_Start_IT(&htim2);
  //     ack.chassis_config_ack = false;
  //   } else if (switches.start_2) {
  //   }
  // }
}

// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//   switches_t *s = &switches;
//   static uint32_t timer2_count = 0;

//   if(htim == &htim2) {
//     if (timer2_count < 800) {
//       timer2_count++;
//       return;
//     }
//     else {
//       timer2_count = 0;
//       if (HAL_GPIO_ReadPin(STOP_2_GPIO_Port, STOP_2_Pin) == GPIO_PIN_RESET) {
//         start_count_2++;
//         if (start_count_2 > 30) {
//           //intereaction_send_can_message(2);
//           s->stop_2 = false;
//           s->start_2 = true;
//         }
//         if (start_count_2 >= 100) {
//           start_count_2 = 0;
//           HAL_TIM_Base_Stop_IT(&htim2);
//         }
//       }
//       else {
//         start_count_2 = 0;
//         HAL_TIM_Base_Stop_IT(&htim2);
//       }
//     }

//   }

//   if(htim == &htim3) {
//     if (HAL_GPIO_ReadPin(STOP_GPIO_Port, STOP_Pin) == GPIO_PIN_RESET) {
//       stop_count_1++;
//       if (stop_count_1 > 30) {
// //        intereaction_send_can_message(2);
//         s->stop_1 = true;
//         s->start_1 = false;
//      }
//       if (stop_count_1 >= 100) {
//         stop_count_1 = 0;
//         HAL_TIM_Base_Stop_IT(&htim3);
//       }
//     }
//     else {
//       stop_count_1 = 0;
//       HAL_TIM_Base_Stop_IT(&htim3);
//     }
//   }

//   if(htim == &htim4) {
//     if (HAL_GPIO_ReadPin(STOP_GPIO_Port, STOP_Pin) == GPIO_PIN_SET) {
//       start_count_1++;
//       if (start_count_1 > 30) {
// 		s->stop_1 = false;
// 		s->start_1 = true;
// //        intereaction_send_can_message(1);
//       }
//       if (ack.chassis_config_ack || start_count_1 >= 300) {
//         start_count_1 = 0;
//         HAL_TIM_Base_Stop_IT(&htim4);
//       }
//     }
//     else {
//       start_count_1 = 0;
//       HAL_TIM_Base_Stop_IT(&htim4);
//     }
//   }
// }

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{	
		CAN_RxHeaderTypeDef RxMessage;
	  uint8_t RxData[8] = {0};
	
	  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, RxData);	
    
    intereacion_can_decode (RxMessage.StdId, RxData);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim) {
     if (htim == &RGB_TIMER) {
       HAL_TIM_PWM_Stop_DMA(htim, RGB_CHANNEL_1);
     }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
