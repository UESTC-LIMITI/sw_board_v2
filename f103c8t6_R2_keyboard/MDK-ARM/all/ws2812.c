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

uint16_t send_buffer[RESET_NUM + WS2812_NUM*24];
 
void ws2812_set_color (uint8_t R, uint8_t G, uint8_t B, uint32_t index) {
	if (index > WS2812_NUM - 1) {
		return;
	}
	int i;
	for (i = 0; i < 8; i++) {
		if ((G << i) & 0x80) send_buffer[RESET_NUM + index*24 + i] = CODE_1;
		else send_buffer[RESET_NUM + index*24 + i] = CODE_0;
	}
	for (i = 0; i < 8; i++) {
		if ((R << i) & 0x80) send_buffer[RESET_NUM + index*24 + 8 + i] = CODE_1;
		else send_buffer[RESET_NUM + 8 + index*24 + i] = CODE_0;
	}
	for (i = 0; i < 8; i++) {
		if ((B << i) & 0x80) send_buffer[RESET_NUM + index*24 + 16 + i] = CODE_1;
		else send_buffer[RESET_NUM + 16 + index*24 + i] = CODE_0;
	}
}

void ws2812_send_buffer (void) {
	memset(send_buffer, 0, sizeof(uint16_t)*RESET_NUM); //由于放在set函数中循环可能太多，造成额外开销，所以放在发送函数中
	HAL_TIM_PWM_Start_DMA (&htim1, TIM_CHANNEL_1, (uint32_t *)send_buffer, BUFFER_NUM);
}
/**
 * 需要加的中断回调函数
 */
// void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim) {
//   HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
// }

void ws2812_set_all_green (uint32_t rgb_num, uint8_t intensity) {
	if (rgb_num > WS2812_NUM) {
		return;
	}
	int i, j;
	memset(send_buffer, 0, sizeof(uint16_t)*BUFFER_NUM);
	for (j = 0; j < rgb_num; j++) {
		for (i = 0; i < 8; i++) {
			if ((intensity << i) & 0x80) send_buffer[RESET_NUM + j*24 + i] = CODE_1;
			else send_buffer[RESET_NUM + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
			send_buffer[RESET_NUM + 8 + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
      send_buffer[RESET_NUM + 16 + j*24 + i] = CODE_0;
		}
	}
}

void ws2812_set_all_red (uint32_t rgb_num, uint8_t intensity) {
	if (rgb_num > WS2812_NUM) {
		return;
	}
	int i, j;
	memset(send_buffer, 0, sizeof(uint16_t)*BUFFER_NUM);
	for (j = 0; j < rgb_num; j++) {
		for (i = 0; i < 8; i++) {
			send_buffer[RESET_NUM + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
			if ((intensity << i) & 0x80) send_buffer[RESET_NUM + j*24 + 8 + i] = CODE_1;
			else send_buffer[RESET_NUM + 8 + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
      send_buffer[RESET_NUM + 16 + j*24 + i] = CODE_0;
		}
	}
}

void ws2812_set_all_blue (uint32_t rgb_num, uint8_t intensity) {
	if (rgb_num > WS2812_NUM) {
		return;
	}
	int i, j;
	memset(send_buffer, 0, sizeof(uint16_t)*BUFFER_NUM);
	for (j = 0; j < rgb_num; j++) {
		for (i = 0; i < 8; i++) {
      send_buffer[RESET_NUM + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
      send_buffer[RESET_NUM + 8 + j*24 + i] = CODE_0;
		}
		for (i = 0; i < 8; i++) {
			if ((intensity << i) & 0x80) send_buffer[RESET_NUM + j*24 + 16 + i] = CODE_1;
			else send_buffer[RESET_NUM + 16 + j*24 + i] = CODE_0;
		}
	}
}



