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
#include <led.h>

// led define
#ifdef LED_1
#define led1_rcc                    RCC_APB2Periph_GPIOB
#define led1_gpio                   GPIOB
#define led1_pin                    GPIO_Pin_6

#define LED1_ON		                GPIO_ResetBits(led1_gpio, led1_pin)
#define LED1_OFF	                GPIO_SetBits(led1_gpio, led1_pin)
#endif

#ifdef LED_2
#define led2_rcc                    RCC_APB2Periph_GPIOC
#define led2_gpio                   GPIOC
#define led2_pin                    GPIO_Pin_13

#define LED2_ON		                GPIO_ResetBits(led2_gpio, led2_pin)
#define LED2_OFF	                GPIO_SetBits(led2_gpio, led2_pin)
#endif

#ifdef LED_3
#define led3_rcc                    RCC_APB2Periph_GPIOA
#define led3_gpio                   GPIOA
#define led3_pin                    GPIO_Pin_0

#define LED3_ON		                GPIO_ResetBits(led3_gpio, led3_pin)
#define LED3_OFF	                GPIO_SetBits(led3_gpio, led3_pin)
#endif

void rt_hw_led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
#ifdef LED_1
    RCC_APB2PeriphClockCmd(led1_rcc,ENABLE);
    GPIO_InitStructure.GPIO_Pin = led1_pin;
    GPIO_Init(led1_gpio, &GPIO_InitStructure);
    rt_hw_led_off(LED_1);
#endif

#ifdef LED_2
    RCC_APB2PeriphClockCmd(led2_rcc,ENABLE);
    GPIO_InitStructure.GPIO_Pin = led2_pin;
    GPIO_Init(led2_gpio, &GPIO_InitStructure);    
    rt_hw_led_off(LED_2);
#endif
	
#ifdef LED_3
    RCC_APB2PeriphClockCmd(led3_rcc,ENABLE);
    GPIO_InitStructure.GPIO_Pin = led3_pin;
    GPIO_Init(led3_gpio, &GPIO_InitStructure);    
    rt_hw_led_off(LED_3);
#endif
}

void rt_hw_led_on(rt_uint8_t n)
{
    switch (n){
    case 0:
#ifdef LED_1
        LED1_ON;
#endif
        break;
    case 1:
#ifdef LED_2
        LED2_ON;
#endif
        break;
	case 2:
#ifdef LED_3
        LED3_ON;
#endif
        break;
    default:
        break;
    }
}

void rt_hw_led_off(rt_uint8_t n)
{
    switch (n){
    case 0:
#ifdef LED_1
        LED1_OFF;
#endif
        break;
    case 1:
#ifdef LED_2
        LED2_OFF;
#endif
        break;
	case 2:
#ifdef LED_3
        LED3_OFF;
#endif
        break;
    default:
        break;
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void tst_led(int argc, char** argv){
	if ( argv[1][0] == '0' ){
        /* set led status */
#ifdef LED_1
        rt_hw_led_off(LED_1);			
#endif
#ifdef LED_2
        rt_hw_led_off(LED_2);			
#endif
#ifdef LED_3
        rt_hw_led_off(LED_3);			
#endif
		rt_kprintf("led off\r\n");
	}else if ( argv[1][0] == '1' ){
        /* set led status */
#ifdef LED_1
        rt_hw_led_on(LED_1);			
#endif
#ifdef LED_2
        rt_hw_led_on(LED_2);			
#endif
#ifdef LED_3
        rt_hw_led_on(LED_3);			
#endif
		rt_kprintf("led on\r\n");
    }
}
MSH_CMD_EXPORT(tst_led, set led on[1] or off[0] );
#endif

