/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */
#include <app_main.h>

#ifdef METER_MONITOR_FUN
//485
static char kwh485ReqData[20] = {0xFE ,0xFE ,0xFE ,0xFE ,0x68 ,0x50 ,0x98 ,0x01 ,0x22 ,0x05 ,0x19 ,0x68 ,0x11 ,0x04 ,0x33 ,0x33 ,0x34 ,0x33 ,0xDB ,0x16};
#endif

void td_main_init(TD_MAIN *p)
{
	p->feedInfo.feed_time_min = 0;
	rt_kprintf("ʱ�䣺%02d:%02d\r\n", _td_main.feedInfo.feed_time_min/60, _td_main.feedInfo.feed_time_min%60);
	p->feedInfo.feed_program = FEED_PROGRAM_1;
	p->dev.stt.motor_turns = 1; //Ĭ��һ??
	p->feedInfo.feed_season = 0x00; //�ļ�
	p->feedInfo.feed_each_time = 0;
	p->dev.stt.water_pump_flag = 0; //��ŷ�Ĭ��Ϊ�ر�״�?
	WATER_PUMP_OFF;
	MOTOR_OFF;
	p->dev.stt.motor_total_count = 0;
	p->dev.stt.motor_count = 0;
	p->Key_Strut.key = 0;
        p->Key_Strut.KeyCnt = 0;
        p->Key_Strut.KeyState = 0;
        p->Key_Strut.KeyLast = 0;
        p->Key_Strut.KeyValue = 0;
        p->Key_Strut.KeyPressFlag = 0;
	if( FEED_PROGRAM_1 == p->feedInfo.feed_program ){
				p->dev.stt.motor_set_turns    = 32;
	}else if( FEED_PROGRAM_2 ==  p->feedInfo.feed_program ){
				p->dev.stt.motor_set_turns    = 5;
	}else if( FEED_PROGRAM_3 ==  p->feedInfo.feed_program ){
				p->dev.stt.motor_set_turns    = 85;	  
	}
}


void td_main_deal(TD_MAIN *p)
{ 
	p->tick++;
    
	chkDeadThread(p);

	//��ι�߼�
	doFeed(p);

	//�����߼�
	doKey(p);
	
	//�����߼�
	doPigIn(p);
}

void chkDeadThread(TD_MAIN *p)
{
	rt_uint8_t rstFlg = RT_FALSE;
	
	//feed dog
	IWDG->KR=0XAAAA;
	
	if( (p->tick%200)!=0 ){ //20s
		return;
	}
	
#ifdef _THREAD_NET_RECV
	if( p->dev.wdg.tick_netRecv != _td_netRecv.tick ){
		p->dev.wdg.tick_netRecv = _td_netRecv.tick;
	}else{
		rstFlg = RT_TRUE;
		rt_kprintf("[MAIN_TASK]: rst thread _td_netRecv...");
	}
#endif
#ifdef _THREAD_NET_TASK
	if( p->dev.wdg.tick_netTask != _td_netTask.tick ){
		p->dev.wdg.tick_netTask = _td_netTask.tick;
	}else{
		rstFlg = RT_TRUE;
		rt_kprintf("[MAIN_TASK]: rst thread _td_netTask...");
	}
#endif
	
	if( RT_TRUE == rstFlg ){
		p->tick = 50;
//		save_param(p);
		rt_kprintf("[MAIN_TASK]: thread dead, mcu restarting !!!!!!");
		rstMcu(); 
	}
}

void rstMcu()
{
	*((u32 *)0xE000ED0C) = 0x05fa0004;
}



void doPigIn(TD_MAIN *p)
{
	if( CHK_PIG_IN ){
		rt_kprintf("��⵽����?...\r\n");
//		p->dev.stt.motor_count = 0x00;
	}
}


void keyproc(TD_MAIN *p);

