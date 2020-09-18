/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#ifndef __TD_NET_TASK_H__
#define __TD_NET_TASK_H__

#include <rtthread.h>
#include <stm32f10x.h>
#include "usart.h"
#include "userCommon.h"

typedef struct
{
	rt_uint32_t  tick;
	
	void (*init)();
	void (*deal)(); 
}TD_NET_TASK;

#define NEW_TD_NET_TASK  {0,\
    (void (*)(rt_uint32_t))td_netTask_init,\
    (void (*)(rt_uint32_t))td_netTask_deal\
}

extern TD_NET_TASK _td_netTask;

void td_netTask_init(TD_NET_TASK *p);
void td_netTask_deal(TD_NET_TASK *p);

#endif
