/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#ifndef __TD_NET_RECV_H__
#define __TD_NET_RECV_H__

#include <rtthread.h>
#include <stm32f10x.h>
#include "userCommon.h"
#include "rtthread.h"

typedef struct
{
      rt_uint32_t  tick;
	  
      void (*init)();
      void (*deal)(); 
}TD_NET_RECV;

#define NEW_TD_NET_RECV  {0,\
    (void (*)(rt_uint32_t))td_netRecv_init,\
    (void (*)(rt_uint32_t))td_netRecv_deal\
}

extern TD_NET_RECV _td_netRecv;

void td_netRecv_init(TD_NET_RECV *p);
void td_netRecv_deal(TD_NET_RECV *p);

#endif
