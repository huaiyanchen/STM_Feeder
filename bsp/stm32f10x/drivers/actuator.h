/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#ifndef __WATER_PUMP_H__
#define __WATER_PUMP_H__

#include <rtthread.h>

#define WATER_PUMP	0

// water pump define
#ifdef WATER_PUMP
#define water_pump_rcc                    RCC_APB2Periph_GPIOA
#define water_pump_gpio                   GPIOA
#define water_pump_pin                    GPIO_Pin_4

#define WATER_PUMP_ON		            GPIO_SetBits(water_pump_gpio, water_pump_pin)//;rt_kprintf("Ë®±Ã-ON\r\n")
#define WATER_PUMP_OFF	                GPIO_ResetBits(water_pump_gpio, water_pump_pin)//;rt_kprintf("Ë®±Ã-OFF\r\n")
#endif

void rt_hw_actuator_init(void);

#endif
