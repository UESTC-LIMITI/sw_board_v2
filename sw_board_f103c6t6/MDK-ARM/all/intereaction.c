/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-06-11 08:54:07
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-06-21 20:02:24
 * @FilePath: \MDK-ARM\all\intereaction.c
 * @Description: 
 * 按键板V2 TODO：
 * 1. 不再使用急停按钮的版本，配置双按钮来启动，用一个灯表示下一次是急停/启动，定时器执行按键消抖/colddown
 * 2. 自检亮灯
 * 3. ws2812监测DT35在线状态
 * 4. 需要开线程了，按键扫描 can发送 LED和WS2812控制
 * Copyright (c) 2024 by UESTC_LIMITI, All Rights Reserved. 
 */
#include "intereaction.h"

switches_t switches = {
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	true,
	false,
	false,
	false,
	false,
	false,
	};
int32_t stop_count = 0;
int32_t start_count = 0;
int32_t dt35_offline_count = 0;
int32_t dt35_offline_id = 0;
// uint32_t stop_count_2 = 0;
// uint32_t start_count_2 = 0;
acknowledge_t ack = {false};


void intereaction_scan_sw(void) {
	switches_t *s = &switches;
	//视觉启动 自检 决策点 轮询读按键 
	if (HAL_GPIO_ReadPin(VISION_START_1_GPIO_Port, VISION_START_1_Pin) == GPIO_PIN_SET) {
		s->vision_start_1 = true;
	} else {
		s->vision_start_1 = false;
	}
	if (HAL_GPIO_ReadPin(VISION_START_2_GPIO_Port, VISION_START_2_Pin) == GPIO_PIN_SET) {
		s->vision_start_1 = true;
	} else {
		s->vision_start_1 = false;
	}
	if (HAL_GPIO_ReadPin(SELF_CHECK_GPIO_Port, SELF_CHECK_Pin) == GPIO_PIN_SET) {
		s->self_check = true;
	} else {
		s->self_check = false;
	}
	
	if (HAL_GPIO_ReadPin(DECISION_GPIO_Port, DECISION_Pin) == GPIO_PIN_SET) {
		s->pick_point_2 = true;
		s->pick_point_1 = false;
	} else {
		s->pick_point_1 = true;
		s->pick_point_2 = false;
	}
	
	//读启动按钮状态，调试用
	if (HAL_GPIO_ReadPin(STOP_GPIO_Port, STOP_Pin) == GPIO_PIN_SET || HAL_GPIO_ReadPin(STOP_2_GPIO_Port, STOP_2_Pin) == GPIO_PIN_SET) {
		s->stop = true;
	} else {
		s->stop = false;
	}

	//轮询读红蓝区
	if (HAL_GPIO_ReadPin(BLUE_AREA_GPIO_Port, BLUE_AREA_Pin) == GPIO_PIN_SET) {
		s->in_blue = true;
		s->in_red = false;
	} else if (HAL_GPIO_ReadPin(RED_AREA_GPIO_Port, RED_AREA_Pin) == GPIO_PIN_SET) {
		s->in_red = true;
		s->in_blue = false;
	}

	//延时消抖
	if (s->vision_start_1_last != s->vision_start_1) {
		osDelay(20);
		if (HAL_GPIO_ReadPin(VISION_START_1_GPIO_Port, VISION_START_1_Pin) == GPIO_PIN_SET) {
			s->vision_start_1 = true;
		} else {
			s->vision_start_1 = false;
		}
	}
	if (s->vision_start_2_last != s->vision_start_2) {
		osDelay(20);
		if (HAL_GPIO_ReadPin(VISION_START_2_GPIO_Port, VISION_START_2_Pin) == GPIO_PIN_SET) {
			s->vision_start_2 = true;
		} else {
			s->vision_start_2 = false;
		}
	}
	if (s->self_check_last != s->self_check) {
		osDelay(20);
		if (HAL_GPIO_ReadPin(SELF_CHECK_GPIO_Port, SELF_CHECK_Pin) == GPIO_PIN_SET) {
			s->self_check = true;
		} else {
			s->self_check = false;
		}
	}

	//更新最后状态
	s->vision_start_1_last = s->vision_start_1;
	s->vision_start_2_last = s->vision_start_2;
	s->self_check_last = s->self_check;
	
}

