/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-06-11 08:54:07
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-06-11 10:54:35
 * @FilePath: \MDK-ARM\Intereaction\intereaction.c
 * @Description: 
 * 
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
	true,
	false,
	};
uint32_t stop_count_1 = 0;
uint32_t start_count_1 = 0;
uint32_t stop_count_2 = 0;
uint32_t start_count_2 = 0;
acknowledge_t ack = {false};


void intereaction_scan_sw(void) {
	switches_t *s = &switches;
	if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == GPIO_PIN_SET) {
		s->sw1 = true;
	} else {
		s->sw1 = false;
	}
	if (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) == GPIO_PIN_SET) {
		s->sw2 = true;
	} else {
		s->sw2 = false;
	}
	if (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == GPIO_PIN_SET) {
		s->sw3 = true;
	} else {
		s->sw3 = false;
	}
	if (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == GPIO_PIN_SET)

//	if (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) == GPIO_PIN_SET) {
//		s->sw4 = true;
//	} else {
//		s->sw4 = false;
//	}

	if (HAL_GPIO_ReadPin(BLUE_AREA_GPIO_Port, BLUE_AREA_Pin) == GPIO_PIN_SET) {
		s->in_blue = true;
		s->in_red = false;
	} else if (HAL_GPIO_ReadPin(RED_AREA_GPIO_Port, RED_AREA_Pin) == GPIO_PIN_SET) {
		s->in_red = true;
		s->in_blue = false;
	}

	s->start_1_last = s->start_1;
	
	
}

uint8_t buffer[2];
void intereaction_send_can_message(uint8_t index) {
	uint32_t stdid = 0;
	switch (index)
	{
	case 1:
		intereaction_single_send();
		return;
		break;
	
	case 2:
		stdid = STOP;
		CAN_SendData (&hcan, NULL, stdid, 0);
		break;
		
	case 3:
		stdid = SELF_CHECK;
		CAN_SendData (&hcan, NULL, stdid, 0);
		break;

	case 4:
		stdid = VISTION_RESTART_1;
		CAN_SendData (&hcan, NULL, stdid, 0);
		break;

	case 5:
		stdid = GO_TO_POINT_X;
		if (switches.in_blue) {
			buffer[0] = 0x01;
		} else if (switches.in_red) {
			buffer[0] = 0x02;
		} else {
		buffer[0] = 0x00;
		}
		CAN_SendData (&hcan, buffer, stdid, 1);
		
	case 6:
		stdid = VISTION_RESTART_2;
		CAN_SendData (&hcan, NULL, stdid, 0);

	default:
		break;
	}

}

void intereaction_single_send (void) {
  memset(buffer, 0, sizeof(buffer));
	if (switches.in_blue) {
		buffer[0] = 0x01;
	} else if (switches.in_red) {
		buffer[0] = 0x02;
	} else {
    buffer[0] = 0x00;
  }
//  delay_us(1);
	if (switches.sw2) {
		buffer[1] = 0x02;
	} else {
		buffer[1] = 0x01;
	}
  CAN_SendData (&hcan, buffer, START, 2);
//  delay_us(1);
}

void intereacion_can_decode (uint32_t stdid, uint8_t *Rxdata) {
	if (stdid == 0x02f) {
		ack.chassis_config_ack = true;
	}
}
