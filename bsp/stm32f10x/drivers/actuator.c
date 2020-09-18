/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */
#include <stm32f10x.h>
#include <actuator.h>

void rt_hw_actuator_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
#ifdef WATER_PUMP
    RCC_APB2PeriphClockCmd(water_pump_rcc,ENABLE);
    GPIO_InitStructure.GPIO_Pin = water_pump_pin;
    GPIO_Init(water_pump_gpio, &GPIO_InitStructure);
    WATER_PUMP_OFF;
#endif
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void tst_water_pump(int argc, char** argv){
        if ( argv[1][0] == '0' ){
                /* set led status */
        #ifdef WATER_PUMP
                WATER_PUMP_OFF;			
        #endif
                rt_kprintf("water pump off\r\n");
        }else if ( argv[1][0] == '1' ){
                /* set led status */
        #ifdef WATER_PUMP
                WATER_PUMP_ON;			
        #endif
                rt_kprintf("water pump on\r\n");
        }
}
MSH_CMD_EXPORT(tst_water_pump, set pump on[1] or off[0] );
#endif

