/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#ifndef __USER_COMMON_H__
#define __USER_COMMON_H__

#include <rtthread.h>
#include <stm32f10x.h>
#include "rtdef.h"
     
/* drv inc */
//#include "led.h"
#include "usart.h"

#define LOG_GSM_DATA_EN     0

#define DEV_UART1   1
#define DEV_UART2   2
#define DEV_UART3   3
#define DEV_UART4   4
#define DEV_UART5   5

/* timer define */
#define _TIMER_FUN_1S

#include "app_main.h"
#include "app_netRecv.h"
#include "app_netTask.h"

/* thread define */
#define _THREAD_MAIN
//#define _THREAD_NET_RECV
//#define _THREAD_NET_TASK

/* function define */
//#define METER_MONITOR_FUN

#define RET_UNKNOW		0x00
#define RET_OK			0x01
#define RET_FAIL		0x02
#define RET_SUSPEND 	0x03
#define RET_CRC_ERR 	0x04
#define RET_CRC_ERR_FF	0x05
#define RET_CRC_ERR_00	0x06

//消息队列控制块
//static struct rt_messagequeue mq;
//static rt_mq_t mq = RT_NULL;
//消息队列中用到的放置消息的内存池
//static char msg_pool[2048];

//void rt_hw_us_delay(rt_uint32_t us);
void Delay500ns(void);
rt_uint8_t hex2u8(rt_uint8_t c);
unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen);

#endif
