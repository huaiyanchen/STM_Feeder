/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */
#include <rtthread.h>
#include <stm32f10x.h>
#include <key.h>



void rt_hw_key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 
#ifdef KEY_1
    RCC_APB2PeriphClockCmd(key1_rcc,ENABLE);
    GPIO_InitStructure.GPIO_Pin = key1_pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(key1_gpio, &GPIO_InitStructure);
	
//	GPIO_EXTILineConfig(key1_port_source, key1_pin_source);
//	EXTI_InitStructure.EXTI_Line = key1_exti_line;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 						
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0 );
//    NVIC_InitStructure.NVIC_IRQChannel = key1_nvic_irq;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef KEY_2
    RCC_APB2PeriphClockCmd(key2_rcc,ENABLE);
    GPIO_InitStructure.GPIO_Pin = key2_pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(key2_gpio, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = key2_led_pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(key2_gpio, &GPIO_InitStructure);
	SW1_LED_OFF;
	
//	GPIO_EXTILineConfig(key2_port_source, key2_pin_source);
//	EXTI_InitStructure.EXTI_Line = key2_exti_line;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 						
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0 );
//    NVIC_InitStructure.NVIC_IRQChannel = key2_nvic_irq;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef KEY_3
    RCC_APB2PeriphClockCmd(key3_rcc,ENABLE);
    GPIO_InitStructure.GPIO_Pin = key3_pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(key3_gpio, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = key3_led_pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(key3_gpio, &GPIO_InitStructure);
	SW2_LED_OFF;
	
//	GPIO_EXTILineConfig(key3_port_source, key3_pin_source);
//	EXTI_InitStructure.EXTI_Line = key3_exti_line;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 						
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0 );
//    NVIC_InitStructure.NVIC_IRQChannel = key3_nvic_irq;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef KEY_4
    RCC_APB2PeriphClockCmd(key4_rcc,ENABLE);
    GPIO_InitStructure.GPIO_Pin = key4_pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(key4_gpio, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = key4_led_pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(key4_gpio, &GPIO_InitStructure);
	SW3_LED_OFF;
	
//	GPIO_EXTILineConfig(key4_port_source, key4_pin_source);
//	EXTI_InitStructure.EXTI_Line = key4_exti_line;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 						
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0 );
//    NVIC_InitStructure.NVIC_IRQChannel = key4_nvic_irq;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef KEY_5
    RCC_APB2PeriphClockCmd(key5_rcc,ENABLE);
    GPIO_InitStructure.GPIO_Pin = key5_pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(key5_gpio, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = key5_led_pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(key5_gpio, &GPIO_InitStructure);
	SW4_LED_OFF;
	
//	GPIO_EXTILineConfig(key4_port_source, key4_pin_source);
//	EXTI_InitStructure.EXTI_Line = key4_exti_line;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 						
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0 );
//    NVIC_InitStructure.NVIC_IRQChannel = key4_nvic_irq;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
#endif
	
#ifdef KEY_6
    RCC_APB2PeriphClockCmd(key6_rcc,ENABLE);
    GPIO_InitStructure.GPIO_Pin = key6_pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(key6_gpio, &GPIO_InitStructure);
#endif

}



uint8_t Test_All_Keys ( void ) //测试所有按键
{
    uint8_t k1, k2, k3, k4, k;
    k1 = key2_stt;             //RSET  KEY
    k2 = key3_stt << 1;        //++
    k3 = key4_stt << 2;        //--
    k4 = key5_stt << 3;        // WATER_PUMP CONTRAL

    k = k1 | k2 | k3 | k4;
    return k;
}