//按照飞书文档来
uint8_t buffer[2];
void intereaction_send_can_message(uint8_t index) {
	uint16_t stdid = 0;
  HAL_CAN_Start(&hcan); // 开启CAN

	switch (index)
	{
	case 1:
		stdid = START;
		memset(buffer, 0, sizeof(buffer));
		if (switches.in_blue) {
			buffer[0] = 0x01;
		} else if (switches.in_red) {
			buffer[0] = 0x02;
		} else {
		buffer[0] = 0x00;
		}
		if (switches.pick_point_2) {
			buffer[1] = 0x02;
		} else {
			buffer[1] = 0x01;
		}
		CAN_Send_Message (stdid, buffer, 2);
		break;
	
	case 2:
		stdid = STOP;
		CAN_Send_Message (stdid, NULL, 0);
		break;
		
	case 3:
		stdid = SELF_CHECK;
		CAN_Send_Message (stdid, NULL, 0);
		break;

	case 4:
		stdid = VISTION_RESTART_2;
		CAN_Send_Message (stdid, NULL, 0);
		break;

	case 5:
		stdid = AREA;
		if (switches.in_blue) {
			buffer[0] = 0x01;
		} else if (switches.in_red) {
			buffer[0] = 0x02;
		} else {
		buffer[0] = 0x00;
		}
		CAN_Send_Message (stdid, buffer, 2);
		break;
		
	case 6:
		stdid = VISTION_RESTART_1;
		CAN_Send_Message (stdid, NULL, 0);
		break;

	default:
		break;
		
	}

}

void intereacion_can_decode (uint32_t stdid, uint8_t *Rxdata) {
	switch (stdid) {
		case 0x02f:
			ack.chassis_config_ack = true;
			break;
			
		case 0x011:
			ack.usb2can_com_ack = true;
			break;
			
		case 0x123:
			ack.chassis_com_ack = true;
			break;
			
		case 0x03f:
			ack.robotoc_arm_com_ack = true;
			break;
			
		case 0x00a:
			ack.take_in_com_ack = true;
			break;
			
		case 0x051:
			ack.dt35_1_online = true;
			break;
			
		case 0x061:
			ack.dt35_2_online = true;
			break;
			
		case 0x071:
			ack.dt35_3_online = true;
			break;
			
		case 0x081:
			ack.dt35_4_online = true;
			break;
			
		case 0x091:
			ack.dt35_5_online = true;
			break;
			
		case 0x0a1:
			ack.dt35_6_online = true;
			break;
			
		// case 0x00c:
		// 	ack.chassis_sc_ack = true;
		// 	break;
			
		// case 0x00d:
		// 	ack.take_in_sc_ack = true;
		// 	break;
			
			
		default:
			break;
	}
}

void intereacion_dt35_offline_check (void) {
	ack.dt35_1_online = false;
	ack.dt35_2_online = false;
	ack.dt35_3_online = false;
	ack.dt35_4_online = false;
	ack.dt35_5_online = false;
	ack.dt35_6_online = false;
	osDelay(100);  //延时等待接收
	if (!ack.dt35_1_online) {
		dt35_offline_id = 1;
	} 
	else if (!ack.dt35_2_online) {
		dt35_offline_id = 2;
	}
	else if (!ack.dt35_3_online) {
		dt35_offline_id = 3;
	}
	else if (!ack.dt35_4_online) {
		dt35_offline_id = 4;
	}
	else if (!ack.dt35_5_online) {
		dt35_offline_id = 5;
	}
	else if (!ack.dt35_6_online) {
		dt35_offline_id = 6;
	}
	else dt35_offline_id = 0;
	for (int i = dt35_offline_count; i; i--) {
		ws2812_set_color_1(255/3,23/3,49/3, 1);
		ws2812_send_buffer1();
		osDelay(400);
		ws2812_set_color_1(128/3,224/3,0, 1);
		ws2812_send_buffer1();
		osDelay(400);
	}
}

/*****************************RGB控制**************************** */

void intereacion_led_control (void) {
	if (ack.chassis_com_ack) {
		HAL_GPIO_WritePin(CHASSIS_LED_GPIO_Port, CHASSIS_LED_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(CHASSIS_LED_GPIO_Port, CHASSIS_LED_Pin, GPIO_PIN_RESET);
	}

	if (ack.usb2can_com_ack) {
		HAL_GPIO_WritePin(COMM_LED_GPIO_Port, COMM_LED_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(COMM_LED_GPIO_Port, COMM_LED_Pin, GPIO_PIN_RESET);
	}

	if (ack.take_in_com_ack) {
		HAL_GPIO_WritePin(TAKE_IN_LED_GPIO_Port, TAKE_IN_LED_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(TAKE_IN_LED_GPIO_Port, TAKE_IN_LED_Pin, GPIO_PIN_RESET);
	}

	if (ack.robotoc_arm_com_ack) {
		HAL_GPIO_WritePin(ROBOTIC_ARM_LED_GPIO_Port, ROBOTIC_ARM_LED_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(ROBOTIC_ARM_LED_GPIO_Port, ROBOTIC_ARM_LED_Pin, GPIO_PIN_RESET);
	}

	intereacion_dt35_offline_check();

}

