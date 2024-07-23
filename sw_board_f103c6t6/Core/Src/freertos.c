/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "intereaction.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void CAN_send(void const * argument);
void RGBs_control(void const * argument);
void scan_switches(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, CAN_send, osPriorityNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, RGBs_control, osPriorityNormal, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, scan_switches, osPriorityIdle, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  { 
    //默认任务用来dt35闪灯吧
    //顺序闪灯，先小后大
    if (dt35_offline_status[0] + dt35_offline_status[1] + dt35_offline_status[2] + dt35_offline_status[3] + dt35_offline_status[4] + dt35_offline_status[5]) {
      if (dt35_offline_status[0]) {
        for (int i = 1; i; i--) {
          ws2812_set_color_1(255/4,23/4,49/4, 1);
          ws2812_send_buffer1();
          osDelay(200);
          ws2812_set_color_1(128/4,224/4,0, 1);
          ws2812_send_buffer1();
          osDelay(200);
          }
          osDelay(500);
      }
      if (dt35_offline_status[1]) {
        for (int i = 2; i; i--) {
          ws2812_set_color_1(255/4,23/4,49/4, 1);
          ws2812_send_buffer1();
          osDelay(200);
          ws2812_set_color_1(128/4,224/4,0, 1);
          ws2812_send_buffer1();
          osDelay(200);
          }
          osDelay(500);
      }
      if (dt35_offline_status[2]) {
        for (int i = 3; i; i--) {
          ws2812_set_color_1(255/4,23/4,49/4, 1);
          ws2812_send_buffer1();
          osDelay(200);
          ws2812_set_color_1(128/4,224/4,0, 1);
          ws2812_send_buffer1();
          osDelay(200);
          }
          osDelay(500);
      }
      if (dt35_offline_status[3]) {
        for (int i = 4; i; i--) {
          ws2812_set_color_1(255/4,23/4,49/4, 1);
          ws2812_send_buffer1();
          osDelay(200);
          ws2812_set_color_1(128/4,224/4,0, 1);
          ws2812_send_buffer1();
          osDelay(200);
          }
          osDelay(500);
      }
      if (dt35_offline_status[4]) {
        for (int i = 5; i; i--) {
          ws2812_set_color_1(255/4,23/4,49/4, 1);
          ws2812_send_buffer1();
          osDelay(200);
          ws2812_set_color_1(128/4,224/4,0, 1);
          ws2812_send_buffer1();
          osDelay(200);
          }
          osDelay(500);
      }
      if (dt35_offline_status[5]) {
        for (int i = 6; i; i--) {
          ws2812_set_color_1(255/4,23/4,49/4, 1);
          ws2812_send_buffer1();
          osDelay(200);
          ws2812_set_color_1(128/4,224/4,0, 1);
          ws2812_send_buffer1();
          osDelay(200);
          }
          osDelay(500);
      }
      osDelay(300);
    }

    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_CAN_send */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CAN_send */
void CAN_send(void const * argument)
{
  /* USER CODE BEGIN CAN_send */
  static int period_count = 0;
  /* Infinite loop */
  for(;;)
  {
    period_count++;
    if (period_count >= 1000) {
      period_count = 0;
      intereaction_send_can_message(5);
      osDelay(1);
      intereaction_send_can_message(4);
      osDelay(1);
    }
    if (switches.start_send_trigger) {
      switches.start_send_trigger = false;
      for (int i = 30; i; i--) {
        intereaction_send_can_message(1);
        osDelay(1);
      }
	  if (!pick_point_trigger) {
		pick_point_trigger = true;
	  }
    }
    else if (switches.stop_send_trigger) {
       switches.stop_send_trigger = false;
      for (int i = 30; i; i--) {
        intereaction_send_can_message(2);
        osDelay(1);
      }
    }
    osDelay(1);
  }
  /* USER CODE END CAN_send */
}

/* USER CODE BEGIN Header_RGBs_control */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RGBs_control */
void RGBs_control(void const * argument)
{
  /* USER CODE BEGIN RGBs_control */
  /* Infinite loop */
  for(;;)
  {
    intereacion_led_control();
    osDelay(1);
  }
  /* USER CODE END RGBs_control */
}

/* USER CODE BEGIN Header_scan_switches */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_scan_switches */
void scan_switches(void const * argument)
{
  /* USER CODE BEGIN scan_switches */
  /* Infinite loop */
  for(;;)
  {
    intereaction_scan_sw();
    osDelay(1);
  }
  /* USER CODE END scan_switches */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

