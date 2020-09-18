#ifndef __DEV_FLASH_H__
#define __DEV_FLASH_H__

#include "rtthread.h"
#include <stm32f10x.h>
#include "fm24cl.h"

typedef struct
{
    rt_bool_t mRwMutex;
}FLASH_DATA;

typedef struct
{
    const char *name; //dev name   
    
	FLASH_DATA data;
	
    rt_uint8_t (*init)();
    rt_uint8_t (*pack)();
    rt_uint8_t (*unpack)();
    rt_uint8_t (*read)();
    rt_uint8_t (*write)();
    rt_uint8_t (*control)();
}IOT_DEVICE_FLASH;

typedef IOT_DEVICE_FLASH * IOT_DEV_FLASH_Handle;

#define IOT_DEVICE_FLASH_INIT  {"DEV_FLASH",\
	{0},\
    (rt_uint8_t (*)(rt_uint32_t))dev_flash_init,\
    RT_NULL,\
    RT_NULL,\
    (rt_uint8_t (*)(rt_uint32_t))dev_flash_read,\
    (rt_uint8_t (*)(rt_uint32_t))dev_flash_write,\
    RT_NULL\
}

extern IOT_DEVICE_FLASH devFlash;

rt_uint8_t dev_flash_init();
rt_uint8_t dev_flash_read(IOT_DEVICE_FLASH *p, rt_uint16_t addr, rt_uint8_t *buf, rt_uint8_t len);
rt_uint8_t dev_flash_write(IOT_DEVICE_FLASH *p, rt_uint16_t addr, rt_uint8_t *buf, rt_uint8_t len);

#endif
