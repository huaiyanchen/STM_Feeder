/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#ifndef __KEY_H__
#define __KEY_H__

#include "app_main.h"

#include <rtthread.h>
// key define
// #define KEY_1 //ˮλ���
#define KEY_2 //SW1
#define KEY_3 //SW2
#define KEY_4 //SW3
#define KEY_5 //SW4
#define KEY_6	//PIG IN

/* KEY_1 */
#ifdef KEY_1
#define key1_rcc                    RCC_APB2Periph_GPIOA
#define key1_gpio                   GPIOA
#define key1_pin                    (GPIO_Pin_6)
// #define key1_rcc                    RCC_APB2Periph_GPIOC
// #define key1_gpio                   GPIOC
// #define key1_pin                    (GPIO_Pin_0)

//#define key1_port_source            GPIO_PortSourceGPIOB
//#define key1_pin_source             GPIO_PinSource4
//#define key1_exti_line              EXTI_Line4
//#define key1_nvic_irq               EXTI4_IRQn

#define key1_stt		            GPIO_ReadInputDataBit(key1_gpio, key1_pin)
#define CHK_WATER_LIMIT             key1_stt
#endif

/* KEY_2 */
#ifdef KEY_2 //SW1
#define key2_rcc                    RCC_APB2Periph_GPIOC
#define key2_gpio                   GPIOC
#define key2_pin                    (GPIO_Pin_6)
#define key2_led_pin                (GPIO_Pin_1)

#define key2_port_source            GPIO_PortSourceGPIOC
#define key2_pin_source             GPIO_PinSource6
#define key2_exti_line              EXTI_Line6
#define key2_nvic_irq               EXTI9_5_IRQn

#define key2_stt		            GPIO_ReadInputDataBit(key2_gpio, key2_pin)
#define SW1_STT_ON                     Bit_SET == key2_stt
#define SW1_LED_OFF                 GPIO_ResetBits(key2_gpio, key2_led_pin)
#define SW1_LED_ON                  GPIO_SetBits(key2_gpio, key2_led_pin)
#endif

/* KEY_3 */
#ifdef KEY_3 //SW2
#define key3_rcc                    RCC_APB2Periph_GPIOC
#define key3_gpio                   GPIOC
#define key3_pin                    (GPIO_Pin_7)
#define key3_led_pin                (GPIO_Pin_2)

#define key3_port_source            GPIO_PortSourceGPIOC
#define key3_pin_source             GPIO_PinSource7
#define key3_exti_line              EXTI_Line7
#define key3_nvic_irq               EXTI9_5_IRQn

#define key3_stt		            GPIO_ReadInputDataBit(key3_gpio, key3_pin)
#define SW2_STT_ON                     Bit_SET == key3_stt
#define SW2_LED_OFF                  GPIO_ResetBits(key3_gpio, key3_led_pin)
#define SW2_LED_ON                 GPIO_SetBits(key3_gpio, key3_led_pin)
#endif

/* KEY_4 */
#ifdef KEY_4 //SW3
#define key4_rcc                    RCC_APB2Periph_GPIOC
#define key4_gpio                   GPIOC
#define key4_pin                    (GPIO_Pin_8)
#define key4_led_pin                (GPIO_Pin_3)

#define key4_port_source            GPIO_PortSourceGPIOC
#define key4_pin_source             GPIO_PinSource8
#define key4_exti_line              EXTI_Line8
#define key4_nvic_irq               EXTI9_5_IRQn

#define key4_stt		            GPIO_ReadInputDataBit(key4_gpio, key4_pin)
#define SW3_STT_ON                     Bit_SET == key4_stt
#define SW3_LED_OFF                  GPIO_ResetBits(key4_gpio, key4_led_pin)
#define SW3_LED_ON                 GPIO_SetBits(key4_gpio, key4_led_pin)
#endif

/* KEY_5 */
#ifdef KEY_5 //SW4
#define key5_rcc                    RCC_APB2Periph_GPIOC
#define key5_gpio                   GPIOC
#define key5_pin                    (GPIO_Pin_9)
#define key5_led_pin                (GPIO_Pin_4)

#define key5_port_source            GPIO_PortSourceGPIOC
#define key5_pin_source             GPIO_PinSource9
#define key5_exti_line              EXTI_Line9
#define key5_nvic_irq               EXTI9_5_IRQn

#define key5_stt		            GPIO_ReadInputDataBit(key5_gpio, key5_pin)
#define SW4_STT_ON                     Bit_SET == key5_stt
#define SW4_LED_OFF                  GPIO_ResetBits(key5_gpio, key5_led_pin)
#define SW4_LED_ON                 GPIO_SetBits(key5_gpio, key5_led_pin)
#endif

/* KEY_6 */
#ifdef KEY_6
#define key6_rcc                    RCC_APB2Periph_GPIOA
#define key6_gpio                   GPIOA
#define key6_pin                    (GPIO_Pin_10)

//#define key1_port_source            GPIO_PortSourceGPIOB
//#define key1_pin_source             GPIO_PinSource4
//#define key1_exti_line              EXTI_Line4
//#define key1_nvic_irq               EXTI4_IRQn

#define key6_stt		            GPIO_ReadInputDataBit(key6_gpio, key6_pin)
#define CHK_PIG_IN                  Bit_RESET == key6_stt
#endif

#define RESET_KEY                   0x01
#define PLUS_KEY                    0x02
#define MINUS_KEY                   0x04
#define CONTRAL_KEY                 0x08
#define RESET_KEY_LONG              0x10

void rt_hw_key_init(void);

#endif
