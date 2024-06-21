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
/**
 * 外设使用情况：
 * timer3 -> stop_1
 * timer4 -> start_1
 * timer1 -> stop_2
 * timer2 -> start_2
 * s7 -> 备用急停
 * s2 -> 红蓝区
 * s3 -> 通信自检和各设备自检
 * s5 -> 视觉一区启动
 * s6 -> 视觉二区启动 
 */
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
#define DESICION_Pin GPIO_PIN_5
#define DESICION_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_7
#define SW1_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_8
#define SW2_GPIO_Port GPIOB
#define STOP_2_Pin GPIO_PIN_9
#define STOP_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
