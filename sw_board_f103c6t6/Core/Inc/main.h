/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CHASSIS_LED_Pin GPIO_PIN_3
#define CHASSIS_LED_GPIO_Port GPIOA
#define TAKE_IN_LED_Pin GPIO_PIN_4
#define TAKE_IN_LED_GPIO_Port GPIOA
#define ROBOTIC_ARM_LED_Pin GPIO_PIN_5
#define ROBOTIC_ARM_LED_GPIO_Port GPIOA
#define COMM_LED_Pin GPIO_PIN_6
#define COMM_LED_GPIO_Port GPIOA
#define BLUE_AREA_Pin GPIO_PIN_15
#define BLUE_AREA_GPIO_Port GPIOA
#define RED_AREA_Pin GPIO_PIN_3
#define RED_AREA_GPIO_Port GPIOB
#define STOP_Pin GPIO_PIN_4
#define STOP_GPIO_Port GPIOB
#define STOP_EXTI_IRQn EXTI4_IRQn
#define DECISION_Pin GPIO_PIN_5
#define DECISION_GPIO_Port GPIOB
#define SELF_CHECK_Pin GPIO_PIN_6
#define SELF_CHECK_GPIO_Port GPIOB
#define VISION_START_1_Pin GPIO_PIN_7
#define VISION_START_1_GPIO_Port GPIOB
#define VISION_START_2_Pin GPIO_PIN_8
#define VISION_START_2_GPIO_Port GPIOB
#define STOP_2_Pin GPIO_PIN_9
#define STOP_2_GPIO_Port GPIOB
#define STOP_2_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