void doKey(TD_MAIN *p)
{
  if(p->Key_Strut.KeyPressFlag == 1){
	  p->Key_Strut.KeyPressFlag  = 0;
	  keyproc(p);
  }
#if 0
	//sw1
	if( SW1_STT_ON ){
		rt_thread_mdelay(50);
		if( SW1_STT_ON ){
			SW1_LED_ON;
			SW2_LED_OFF;
			SW3_LED_OFF;
			SW4_LED_OFF;
//			p->dev.stt.motor_turns = 1;
			
			if( FEED_PROGRAM_1 == p->feedInfo.feed_program ){
				p->dev.stt.motor_set_turns    = 32;
				p->feedInfo.feed_time_min = 14*60+30;  //�����趨ʱ�� 6:30
			}else if( FEED_PROGRAM_2 ==  p->feedInfo.feed_program ){
					  p->dev.stt.motor_set_turns    = 5;
					  p->feedInfo.feed_time_min = 14*60+30;  //�����趨ʱ�� 7:00	
			}else if( FEED_PROGRAM_3 ==  p->feedInfo.feed_program ){
					  
			}
		}					
	}else if( SW2_STT_ON ){
		rt_thread_mdelay(50);
		if( SW2_STT_ON ){
			SW1_LED_OFF;
			SW2_LED_ON;
			SW3_LED_OFF;
			SW4_LED_OFF;
			p->dev.stt.motor_set_turns++; 
			rt_kprintf("��ť��SW2_LED_ON\r\n");
		}
	}else if( SW3_STT_ON ){
		rt_thread_mdelay(50);
		if( SW3_STT_ON ){
			SW1_LED_OFF;
			SW2_LED_OFF;
			SW3_LED_ON;
			SW4_LED_OFF;
			p->dev.stt.motor_set_turns--; 
			rt_kprintf("��ť��SW3_LED_ON\r\n");
		}
	}else if( SW4_STT_ON ){
		rt_thread_mdelay(50);
		if( SW4_STT_ON ){
			SW1_LED_OFF;
			SW2_LED_OFF;
			SW3_LED_OFF;
			if(p->dev.stt.water_pump_flag == 0){  //�򿪵�ŷ������?
				p->dev.stt.water_pump_flag = 1;
				WATER_PUMP_ON;
				SW4_LED_ON;
			}else{								  //�رյ�ŷ���?
					p->dev.stt.water_pump_flag = 0;
					WATER_PUMP_OFF;
					SW4_LED_OFF;
			}
			rt_kprintf("��ť��SW4_LED_ON\r\n");
		}
	}
#endif        
}

void doFeed(TD_MAIN *p)
{
	if(p->dev.stt.key_set_motor_flag == 1){
		if(p->dev.stt.motor_count >= MOTOR_ONE_CIRCLE*1){
			MOTOR_OFF;
			SW1_LED_OFF;
			p->dev.stt.motor_count = 0;
			p->dev.stt.key_set_motor_flag = 0;
		}else{
				MOTOR_ON;
				SW1_LED_ON;
		}
	}
	if( FEED_PROGRAM_3 == p->feedInfo.feed_program ){
		//�����ᡢ�����ᡢ���ᣨ����?�����?
		doFeed_program_3(p);
	}else if( FEED_PROGRAM_2 == p->feedInfo.feed_program ){
		//������
		doFeed_program_2(p);
	}else if( FEED_PROGRAM_1 == p->feedInfo.feed_program ){
		//�仳�ᶨλ����������λ��
		doFeed_program_1(p);
	}
}

//�����ᡢ�����ᡢ���ᣨ����?�����?
//ιҩ�߼�Ϊ���ļ���7-12 | 15-20  ->ˮ+��; ����ʱ��ֻ��ˮ
//			 ������7-12 | 15-19  ->ˮ+��?�����ʱ��ֻ���?
//ʳ���б���2CM��ˮλ��ÿͷ��?���?1500~3000g���������ת��һȦ��Ͷ��?50g  
void doFeed_program_3(TD_MAIN *p)
{ 
	static rt_uint8_t doType = 0x00; 

	if(p->feedInfo.feed_season == 0x00){ //�ļ�ι
		if(p->feedInfo.feed_time_min == 7*60 && p->feedInfo.feed_time_second == 0){
			doType = EAT_TYPE_FEED_ONLY;
			p->dev.stt.motor_turns = p->dev.stt.motor_set_turns + 30;
		}else if(p->feedInfo.feed_time_min == 10*60 && p->feedInfo.feed_time_second == 0){
					doType = EAT_TYPE_FEED_ONLY;
					p->dev.stt.motor_turns = p->dev.stt.motor_set_turns - 50;
		}else if(p->feedInfo.feed_time_min == 12*60 && p->feedInfo.feed_time_second == 0){
					doType = EAT_TYPE_FEED_ONLY;
					p->dev.stt.motor_turns = p->dev.stt.motor_set_turns - 50;
		}else if(p->feedInfo.feed_time_min == 14*60+30 && p->feedInfo.feed_time_second == 0){
					doType = EAT_TYPE_FEED_ONLY;
					p->dev.stt.motor_turns = p->dev.stt.motor_set_turns - 50;
		}else if(p->feedInfo.feed_time_min == 16*60+30 && p->feedInfo.feed_time_second == 0){
					doType = EAT_TYPE_FEED_ONLY;
					p->dev.stt.motor_turns = p->dev.stt.motor_set_turns -30;
		}else if(p->feedInfo.feed_time_min == 19*60 && p->feedInfo.feed_time_second == 0){
					doType = EAT_TYPE_FEED_ONLY;
					p->dev.stt.motor_turns = p->dev.stt.motor_set_turns + 50;
		}
				
	}else if(p->feedInfo.feed_season == 0x00){

	}
	if( doType == EAT_TYPE_FEED_ONLY){
		if(p->dev.stt.motor_count >= MOTOR_ONE_CIRCLE*p->dev.stt.motor_turns){
			MOTOR_OFF;
			doType = 0;
			p->dev.stt.motor_count = 0;
			p->dev.stt.motor_turns = 0;
			p->dev.stt.motor_flag = 0;
		}else{
				MOTOR_ON;
				p->dev.stt.motor_flag = 1;
		}
        }
	
}

