/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <rtthread.h>
#include "app_main.h"

#define MOTOR_CTRL
#define MOTOR_COUNT

// motor ctrl define
#ifdef MOTOR_CTRL
#define motor_ctrl_rcc                    	RCC_APB2Periph_GPIOA
#define motor_ctrl_gpio                   	GPIOA
#define motor_ctrl_pin                    	GPIO_Pin_8

#define MOTOR_ON		                	GPIO_SetBits(motor_ctrl_gpio, motor_ctrl_pin)//;rt_kprintf("马达-ON\r\n")
#define MOTOR_OFF	                		GPIO_ResetBits(motor_ctrl_gpio, motor_ctrl_pin)//;rt_kprintf("马达-OFF\r\n")
#endif

#ifdef MOTOR_COUNT
#define motor_count_rcc                    	RCC_APB2Periph_GPIOA
#define motor_count_gpio                   	GPIOA
#define motor_count_pin                    	GPIO_Pin_7

#define motor_count_port_source            	GPIO_PortSourceGPIOA
#define motor_count_pin_source             	GPIO_PinSource7
#define motor_count_exti_line              	EXTI_Line7
#define motor_count_nvic_irq               	EXTI9_5_IRQn

#define MOTOR_PULSE_RD		               	GPIO_ReadInputDataBit(motor_count_gpio, motor_count_pin)
#endif

void rt_hw_motor_init(void);

#endif
