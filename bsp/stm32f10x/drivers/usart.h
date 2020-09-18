/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#ifndef __USART_H__
#define __USART_H__

#include <rthw.h>
#include <rtthread.h>

#define UART_ENABLE_IRQ(n)            NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           NVIC_DisableIRQ((n))

typedef struct
{
      rt_device_t  COMDev1;       //通讯设备 uart1
      rt_device_t  COMDev2;       //通讯设备 uart2
      rt_device_t  COMDev3;       //通讯设备 uart3   
      rt_device_t  COMDev4;       //通讯设备 uart4  
      rt_device_t  COMDev5;       //通讯设备 uart5  

      void (*init)(); 
}ITS_UART;

typedef ITS_UART * ITS_UART_Handle;

#define ITS_UART_DEFAULTS  {RT_NULL,\
    RT_NULL,\
    RT_NULL,\
    RT_NULL,\
    RT_NULL,\
    (void (*)(rt_uint32_t))ITS_UART_Init\
}

extern ITS_UART _uart;

void ITS_UART_Init(ITS_UART_Handle);

void rt_hw_usart_init(void);
rt_size_t uart_get_ch(rt_uint8_t comIndex, rt_uint8_t *buf);
rt_size_t uart_send_buf(rt_uint8_t comIndex, char *buf, rt_uint8_t len);
#endif
