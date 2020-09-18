/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#ifndef __TD_MAIN_H__
#define __TD_MAIN_H__

#include <rtthread.h>
#include <stm32f10x.h>
#include "userCommon.h"

#include "key.h"
#include "actuator.h"
#include "motor.h"
#include "led.h"

#include "key.h"
#include "dev_flash.h"
#include "hw_iap.h"


#define MOTOR_ONE_CIRCLE		1300

#define FEED_PROGRAM_1		1//�仳�ᶨλ����������λ����1ͷ��1����
#define FEED_PROGRAM_2		2//������
#define FEED_PROGRAM_3		3//�����ᡢ�����ᡢ���ᣨ����Ⱥ����

#define EAT_TYPE_WATER_FEED		0x01
#define EAT_TYPE_WATER_ONLY		0x02
#define EAT_TYPE_FEED_ONLY		0x03

#define FEED_CHK_INTERVAL_30S		30
#define FEED_CHK_INTERVAL_30MIN		1800
#define FEED_WATER_STOP			2000//Bit_RESET//Bit_SET //Bit_RESET

/////////////////////////////////////////////////////////////////
#define APP_SOCKET_NUM		10
#define APP_RULE_CHARGE_MODE	APP_RULE_MODE_VOL
#define APP_RULE_MODE_TIME	0x01
#define APP_RULE_MODE_VOL	0x02

//stt define
#define APP_CHARGE_START	0x01
#define APP_CHARGE_STOP		0x00

#define APP_CHARGE_NULL				0x00
#define APP_CHARGE_QR				0x01
#define APP_CHARGE_CARD_ONLINE		0x02
#define APP_CHARGE_CARD_OFFLINE		0x04
#define APP_CHARGE_COIN				0x08

#define MAX_RECV_LORA_FRAME_LENGTH   64
#define RCC_APBxPeriph_485_IO	     RCC_APB2Periph_GPIOC
#define EN_485_PIN						 GPIO_Pin_5
#define EN_485_IO						 GPIOC

#define EN_485_RX				GPIO_ResetBits(EN_485_IO, EN_485_PIN)
#define EN_485_TX 				GPIO_SetBits(EN_485_IO, EN_485_PIN)


typedef struct
{
    rt_uint8_t key;
    rt_uint8_t KeyCnt;
    rt_uint8_t KeyState;
    rt_uint8_t KeyLast;
    rt_uint8_t KeyValue;
    rt_uint8_t KeyPressFlag;	//按键状态，上次按键值，当前按下的键号,按键按下标志
}KEY_Structure;

typedef struct
{
//	rt_bool_t reqFlg;	//request flg
	rt_bool_t stFlg;	//start flg
    rt_uint8_t ver;     //versiion
	rt_uint8_t area;	//request app area
	rt_uint32_t offset;	//request data offset
	rt_uint16_t reqLen;	//request data length
	rt_uint8_t stt; 	//0x01: continue, 0x02: finish, 0x03: err
    rt_uint8_t timeOut; //request data timeout
}APP_DEV_OTA;

typedef struct
{
	rt_uint32_t motor_count;
	rt_uint32_t motor_total_count;
	rt_uint8_t motor_turns; //Ȧ��
	rt_uint8_t motor_set_turns;
	rt_uint8_t water_pump_flag;
	rt_uint8_t motor_flag;
	rt_uint8_t key_set_motor_flag;
	rt_uint16_t WATER_ADC_ConvertedValue;
	// rt_uint8_t key1_flg;
	// rt_uint8_t key2_flg;
	// rt_uint8_t key3_flg;
	// rt_uint8_t key4_flg;
	
	rt_uint8_t socketSum;	
	rt_uint8_t orderId[APP_SOCKET_NUM][6];
	rt_uint8_t socketStt[APP_SOCKET_NUM];
	rt_uint8_t chargeType[APP_SOCKET_NUM];
	rt_uint8_t addTimes[APP_SOCKET_NUM];
	
	rt_uint8_t autoStopInfo[APP_SOCKET_NUM];
	
	float runTime[APP_SOCKET_NUM]; 	//time
	float restTime[APP_SOCKET_NUM];
	float runVol[APP_SOCKET_NUM];	//vol
	float restVol[APP_SOCKET_NUM];
	float runCash[APP_SOCKET_NUM];	//cash
	float restCash[APP_SOCKET_NUM];
	
	float currA[APP_SOCKET_NUM];
	float currV[APP_SOCKET_NUM];
	rt_uint16_t currW[APP_SOCKET_NUM];
	rt_uint16_t avgW[APP_SOCKET_NUM];
	rt_uint16_t maxW[APP_SOCKET_NUM];
    
    //�������
	rt_uint8_t pwKwhInitFlg;
    rt_uint32_t pwKwhRegBegin[APP_SOCKET_NUM];
    rt_uint32_t pwKwhRegNext[APP_SOCKET_NUM];
    rt_uint32_t pwKwhRegShiftBegin[APP_SOCKET_NUM];
    rt_uint32_t pwKwhRegCurr[APP_SOCKET_NUM];
}APP_DEV_STT;

