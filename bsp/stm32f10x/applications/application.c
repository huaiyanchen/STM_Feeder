/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2013-07-12     aozima       update for auto initial.
 */

/**
 * @addtogroup STM32registTimeOut
 */
/*@{*/

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>
#include <rtgui/calibration.h>
#endif

#include "led.h"
	 
#include "app_main.h"
#include "app_netRecv.h"
#include "app_netTask.h"
#include "usart.h"

#include "dev_flash.h"

ALIGN(RT_ALIGN_SIZE)

//dev define
IOT_DEVICE_FLASH devFlash = IOT_DEVICE_FLASH_INIT;

//thread element define
TD_MAIN _td_main = NEW_TD_MAIN;
TD_NET_RECV _td_netRecv = NEW_TD_NET_RECV;
TD_NET_TASK _td_netTask = NEW_TD_NET_TASK;

//link dev define
ITS_UART _uart = ITS_UART_DEFAULTS;
void KeyScan ( TD_MAIN *p );
#ifdef RT_USING_RTGUI
rt_bool_t cali_setup(void)
{
    rt_kprintf("cali setup entered\n");
    return RT_FALSE;
}

void cali_store(struct calibration_data *data)
{
    rt_kprintf("cali finished (%d, %d), (%d, %d)\n",
               data->min_x,
               data->max_x,
               data->min_y,
               data->max_y);
}
#endif /* RT_USING_RTGUI */

void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif

    /* Filesystem Initialization */
#if defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System initialized!\n");
    }
    else
        rt_kprintf("File System initialzation failed!\n");
#endif  /* RT_USING_DFS */

#ifdef RT_USING_RTGUI
    {
        extern void rt_hw_lcd_init();
        extern void rtgui_touch_hw_init(void);

        rt_device_t lcd;

        /* init lcd */
        rt_hw_lcd_init();

        /* init touch panel */
        rtgui_touch_hw_init();

        /* find lcd device */
        lcd = rt_device_find("lcd");

        /* set lcd device as rtgui graphic driver */
        rtgui_graphic_set_device(lcd);

#ifndef RT_USING_COMPONENTS_INIT
        /* init rtgui system server */
        rtgui_system_server_init();
#endif

        calibration_set_restore(cali_setup);
        calibration_set_after(cali_store);
        calibration_init();
    }
#endif /* #ifdef RT_USING_RTGUI */
}


static void fun_timeOut_10ms(void* parameter)
{
  KeyScan(&_td_main);
}


