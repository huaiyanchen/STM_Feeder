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
#include <motor.h>

void rt_hw_motor_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

#ifdef MOTOR_CTRL
    RCC_APB2PeriphClockCmd(motor_ctrl_rcc, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = motor_ctrl_pin;
    GPIO_Init(motor_ctrl_gpio, &GPIO_InitStructure);
    MOTOR_OFF;
#endif

#ifdef MOTOR_COUNT
    RCC_APB2PeriphClockCmd(motor_count_rcc, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = motor_count_pin;
    GPIO_Init(motor_count_gpio, &GPIO_InitStructure);  
	
	GPIO_EXTILineConfig(motor_count_port_source, motor_count_pin_source);
	EXTI_InitStructure.EXTI_Line = motor_count_exti_line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//EXTI_Trigger_Rising; 						
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0 );
    NVIC_InitStructure.NVIC_IRQChannel = motor_count_nvic_irq;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void tst_motor(int argc, char** argv){
	if ( argv[1][0] == '0' ){
#ifdef MOTOR_CTRL
        MOTOR_OFF;		
		rt_kprintf("MOTOR COUNT: %d\r\n",_td_main.dev.stt.motor_count);
#endif
		rt_kprintf("motor off\r\n");
	}else if ( argv[1][0] == '1' ){
#ifdef MOTOR_CTRL
        MOTOR_ON;	
		_td_main.dev.stt.motor_count = 0x00;
#endif
		rt_kprintf("motor on\r\n");
    }
}
MSH_CMD_EXPORT(tst_motor, set motor on[1] or off[0] );
#endif

