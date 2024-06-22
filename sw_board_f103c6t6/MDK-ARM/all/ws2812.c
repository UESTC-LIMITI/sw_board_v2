/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-05-21 16:57:46
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-05-26 09:45:34
 * @FilePath: \MDK-ARM\ws2812\ws2812.c
 * @Description: 
 * 
 * Copyright (c) 2024 by UESTC_LIMITI, All Rights Reserved. 
 */
#include "ws2812.h"
#include "tim.h"

Ws2812_Work_Mode_t RGB_Work_Mode;

#if defined (CCCR_BIT_32)
uint32_t send_buffer1[RESET_NUM + WS2812_NUM*24];
uint32_t send_buffer2[RESET_NUM + WS2812_NUM*24];
#else
uint16_t send_buffer1[RESET_NUM + WS2812_NUM*24];
uint16_t send_buffer2[RESET_NUM + WS2812_NUM*24];
#endif



void ws2812_set_color_1 (uint8_t R, uint8_t G, uint8_t B, uint32_t index) {
	if (index > WS2812_NUM - 1) {
		return;
	}
	int i;
  float ratio = 0.8;
  R *= ratio;
  G *= ratio;
  B *= ratio;
	for (i = 0; i < 8; i++) {
		if ((G << i) & 0x80) send_buffer1[RESET_NUM + index*24 + i] = CODE_1;
		else send_buffer1[RESET_NUM + index*24 + i] = CODE_0;
	}
	for (i = 0; i < 8; i++) {
		if ((R << i) & 0x80) send_buffer1[RESET_NUM + index*24 + 8 + i] = CODE_1;
		else send_buffer1[RESET_NUM + 8 + index*24 + i] = CODE_0;
	}
	for (i = 0; i < 8; i++) {
		if ((B << i) & 0x80) send_buffer1[RESET_NUM + index*24 + 16 + i] = CODE_1;
		else send_buffer1[RESET_NUM + 16 + index*24 + i] = CODE_0;
	}
}

void ws2812_send_buffer1 (void) {
	memset(send_buffer1, 0, sizeof(uint16_t)*RESET_NUM); //由于放在set函数中循环可能太多，造成额外开销，所以放在发送函数中
	HAL_TIM_PWM_Start_DMA (&RGB_TIMER, RGB_CHANNEL_1, (uint32_t *)send_buffer1, BUFFER_NUM);
}
/**
 * 需要加的中断回调函数
 */
// void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim) {
//      if (htim == &RGB_TIMER) {
//        HAL_TIM_PWM_Stop_DMA(htim, RGB_CHANNEL);
//      }
// }