typedef struct
{
	rt_uint8_t setFlg;
	
	rt_uint8_t fullPower;
	rt_uint8_t fullTime;
	rt_uint8_t minCalcUnit;
	rt_uint8_t chargeMode;
	rt_uint16_t prePayment;
	rt_uint16_t powerLev1;	
	rt_uint16_t powerLev2;	
	rt_uint16_t powerLev3;	
	rt_uint16_t powerLev4;
	rt_uint16_t paramLev1;
	rt_uint16_t paramLev2;
	rt_uint16_t paramLev3;
	rt_uint16_t paramLev4;
	rt_uint8_t plugTime;
}APP_DEV_RULE;

typedef struct
{
    rt_uint8_t priorityFlg[APP_SOCKET_NUM];
    rt_uint8_t priorityTimeout[APP_SOCKET_NUM];
    
	rt_uint8_t reqFlg[APP_SOCKET_NUM];   
	rt_uint8_t evenType[APP_SOCKET_NUM]; //0x00: stop, 0x01: start
    
    rt_uint8_t reqMoneyFlg; //�����
    rt_uint32_t reqMoneyid;
	
	rt_uint32_t id[APP_SOCKET_NUM];
	rt_uint8_t type[APP_SOCKET_NUM];	//0x01: online card, 0x02: offline card
    
    //show balance
    rt_uint8_t showMoneyFlg;
    rt_uint8_t showMoneyTime;
    rt_uint8_t voiceMoneyFlg;
	rt_uint32_t money;
}APP_CARD;

typedef struct
{
	rt_uint8_t reqFlg[APP_SOCKET_NUM];
	rt_uint8_t currNum[APP_SOCKET_NUM];
	rt_uint8_t totalNum[APP_SOCKET_NUM];
	rt_uint8_t evenType[APP_SOCKET_NUM]; //0x02: add, 0x01: start
}APP_COIN;

typedef struct
{
	rt_uint32_t tick_netRecv;
	rt_uint32_t tick_netTask;
	rt_uint32_t tick_pwTask;
	rt_uint32_t tick_rfid;
}APP_THREAD_WDG;

typedef struct{
    rt_uint8_t flg;
    rt_uint8_t time; //judge flg time
    rt_uint8_t showPwFlg;
    rt_uint8_t showPwIndex;
}APP_TST;

typedef struct
{
	APP_DEV_STT stt;
	APP_CARD card;
	APP_COIN coin;
	APP_DEV_RULE rule;
	APP_THREAD_WDG wdg;
	APP_DEV_OTA ota;
	APP_TST tst;
}APP_DEV_INFO;

typedef struct {
	/* data */
	rt_uint8_t feed_program;	//��ι����

	rt_uint8_t pigSum;     //��ͷ��
	rt_uint8_t feed_season;	//���ڣ������ģ�
	rt_uint16_t feed_time_second;  //��ʱ�����ӣ�
	rt_uint16_t feed_time_min;  //��ʱ�����ӣ�
	rt_uint16_t feed_time_interval; //ι��ʱ����(��)

	rt_uint8_t age_of_day; //��������
	rt_uint8_t age_of_all; //������
	rt_uint8_t feed_type;  //����Ʒ��
	rt_uint8_t feed_each_time; //����ιʳ(g)
	rt_uint8_t feed_gram_one_day; //��ι����(g)
	rt_uint8_t feed_times_one_day; //��ι����

	float target_weight; //Ŀ������ �����
	float daily_gain;	 //�������� ����/ͷ/�죩
	float total_consumption;  //�ۼƺ���(g)
	float feed_meat_ratio;	  //�����
}APP_FEED_INFO;


typedef struct
{
	rt_uint32_t  tick;

    rt_uint8_t rxPos;
    rt_uint16_t RxLen;//�������ݳ���
    rt_uint8_t RxBuf[ MAX_RECV_LORA_FRAME_LENGTH ];//�������ݻ�����
    
	APP_DEV_INFO dev;
	APP_FEED_INFO feedInfo;
    KEY_Structure Key_Strut;
	
	void (*init)();
	void (*deal)(); 
}TD_MAIN;

#define NEW_TD_MAIN  {0,\
    0,\
    0,\
    {0},\
	{0},\
	{0},\
        {0},\
    (void (*)(rt_uint32_t))td_main_init,\
    (void (*)(rt_uint32_t))td_main_deal\
}

extern TD_MAIN _td_main;

void td_main_init(TD_MAIN *p);
void td_main_deal(TD_MAIN *p);
void chkDeadThread(TD_MAIN *p);

void doFeed(TD_MAIN *p);
void doFeed_program_3(TD_MAIN *p);
void doFeed_program_2(TD_MAIN *p);
void doFeed_program_1(TD_MAIN *p);

void doKey(TD_MAIN *p);
void doPigIn(TD_MAIN *p);

void save_param(TD_MAIN *p);
void load_saveParam(TD_MAIN *p);
void rstMcu();
void clr_param();
#endif
