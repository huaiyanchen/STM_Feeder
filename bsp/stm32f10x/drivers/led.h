/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#ifndef __LED_H__
#define __LED_H__

#include <rtthread.h>

#define LED_1	0
#define LED_2	1
#define LED_3	2

#define LED_RED			LED_1
#define LED_GREEN		LED_2
#define LED_BLUE		LED_3

#define LED_POWER		LED_1
#define LED_NET			LED_2
#define LED_CARD		LED_3

void rt_hw_led_init(void);
void rt_hw_led_on(rt_uint8_t led);
void rt_hw_led_off(rt_uint8_t led);

#endif
