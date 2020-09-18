/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */
#include <app_netTask.h>
#include "hw_iap.h"

__root const int downloadVersion @".downloadVersion" = 0x10; //v1.0

/*
v1.3更新小功率计费问题 
*/

void td_netTask_init(TD_NET_TASK *p)
{
}

void td_netTask_deal(TD_NET_TASK *p)
{
	p->tick++;
}
