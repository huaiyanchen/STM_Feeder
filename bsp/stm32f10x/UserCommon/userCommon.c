/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#include <userCommon.h>

void Delay500ns(void)
{
	u8 i;
	i=4;
	while(i--);
}

void rt_hw_us_delay(rt_uint32_t us)
{
	rt_uint32_t delta;
	rt_uint32_t current_delay;
	us = us * (SysTick->LOAD/(1000000/RT_TICK_PER_SECOND));
	delta = SysTick->VAL;
	/* 循环获得当前时间，直到达到指定的时间后退出循环 */
	do
	{
		if ( delta > SysTick->VAL ){
			current_delay = delta - SysTick->VAL;
		}else{
		/* 延时跨越了一次OS tick的边界时的处理 */
			current_delay = SysTick->LOAD + delta - SysTick->VAL;
		}
	} while( current_delay < us );
}

/*hex(char) --> int*/
rt_uint8_t hex2u8(rt_uint8_t c)
{
     rt_uint8_t tmp=0;
     
     if(c>='0' && c<='9'){
        tmp= c-'0';
     }else if(c>='A' && c<='F'){
        tmp=c-'A'+10;
     }else if(c>='a' && c<='f'){
        tmp=c-'a'+10;
     }
     
     return tmp;
}

void InvertUint16(unsigned short *dBuf,unsigned short *srcBuf)
{
	int i;
	unsigned short tmp[4];
	tmp[0] = 0;
	for(i=0;i< 16;i++)
	{
		if(srcBuf[0]& (1 << i))
		tmp[0]|=1<<(15 - i);
	}
	dBuf[0] = tmp[0];
}

void InvertUint8(unsigned char *dBuf,unsigned char *srcBuf)
{
	int i;
	unsigned char tmp[4];
	tmp[0] = 0;
	for(i=0;i< 8;i++)
	{
		if(srcBuf[0]& (1 << i))
		 tmp[0]|=1<<(7-i);
	}
	dBuf[0] = tmp[0];
}

unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen)
{
	unsigned short wCRCin = 0xFFFF;
	unsigned short wCPoly = 0x8005;
	unsigned char wChar = 0;
	
	while (usDataLen--) 	
	{
		wChar = *(puchMsg++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin) ;
}