void ws2812_set_all_green_1 (uint32_t rgb_num, uint8_t intensity) {
	if (rgb_num > WS2812_NUM) {
		return;
	}
	int i, j;
	memset(send_buffer1, 0, sizeof(uint16_t)*BUFFER_NUM);
	for (j = 0; j < rgb_num; j++) {
		for (i = 0; i < 8; i++) {
			if ((intensity << i) & 0x80) send_buffer1[RESET_NUM + j*24 + i] = CODE_1;
			else send_buffer1[RESET_NUM + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
			send_buffer1[RESET_NUM + 8 + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
      send_buffer1[RESET_NUM + 16 + j*24 + i] = CODE_0;
		}
	}
}

void ws2812_set_all_red_1 (uint32_t rgb_num, uint8_t intensity) {
	if (rgb_num > WS2812_NUM) {
		return;
	}
	int i, j;
	memset(send_buffer1, 0, sizeof(uint16_t)*BUFFER_NUM);
	for (j = 0; j < rgb_num; j++) {
		for (i = 0; i < 8; i++) {
			send_buffer1[RESET_NUM + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
			if ((intensity << i) & 0x80) send_buffer1[RESET_NUM + j*24 + 8 + i] = CODE_1;
			else send_buffer1[RESET_NUM + 8 + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
      send_buffer1[RESET_NUM + 16 + j*24 + i] = CODE_0;
		}
	}
}

void ws2812_set_all_blue_1 (uint32_t rgb_num, uint8_t intensity) {
	if (rgb_num > WS2812_NUM) {
		return;
	}
	int i, j;
	memset(send_buffer1, 0, sizeof(uint16_t)*BUFFER_NUM);
	for (j = 0; j < rgb_num; j++) {
		for (i = 0; i < 8; i++) {
      send_buffer1[RESET_NUM + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
      send_buffer1[RESET_NUM + 8 + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
			if ((intensity << i) & 0x80) send_buffer1[RESET_NUM + j*24 + 16 + i] = CODE_1;
			else send_buffer1[RESET_NUM + 16 + j*24 + i] = CODE_0;
		}
	}
}


/*********************************** 第二个灯板 ***************************************/

void ws2812_set_color_2 (uint8_t R, uint8_t G, uint8_t B, uint32_t index) {
	if (index > WS2812_NUM - 1) {
		return;
	}
	int i;
  float ratio = 0.8;
  R *= ratio;
  G *= ratio;
  B *= ratio;
	for (i = 0; i < 8; i++) {
		if ((G << i) & 0x80) send_buffer2[RESET_NUM + index*24 + i] = CODE_1;
		else send_buffer2[RESET_NUM + index*24 + i] = CODE_0;
	}
	for (i = 0; i < 8; i++) {
		if ((R << i) & 0x80) send_buffer2[RESET_NUM + index*24 + 8 + i] = CODE_1;
		else send_buffer2[RESET_NUM + 8 + index*24 + i] = CODE_0;
	}
	for (i = 0; i < 8; i++) {
		if ((B << i) & 0x80) send_buffer2[RESET_NUM + index*24 + 16 + i] = CODE_1;
		else send_buffer2[RESET_NUM + 16 + index*24 + i] = CODE_0;
	}
}

void ws2812_send_buffer2 (void) {
	memset(send_buffer2, 0, sizeof(uint16_t)*RESET_NUM); //由于放在set函数中循环可能太多，造成额外开销，所以放在发送函数中
	HAL_TIM_PWM_Start_DMA (&RGB_TIMER, RGB_CHANNEL_2, (uint32_t *)send_buffer2, BUFFER_NUM);
}
/**
 * 需要加的中断回调函数
 */
// void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim) {
//      if (htim == &RGB_TIMER) {
//        HAL_TIM_PWM_Stop_DMA(htim, RGB_CHANNEL);
//      }
// }

void ws2812_set_all_green_2 (uint32_t rgb_num, uint8_t intensity) {
	if (rgb_num > WS2812_NUM) {
		return;
	}
	int i, j;
	memset(send_buffer2, 0, sizeof(uint16_t)*BUFFER_NUM);
	for (j = 0; j < rgb_num; j++) {
		for (i = 0; i < 8; i++) {
			if ((intensity << i) & 0x80) send_buffer2[RESET_NUM + j*24 + i] = CODE_1;
			else send_buffer2[RESET_NUM + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
			send_buffer2[RESET_NUM + 8 + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
      send_buffer2[RESET_NUM + 16 + j*24 + i] = CODE_0;
		}
	}
}

void ws2812_set_all_red_2 (uint32_t rgb_num, uint8_t intensity) {
	if (rgb_num > WS2812_NUM) {
		return;
	}
	int i, j;
	memset(send_buffer2, 0, sizeof(uint16_t)*BUFFER_NUM);
	for (j = 0; j < rgb_num; j++) {
		for (i = 0; i < 8; i++) {
			send_buffer2[RESET_NUM + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
			if ((intensity << i) & 0x80) send_buffer2[RESET_NUM + j*24 + 8 + i] = CODE_1;
			else send_buffer2[RESET_NUM + 8 + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
      send_buffer2[RESET_NUM + 16 + j*24 + i] = CODE_0;
		}
	}
}

void ws2812_set_all_blue_2 (uint32_t rgb_num, uint8_t intensity) {
	if (rgb_num > WS2812_NUM) {
		return;
	}
	int i, j;
	memset(send_buffer2, 0, sizeof(uint16_t)*BUFFER_NUM);
	for (j = 0; j < rgb_num; j++) {
		for (i = 0; i < 8; i++) {
      send_buffer2[RESET_NUM + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
      send_buffer2[RESET_NUM + 8 + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
			if ((intensity << i) & 0x80) send_buffer2[RESET_NUM + j*24 + 16 + i] = CODE_1;
			else send_buffer2[RESET_NUM + 16 + j*24 + i] = CODE_0;
		}
	}
}

// void ws2812_run()
// {
// 	switch (RGB_Work_Mode)
// 	{
// 		case RGB_IDLE:
// 			ws2812_set_all_red_2(16, 0);
// 			break;
// 		case RED_ON:
// 			ws2812_set_all_red_2(16, 127);
// 			break;
// 		case GREEN_ON:
// 			ws2812_set_all_green_2(16, 127);
// 			break;
// 		case RED_GREEN_BLINK:
// 			if (Auto.time % 2 == 1)
// 			{
// 				ws2812_set_all_green_2(16, 127);
// 			}
// 			else
// 			{
// 				ws2812_set_all_red_2(16, 127);
// 			}
// 			break;
// 	}
// 	ws2812_send_buffer2();
// }