void KeyScan ( TD_MAIN *p ) //键值扫描
{
    if(!p->Key_Strut.KeyPressFlag)
    {
        p->Key_Strut.key = Test_All_Keys();
        switch ( p->Key_Strut.KeyState )
        {
            case 0: //键按下
                p->Key_Strut.KeyCnt  = 0;
                p->Key_Strut.KeyLast = p->Key_Strut.key;
                if ( p->Key_Strut.KeyLast    != 0 )
                    p->Key_Strut.KeyState = 1;
                break;
            case 1: //防抖，如果按键键值变了，则重新等待按键按下
                if ( p->Key_Strut.KeyLast == p->Key_Strut.key )
                {
                    p->Key_Strut.KeyState = 2;
                    if(p->Key_Strut.KeyLast == RESET_KEY){
                            
                    }else if(p->Key_Strut.KeyLast == PLUS_KEY){
                            SW2_LED_ON;
                    }else if(p->Key_Strut.KeyLast == MINUS_KEY){
                            SW3_LED_ON;
                    }
                }
                else
                    p->Key_Strut.KeyState = 0;
                break;
            case 2://按键抬起
                if ( p->Key_Strut.key == 0 ) //如果当前所有按键都已经抬起
                {
                    p->Key_Strut.KeyValue = p->Key_Strut.KeyLast;
                    p->Key_Strut.KeyState = 0;
                    if ( ( p->Key_Strut.KeyValue == RESET_KEY )
                         || ( p->Key_Strut.KeyValue == PLUS_KEY )
                         || ( p->Key_Strut.KeyValue == MINUS_KEY )
                         || ( p->Key_Strut.KeyValue == CONTRAL_KEY ) ) //判断按键值是否正确
                    {
                        p->Key_Strut.KeyPressFlag = 1;
                        SW1_LED_OFF;
                        SW2_LED_OFF;
                        SW3_LED_OFF;
                    }
                    else    p->Key_Strut.KeyState = 0;
                }else{
                        if(p->Key_Strut.KeyLast == p->Key_Strut.key){
                             p->Key_Strut.KeyCnt++;
                             if(p->Key_Strut.KeyLast == RESET_KEY) SW1_LED_ON;                             
                             if(p->Key_Strut.KeyCnt > 200){
                                  p->Key_Strut.KeyValue = p->Key_Strut.KeyLast;
                                  if ( p->Key_Strut.KeyValue == RESET_KEY ){ //长按复位键
                                        p->Key_Strut.KeyValue = RESET_KEY_LONG;
                                        p->Key_Strut.KeyPressFlag = 1;
                                        p->Key_Strut.KeyState = 4;
                                  }  
                             }
                        }else{
                                p->Key_Strut.KeyState = 0;
                        }
                }
                break;
            case 4:
                if ( p->Key_Strut.key == 0 )
                {
                    p->Key_Strut.KeyState = 0;
                    p->Key_Strut.KeyCnt = 0;
                }
                break;
            default:
                break;
        }
    }
}


void keyproc(TD_MAIN *p)
{
    if(p->Key_Strut.KeyValue == RESET_KEY_LONG){
        if( FEED_PROGRAM_1 == p->feedInfo.feed_program ){
				p->dev.stt.motor_set_turns    = 32;
				p->feedInfo.feed_time_min = 17*60+20;  //?????趨??? 6:30
			}else if( FEED_PROGRAM_2 ==  p->feedInfo.feed_program ){
					  p->dev.stt.motor_set_turns    = 5;
					  p->feedInfo.feed_time_min = 17*60+10;  //?????趨??? 7:00	
			}else if( FEED_PROGRAM_3 ==  p->feedInfo.feed_program ){
                                          p->feedInfo.feed_time_min = 17*60+18;  //?????趨??? 7:00
                                          p->dev.stt.motor_set_turns = 85;
			}
    }else if(p->Key_Strut.KeyValue == PLUS_KEY){
        p->dev.stt.motor_set_turns++; 
    }else if(p->Key_Strut.KeyValue == MINUS_KEY){
        p->dev.stt.motor_set_turns--; 
    }else if(p->Key_Strut.KeyValue == CONTRAL_KEY){
             if(p->dev.stt.water_pump_flag == 0){  //??????????
                    p->dev.stt.water_pump_flag = 1;
                    WATER_PUMP_ON;
                    SW4_LED_ON;
			 }else{								  //????????
                        p->dev.stt.water_pump_flag = 0;
                        WATER_PUMP_OFF;
                        SW4_LED_OFF;
			 }
    }else if(p->Key_Strut.KeyValue == RESET_KEY){
             if(p->dev.stt.motor_flag == 0){
                p->dev.stt.key_set_motor_flag = 1;
             }
    }
    
}