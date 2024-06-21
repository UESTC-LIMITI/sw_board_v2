/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-06-11 08:53:58
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-06-18 23:24:10
 * @FilePath: \MDK-ARM\all\intereaction.h
 * @Description: 
 * 
 * Copyright (c) 2024 by UESTC_LIMITI, All Rights Reserved. 
 */
#ifndef __INTEREACTION_H__ 
#define __INTEREACTION_H__

#include "can.h"
#include "can_bsp.h"
#include "main.h"
#include "stdbool.h"
#include "tim.h"
#include "utils.h"
#include "string.h"

#define COMMUNICATION_TEST 0x00
#define START 0x01
#define STOP 0x02
#define SELF_CHECK 0x03
#define VISTION_RESTART_1 0x04
#define VISTION_RESTART_2 0x021
#define GO_TO_POINT_X 0x05
#define IN_BLUE_AREA 0x06
#define IN_RED_AREA 0x07

typedef struct {
	bool sw1;  //发送一次性状态
	bool sw1_last;
	bool sw2;  //设置第一次看球点，打开为2号点，关闭为1号点
	bool sw2_last;
	bool sw3;  //请求自检
	bool sw3_last;
	// bool sw4;
	// bool sw4_last;
	bool in_red;
	bool in_blue;
	bool stop_1;  //按下停止，抬起启动
	bool stop_1_last;  //按下停止，抬起启动
	bool stop_2;  //按下停止，抬起启动
	bool stop_2_last;  //按下停止，抬起启动
	bool start_1;
	bool start_1_last;
	bool start_2;
	bool start_2_last;
} switches_t;

typedef struct {
	bool chassis_config_ack;
	bool chassis_com_ack;
	bool usb2can_com_ack;
	bool take_in_com_ack;
	bool robotoc_arm_com_ack;
	bool chassis_sc_ack;
	bool take_in_sc_ack;
	bool robotoc_arm_sc_ack;
} acknowledge_t;

void intereaction_scan_sw(void);
void intereaction_send_can_message(uint8_t index);
void intereaction_single_send (void);
void intereacion_can_decode (uint32_t stdid, uint8_t *Rxdata);
extern switches_t switches;
extern uint32_t stop_count_1;
extern uint32_t start_count_1;
extern uint32_t stop_count_2;
extern uint32_t start_count_2;
extern acknowledge_t ack;

#endif