#ifdef _TIMER_FUN_1S
static void fun_timeOut_1s(void* parameter)
{
//    rt_uint8_t i = 0x00;
	
	// float mParam = 0x00;
	// rt_uint16_t mShift = 0x00;
    // static rt_uint8_t netLinkTime = 0x00;
    
    // static rt_uint8_t time5s = 0x00;
    static rt_uint8_t ledFlg = 1;
    if(_td_main.feedInfo.feed_each_time > 0){
        _td_main.feedInfo.feed_each_time--;
    }
	if(ledFlg==1){
        rt_hw_led_on(LED_RED);
        // rt_hw_led_on(LED_GREEN);
        // rt_hw_led_on(LED_BLUE);
		ledFlg = 0x00;
	}else{
		rt_hw_led_off(LED_RED);
        // rt_hw_led_off(LED_GREEN);
        // rt_hw_led_off(LED_BLUE);
		ledFlg = 0x01;
	}

    //ιʳʱ��-��ʱ
    _td_main.feedInfo.feed_time_second++;
    if( _td_main.feedInfo.feed_time_second >= 60 ){
        _td_main.feedInfo.feed_time_second = 0x00;
        _td_main.feedInfo.feed_time_min++;
        if(_td_main.feedInfo.feed_time_min == 24*60){
            _td_main.feedInfo.feed_time_min = 0;   //ÿ���ʱ������
            _td_main.dev.stt.motor_total_count++;  //ÿ��ĵ��Ȧ������
        }
        rt_kprintf("ʱ�䣺%02d:%02d\r\n", _td_main.feedInfo.feed_time_min/60, _td_main.feedInfo.feed_time_min%60);
    }

    //ιʳ���-��ʱ
    _td_main.feedInfo.feed_time_interval++;
    if( _td_main.feedInfo.feed_time_interval>=(FEED_CHK_INTERVAL_30S+6) ){
        _td_main.feedInfo.feed_time_interval = 0x00;
//		_td_main.dev.stt.motor_count = 0x00;
    }
    if( (_td_main.feedInfo.feed_time_interval%10)==0x00){ //10s
        rt_kprintf("ιʳ���ʱ�䣺%02d\r\n", _td_main.feedInfo.feed_time_interval);
    }
    
	
#if 0////
	if( _td_main.dev.tst.time<0xff ) _td_main.dev.tst.time++;
    
    //ota 
    if( _td_main.dev.ota.stt == 0x03 ){       
        if(_td_main.dev.ota.timeOut < 6){
            _td_main.dev.ota.timeOut++;
        }else{
            _td_main.dev.ota.timeOut = 0x00;
            _td_main.dev.ota.stt = 0x01;
            _td_main.dev.ota.stFlg = RT_TRUE;
        }
    }
    
    netLinkTime++;
    if( (netLinkTime%8) == 0x00 ){
        if( !_td_netTask.dev.stt.isLogin ){
            devVoice.write(&devVoice, SD_NET_CONN);
        }
        netLinkTime = 0x00;
    }
    
	
	//count timeout
	_td_netTask.dev.timeOut.at++;
	_td_netTask.dev.timeOut.csq++;
	_td_netTask.dev.timeOut.login++;
	_td_netTask.dev.timeOut.hrt++;
	
	_td_netRecv.msg.tcp.registTimeOut++;
    _td_netRecv.msg.tcp.cmdTimeOut++;
    _td_netRecv.msg.tcp.atTimeOut++;
    
    //voice handler
    devVoice.data.time++;
    if(devVoice.data.time>=1){
        devVoice.data.type = 0x00;
    }
    
	//voice of key
    if( _td_rfid.key.pressFlg ){       
        TM1640_DisplayNum(2, 10-_td_rfid.key.timeOut); 
        
        //tip: voice
        if( ((10-_td_rfid.key.timeOut)%3)==0x00 ){
            devVoice.write(&devVoice, SD_PAY_CARD);
        }
        
        if(_td_rfid.key.timeOut>=10){
            devVoice.write(&devVoice, SD_PAY_TIMEOUT);
            _td_rfid.key.pressFlg = RT_FALSE;
        }
        
        _td_rfid.key.timeOut++;
    }
    
    //show card money
    if( RT_TRUE == _td_main.dev.card.showMoneyFlg ){
        TM1640_ShowMoney(_td_main.dev.card.money);
        if(_td_main.dev.card.showMoneyTime==2){
            devVoice.write(&devVoice, SD_BALANCE);
        }
        if(_td_main.dev.card.showMoneyTime==3){
            _td_main.dev.card.voiceMoneyFlg = RT_TRUE;
        }
        _td_main.dev.card.showMoneyTime++;
        if( _td_main.dev.card.showMoneyTime >= 4 ){           
            _td_main.dev.card.showMoneyFlg = RT_FALSE;
        }      
    }

    //charge timer & power tick
    for(i=0;i<_td_main.dev.stt.socketSum;i++){
        //priority (card & qr)
        if( _td_main.dev.card.priorityFlg[i] == RT_TRUE ){
            _td_main.dev.card.priorityTimeout[i]++;
            if( _td_main.dev.card.priorityTimeout[i] >= 11 ){
                 _td_main.dev.card.priorityFlg[i] = RT_FALSE;
            }
        }
        
        if( APP_CHARGE_START == _td_main.dev.stt.socketStt[i] ){ //on charge           
            if(_td_main.dev.stt.currW[i] > _td_main.dev.rule.powerLev4){ //over power time
#if 1
                _td_pwTask.stt.overPwTick[i]++;
#endif
                _td_pwTask.stt.fullTime[i] = 0x00;
                _td_pwTask.stt.powerShift[i] = 4;
            }else if( _td_main.dev.stt.currW[i] > _td_main.dev.rule.powerLev3 ){ //shift 4
                _td_pwTask.stt.powerShift[i] = 4;
                _td_pwTask.stt.fullTime[i] = 0x00;
                _td_pwTask.stt.overPwTick[i] = 0x00;
            }else if( _td_main.dev.stt.currW[i] > _td_main.dev.rule.powerLev2 ){ //shift 3
                _td_pwTask.stt.powerShift[i] = 3;
                _td_pwTask.stt.fullTime[i] = 0x00;
                _td_pwTask.stt.overPwTick[i] = 0x00;
            }else if( _td_main.dev.stt.currW[i] > _td_main.dev.rule.powerLev1 ){ //shift 2
                _td_pwTask.stt.powerShift[i] = 2;
                _td_pwTask.stt.fullTime[i] = 0x00;
                _td_pwTask.stt.overPwTick[i] = 0x00;
            }else if( _td_main.dev.stt.currW[i] < _td_main.dev.rule.fullPower ){ //charge full time
#if 1
                _td_pwTask.stt.fullTime[i]++;
#endif
                _td_pwTask.stt.overPwTick[i] = 0x00;
                _td_pwTask.stt.powerShift[i] = 1; //shift 1				
            }else{
                _td_pwTask.stt.overPwTick[i] = 0x00;
                _td_pwTask.stt.fullTime[i] = 0x00;
                _td_pwTask.stt.powerShift[i] = 1; //shift 1
            }
#if 1
			if( _td_main.dev.stt.currW[i] < 5 ){ //no load time
				_td_pwTask.stt.noLoadTime[i]++;
			}else{
				_td_pwTask.stt.noLoadTime[i]=0x00;
			}
#endif
			
            //calc time & vol
			if( _td_pwTask.stt.powerShift[i] == 4 ){ //shift 4
				mShift = _td_main.dev.rule.paramLev4;
			}else if( _td_pwTask.stt.powerShift[i] == 3 ){ //shift 3
				mShift = _td_main.dev.rule.paramLev3;
			}else if( _td_pwTask.stt.powerShift[i] == 2 ){ //shift 2
				mShift = _td_main.dev.rule.paramLev2;
			}else{ //shift 1
				mShift = _td_main.dev.rule.paramLev1;
			}
			
            if( 0x01 == _td_main.dev.rule.chargeMode ){ //time mode
                //time
                mParam = ((_td_main.dev.rule.paramLev1*1.0/mShift)/60.0);
                
                if(_td_main.dev.stt.restTime[i]>=mParam){
                    _td_main.dev.stt.restTime[i] -= mParam;
                }else{
                    _td_main.dev.stt.restTime[i] = 0x00;
                }
                _td_main.dev.stt.runTime[i] += mParam;
                //money
                mParam = ((_td_main.dev.rule.paramLev1*1.0/mShift)/60.0)*(_td_main.dev.rule.prePayment*1.0/_td_main.dev.rule.paramLev1);
                if(_td_main.dev.stt.restCash[i]>=mParam){
                    _td_main.dev.stt.restCash[i] -= mParam;
                }else{
                    _td_main.dev.stt.restCash[i] = 0x00;
                    _td_main.dev.stt.restTime[i] = 0x00;
                }
                _td_main.dev.stt.runCash[i] += mParam;
            }else{ //vol mode
                time5s++;
                if( time5s >= 5 ){
                    //time
                    mParam = (5.0/60.0);
                    _td_main.dev.stt.runTime[i] += mParam;
                    if( _td_main.dev.stt.pwKwhRegCurr[i] > _td_main.dev.stt.pwKwhRegShiftBegin[i] ){
                        //vol
                        mParam = (1638.4*256.0*1.218*1.218*(20.0*5.0+0.051)/(3600000.0*4046.0*1000.0*1.0*0.051))*(_td_main.dev.stt.pwKwhRegCurr[i] - _td_main.dev.stt.pwKwhRegShiftBegin[i])  *1.038672*1.333*0.7272;
                        if(_td_main.dev.stt.restVol[i]>=(mParam*1000)){
                            _td_main.dev.stt.restVol[i] -= (mParam*1000);
                        }else{
                            _td_main.dev.stt.restVol[i] = 0x00;
                        }
                        //money
                        mParam = mShift*mParam; // ��Ǯ
                        if(_td_main.dev.stt.restCash[i]>=mParam){
                            _td_main.dev.stt.restCash[i] -= mParam;
                        }else{
                            _td_main.dev.stt.restCash[i] = 0x00;
                            _td_main.dev.stt.restVol[i] = 0x00;
                        }
                        _td_main.dev.stt.runCash[i] += mParam;
                        _td_main.dev.stt.pwKwhRegShiftBegin[i] = _td_main.dev.stt.pwKwhRegCurr[i];
                    }
                    
                    time5s = 0x00;
                }
            }
        }else{ //on stop
            _td_pwTask.stt.fullTime[i] = 0x00;
            _td_pwTask.stt.overPwTick[i] = 0x00;
            _td_pwTask.stt.powerShift[i] = 0x00;
			_td_pwTask.stt.noLoadTime[i] = 0x00;
			_td_main.dev.stt.maxW[i] = 0x00;
        }
    }
#endif
}
#endif