//������ 
//�iÿ�δ���������?5?���?30�����ʱ��?
//ÿ���ߵ㣬����?5??
//ˮλ����2CM��ˮ�϶�����
//��������~�ĵ㲻����
void doFeed_program_2(TD_MAIN *p)
{
	static rt_uint8_t doType = 0x00; 

	if( p->feedInfo.feed_time_min == 7*60  && p->feedInfo.feed_time_second == 0){ //ÿ�������ߵ�����?��?5??
	    p->dev.stt.motor_turns = p->dev.stt.motor_set_turns;
		doType = EAT_TYPE_FEED_ONLY;
	}

	if( doType != EAT_TYPE_FEED_ONLY && CHK_PIG_IN && p->feedInfo.feed_each_time == 0){//��������?�����?
//		if( p->feedInfo.feed_time_min >= 14*60 && p->feedInfo.feed_time_min <= 16*60) return;
		if( p->dev.stt.motor_total_count >= 75*MOTOR_ONE_CIRCLE)  return;
	    p->dev.stt.motor_turns = p->dev.stt.motor_set_turns;
		doType = EAT_TYPE_FEED_ONLY;
		p->feedInfo.feed_each_time = FEED_CHK_INTERVAL_30S;
	}

	if( doType == EAT_TYPE_FEED_ONLY){
		if(p->dev.stt.motor_count >= MOTOR_ONE_CIRCLE*p->dev.stt.motor_turns){
			MOTOR_OFF;
			doType = 0;
			p->dev.stt.motor_count = 0;
			p->dev.stt.motor_turns = 0;
			p->dev.stt.motor_flag = 0;
		}else{
				MOTOR_ON;
				p->dev.stt.motor_flag = 1;
		}
	}
	// if( FEED_WATER_STOP > p->dev.stt.WATER_ADC_ConvertedValue ){//ˮλ�ﵽ��
	// 	MOTOR_OFF;
	// 	WATER_PUMP_OFF;
	// 	_td_main.dev.stt.motor_count = 0x00;
	// }
	// else{
	// 		WATER_PUMP_ON;
	// }
}


//����ʱ����ˮ������?��?ˮ�������Ϻ�30min��ˮ��ʳ���б���1CMˮλ��
//�仳��A,B���ַ���
//����a���ļ�7~17����  ����7~16����            2.8kg 0.2
//����b������90��?���ÿ��ιһ�Σ�?7��30��ʼ      ���ݱ��ж�
//	    ����90����ļ�?7~17 ����?�����? 7~16 ����
//ÿ��һ����Ҫת60?����ļ�ʮ��Сʱ������?9��Сʱ
void doFeed_program_1(TD_MAIN *p)
{
	static rt_uint8_t doType = 0x00;
	if(p->feedInfo.feed_season == 0x00){ //�ļ�
		if(p->feedInfo.feed_time_min == 7*60 && p->feedInfo.feed_time_second == 0 ){  //����뿪ʼ�?
			doType = EAT_TYPE_FEED_ONLY;
			p->dev.stt.motor_turns = p->dev.stt.motor_set_turns;
		}else if(p->feedInfo.feed_time_min == 14*60 + 30 && p->feedInfo.feed_time_second == 0){
			doType = EAT_TYPE_FEED_ONLY;
			p->dev.stt.motor_turns = p->dev.stt.motor_set_turns;
		}
	}else if(p->feedInfo.feed_season == 0x01){ //����
			  if(p->feedInfo.feed_time_min >= 7*60 && p->feedInfo.feed_time_min <= 16*60){
				  doType = EAT_TYPE_FEED_ONLY;
				  p->feedInfo.feed_time_interval = FEED_CHK_INTERVAL_30MIN;
			}
	}
	if(doType == EAT_TYPE_FEED_ONLY){
		if( p->dev.stt.motor_count >= MOTOR_ONE_CIRCLE*p->dev.stt.motor_turns){
			MOTOR_OFF;
			p->dev.stt.motor_count = 0;
			p->dev.stt.motor_turns = 0;
			doType = 0;
			p->dev.stt.motor_flag = 0;
		}else{
				MOTOR_ON;
				p->dev.stt.motor_flag = 1;
		}
	}
}



