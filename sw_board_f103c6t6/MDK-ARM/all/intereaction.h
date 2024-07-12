/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-06-11 08:53:58
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-06-21 19:49:05
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
#include "cmsis_os.h"
#include "ws2812.h"

#define COMMUNICATION_TEST 0x00
#define START 0x01
#define STOP 0x02
#define SELF_CHECK 0x03
#define VISTION_RESTART_2 0x004
#define WAITING_CHOICE 0x004
#define VISTION_RESTART_1 0x006
#define GO_TO_POINT_X 0x05
#define AREA 0x05

typedef struct {
	bool vision_start_1;  
	bool vision_start_1_last;
	bool vision_start_2;  
	bool vision_start_2_last;
	bool self_check;  //请求自检
	bool self_check_last;
	bool pick_point_1; //设置第一次看球点，打开为2号点，关闭为1号点
	bool pick_point_2;

	bool stop;  
	bool stop_send_trigger; 
	bool start;
	bool start_send_trigger;

	bool in_red;
	bool in_blue;
} switches_t;

typedef struct {
	bool chassis_config_ack;
	bool chassis_com_ack;
	bool usb2can_com_ack_1;
	bool usb2can_com_ack_2;
	bool take_in_com_ack;
	bool robotoc_arm_com_ack;
	bool dt35_1_online;
	bool dt35_2_online;
	bool dt35_3_online;
	bool dt35_4_online;
	bool dt35_5_online;
	bool dt35_6_online;
	// bool chassis_sc_ack;
	// bool take_in_sc_ack;
	// bool robotoc_arm_sc_ack;
} acknowledge_t;

void intereaction_scan_sw(void);
void intereaction_send_can_message(uint8_t index);
void intereacion_can_decode (uint32_t stdid, uint8_t *Rxdata);
void intereacion_dt35_offline_check (void);
void intereacion_led_control (void);
extern switches_t switches;
extern int32_t stop_count;
extern int32_t start_count;
// extern uint32_t stop_count_2;
// extern uint32_t start_count_2;
extern acknowledge_t ack;
extern int32_t dt35_offline_count;
extern bool pick_point_trigger;
extern bool usb2can_led_blink_flag;
#endif