#ifdef _THREAD_MAIN
static void rt_main_thread_entry(void* parameter)
{    
	_td_main.init( &_td_main );
	while (1){
		_td_main.deal( &_td_main );  
        rt_thread_delay(10);//100ms      
    }
}
#endif

#ifdef _THREAD_NET_RECV
static void rt_netRecv_thread_entry(void* parameter)
{
    _td_netRecv.init( &_td_netRecv );
    while(1){
        _td_netRecv.deal( &_td_netRecv );
        rt_thread_delay(10);//100ms
    }
}
#endif

#ifdef _THREAD_NET_TASK
static void rt_netTask_thread_entry(void* parameter)
{
    _td_netTask.init( &_td_netTask );
    while(1){
        _td_netTask.deal( &_td_netTask );
        rt_thread_delay(10);//100ms
    }
}
#endif

#ifdef _THREAD_PW_TASK
static void rt_pwTask_thread_entry(void* parameter)
{
    _td_pwTask.init( &_td_pwTask );
    while(1){
        _td_pwTask.deal( &_td_pwTask );
        rt_thread_delay(10);//100ms
    }
}
#endif

#ifdef _THREAD_RFID_TASK
static void rt_rfidTask_thread_entry(void* parameter)
{
    _td_rfid.init( &_td_rfid );
    while(1){
        _td_rfid.deal( &_td_rfid );
        rt_thread_delay(10);//100ms
    }
}
#endif

