/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-05-21 16:58:01
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-05-26 10:30:19
 * @FilePath: \MDK-ARM\ws2812\ws2812.h
 * @Description: 
 * 
 * Copyright (c) 2024 by UESTC_LIMITI, All Rights Reserved. 
 */
#ifndef __WS_2812_H__
#define __WS_2812_H__
 
#include "main.h"
#include "dma.h"
#include "string.h"

#define CODE_1       (58)       //1码定时器计数次数
#define CODE_0       (25)       //0码定时器计数次数

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
 * 电黄色 255 255 51
 * 托里亚湾蓝 15 45 148
 * 初音色 57,197,187
 * 电科蓝 21,56,135
 * 电科橙 227,119,20
 * 天蓝色 118,215,234
*/


 
/*建立一个定义单个LED三原色值大小的结构体*/
typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}RGB_Color_TypeDef;
 
#define WS2812_NUM 16  
#define RESET_NUM 225
#define BUFFER_NUM RESET_NUM + WS2812_NUM*24

void ws2812_set_color (uint8_t R, uint8_t G, uint8_t B, uint32_t index);
void ws2812_send_buffer (void);
void ws2812_set_all_green (uint32_t rgb_num, uint8_t intensity);
void ws2812_set_all_red (uint32_t rgb_num, uint8_t intensity);
void ws2812_set_all_blue (uint32_t rgb_num, uint8_t intensity);

extern uint16_t send_buffer[RESET_NUM + WS2812_NUM*24];
#endif