#ifdef RT_USING_FINSH
#include <finsh.h>
void clr_param()
{
	rt_uint8_t fwrBuf[8] = {0x00};
	rt_uint8_t i = 0x00;
	
	for(i=0;i<_td_main.dev.stt.socketSum;i++){
		//order id
		devFlash.write(&devFlash, FRAM_ADDR_ORDER_ID+i*6, fwrBuf, 6);
        memset(_td_main.dev.stt.orderId[i], 0x00, sizeof(_td_main.dev.stt.orderId[i]));
		//socket stt
		devFlash.write(&devFlash, FRAM_ADDR_SOCKET_STT+i, fwrBuf, 1);
        _td_main.dev.stt.socketStt[i] = 0x00;
		//charge type
		devFlash.write(&devFlash, FRAM_ADDR_CHARGE_TYPE+i, fwrBuf, 1);
        _td_main.dev.stt.chargeType[i] = 0x00;
		//add times
		devFlash.write(&devFlash, FRAM_ADDR_ADD_TIMES+i, fwrBuf, 1);
        _td_main.dev.stt.addTimes[i] = 0x00;
		//autoStopInfo
		devFlash.write(&devFlash, FRAM_ADDR_AUTO_STOP_INFO+i, fwrBuf, 1);
        _td_main.dev.stt.autoStopInfo[i] = 0x00;
		//run time
		devFlash.write(&devFlash, FRAM_ADDR_RUN_TIME+i*2, fwrBuf, 2);
        _td_main.dev.stt.runTime[i] = 0x00;
		//rest time
		devFlash.write(&devFlash, FRAM_ADDR_REST_TIME+i*2, fwrBuf, 2);
        _td_main.dev.stt.restTime[i] = 0x00;
		//run vol
		devFlash.write(&devFlash, FRAM_ADDR_RUN_VOL+i*2, fwrBuf, 2);
        _td_main.dev.stt.runVol[i] = 0x00;
		//rest vol
		devFlash.write(&devFlash, FRAM_ADDR_REST_VOL+i*2, fwrBuf, 2);
        _td_main.dev.stt.restVol[i] = 0x00;
		//run cash
		devFlash.write(&devFlash, FRAM_ADDR_RUN_CASH+i*2, fwrBuf, 2);
        _td_main.dev.stt.runCash[i] = 0x00;
		//rest cash
		devFlash.write(&devFlash, FRAM_ADDR_REST_CASH+i*2, fwrBuf, 2);
        _td_main.dev.stt.restCash[i] = 0x00;
		//avg w
		devFlash.write(&devFlash, FRAM_ADDR_AVG_W+i*2, fwrBuf, 2);
        _td_main.dev.stt.avgW[i] = 0x00;
		//max w
		devFlash.write(&devFlash, FRAM_ADDR_MAX_W+i*2, fwrBuf, 2);
        _td_main.dev.stt.maxW[i] = 0x00;
		//card id
		devFlash.write(&devFlash, FRAM_ADDR_CARD_ID+i*4, fwrBuf, 4);
		_td_main.dev.card.id[i]=0x00;
		//card type
		devFlash.write(&devFlash, FRAM_ADDR_CARD_TYPE+i, fwrBuf, 1);
        _td_main.dev.card.type[i]=0x00;
	}
	
	rt_kprintf(">>>>>> clr_param complete\r\n");
}
void reboot()
{
    rt_kprintf(">>>>>> reboot mcu\r\n");
    rstMcu();
}

//MSH_CMD_EXPORT(tst_stm32flash, tst w/r stm32 flash );
MSH_CMD_EXPORT(clr_param, clear flash memory );
MSH_CMD_EXPORT(reboot, reboot mcu );
#endif