int rt_application_init(void)
{
    rt_thread_t mThread;
    rt_timer_t mTimer ,mTimer2;
//	rt_err_t result;
    
    _uart.init(&_uart);
    
    /* create timer 1s */
#ifdef _TIMER_FUN_1S
    mTimer = rt_timer_create("timer1s",             /* name of timer */
                                fun_timeOut_1s,     /* call back fun*/
                                RT_NULL,            /* call back fun param */
                                100,                /* 100 OS Tick( 1 tick = 10ms) */
                                RT_TIMER_FLAG_PERIODIC);    /* periodic */
    if( mTimer != RT_NULL ){
        rt_timer_start(mTimer);
    }
    
    mTimer2 = rt_timer_create("mTimer10ms",fun_timeOut_10ms,RT_NULL,1,RT_TIMER_FLAG_PERIODIC);
    if ( mTimer2 != RT_NULL){
         rt_timer_start(mTimer2);
    }
#endif
	
	/* ��ʼ����Ϣ���� */
//	mq = rt_mq_create("mqt",
//					  128,
//					  16,
//					  RT_IPC_FLAG_FIFO);
	
//	result = rt_mq_init(mq, "mqt",
//			  &msg_pool[0],        /* �ڴ��ָ��msg_pool */
//			  128 - sizeof(void*), /* ÿ����Ϣ�Ĵ�С�� 128 - void* */
//			  sizeof(msg_pool),    /* �ڴ�صĴ�С��msg_pool�Ĵ�С */
//			  RT_IPC_FLAG_FIFO);   /* ����ж���̵߳ȴ�������FIFO�ķ���������Ϣ */
//	
//	if(result!=RT_EOK){
//		rt_kprintf("init message queue failed!\r\n");
//		return -1;
//	}
	
#if 0//tst
	rt_uint8_t buf[128];
	rt_memset(&buf[0], 0, sizeof(buf));
	while(rt_mq_recv(tst_mq, &buf[0], sizeof(buf), RT_WAITING_NO) == RT_EOK){
		rt_kprintf(">>> get msg\r\n");
	}
	while(1);
#endif
    
	/* init rtos thread */
	mThread = rt_thread_create("tdInit",
                                   rt_init_thread_entry, RT_NULL,
                                   512, 1, 20);
	if( mThread != RT_NULL ){
        rt_thread_startup(mThread);
	}
	
#ifdef _THREAD_MAIN
    /* init main thread */
	mThread = rt_thread_create("tdMain",
                                   rt_main_thread_entry, RT_NULL,
                                   512+256, 1, 20);
	if( mThread != RT_NULL ){
        rt_thread_startup(mThread);
	} 
#endif
    
#ifdef _THREAD_NET_RECV
    /* init net recv thread */
	mThread = rt_thread_create("tdNetRecv",
                                   rt_netRecv_thread_entry, RT_NULL,
                                   1024+512+512+256+512+512, 1, 20);
	if( mThread != RT_NULL ){
        rt_thread_startup(mThread);
	} 
#endif
    
#ifdef _THREAD_NET_TASK
    /* init net task thread */
	mThread = rt_thread_create("tdNetTask",
                                   rt_netTask_thread_entry, RT_NULL,
                                   1024+512+512+256+512+256+128+512+256, 1, 20);
	if( mThread != RT_NULL ){
        rt_thread_startup(mThread);
	} 
#endif

    return 0;
}

/*@}*/
