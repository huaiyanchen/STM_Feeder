/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */
#include <app_netRecv.h>

void td_netRecv_init(TD_NET_RECV *p)
{
}

void td_netRecv_deal(TD_NET_RECV *p)
{
	p->tick++;
}

