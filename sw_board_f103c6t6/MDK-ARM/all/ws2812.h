/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-05-21 16:58:01
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-05-30 20:11:46
 * @FilePath: \MDK-ARM\all\ws2812.h
 * @Description: 
 * 
 * Copyright (c) 2024 by UESTC_LIMITI, All Rights Reserved. 
 */
#ifndef __WS_2812_H__
#define __WS_2812_H__
 
#include "main.h"
#include "dma.h"
#include "string.h"
#include "tim.h"

/**
 * RGB 色表  自查：https://www.yansedaquan.com/RGBSearch?Number=3783611&Hex=39c5bb&rgb=57%2C197%2C187
 * 
 * 花と水飴、最終電車 245,158,147
 * 月を歩いている 6,44,134
 * ヨヒラ 255,23,49
 * 夜明けと蛍 90,123,142
 * だから僕は音楽を辞めた 162,70,43
 * エルマ 156,151,112
 * 夏草が邪魔をする 186,192,175
 * Alice in 冷凍庫 96,185,224
 * 未完成エイトビーツ 105,167,223
 * SEASIDE SOLILOQUIES 177,233,237
 * 八星 178,178,178
 * .CALLC. 242,145,56
 * 東方阿漕祭 237,80,58
 * 絶対にチョコミントを食べるアオイチャン 100,194,169
 * Seyana. 251,200,192
 * 
 * 第二集 128,224,0
 * 
 * 电黄色 255 255 51
 * 托里亚湾蓝 15 45 148
 * 初音色 57,197,187
 * 电科蓝 21,56,135
 * 电科橙 227,119,20
 * 天蓝色 118,215,234
*/
#define TIMER_ARR    RGB_TIMER.Instance->ARR
#define CODE_1       (uint32_t)TIMER_ARR*2/3     //1码定时器计数次数
#define CODE_0       (uint32_t)TIMER_ARR*1/3       //0码定时器计数次数

#define RGB_TIMER htim2
#define RGB_CHANNEL_1 TIM_CHANNEL_1
#define RGB_CHANNEL_2 TIM_CHANNEL_2
// #define CCCR_BIT_32
#define CCCR_BIT_16
 
/*建立一个定义单个LED三原色值大小的结构体*/
typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}RGB_Color_TypeDef;
 
#define WS2812_NUM 2  
#define RESET_NUM 225
#define BUFFER_NUM RESET_NUM + WS2812_NUM*24

typedef enum
{
	RGB_IDLE = 0x0U,
	RED_ON,
	GREEN_ON,
	RED_GREEN_BLINK,
} Ws2812_Work_Mode_t;

void ws2812_set_color_1 (uint8_t R, uint8_t G, uint8_t B, uint32_t index);
void ws2812_send_buffer1 (void);
void ws2812_set_all_green_1 (uint32_t rgb_num, uint8_t intensity);
void ws2812_set_all_red_1 (uint32_t rgb_num, uint8_t intensity);
void ws2812_set_all_blue_1 (uint32_t rgb_num, uint8_t intensity);

void ws2812_set_color_2 (uint8_t R, uint8_t G, uint8_t B, uint32_t index);
void ws2812_send_buffer2 (void);
void ws2812_set_all_green_2 (uint32_t rgb_num, uint8_t intensity);
void ws2812_set_all_red_2 (uint32_t rgb_num, uint8_t intensity);
void ws2812_set_all_blue_2 (uint32_t rgb_num, uint8_t intensity);

// void ws2812_run(void);

extern Ws2812_Work_Mode_t RGB_Work_Mode;

//extern uint16_t send_buffer[RESET_NUM + WS2812_NUM*24];
#endif
