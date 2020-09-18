/*******************************************************************************
* FILE NAME:    hw_uart.h

* COPYRIGHT (C) 2013, wfzeng@foxmail.com
* Change Logs:
* Date         Author       Notes
* 20130515     wfzeng       First Version
*******************************************************************************/
#ifndef _DEF_HW_IAP_H_
#define _DEF_HW_IAP_H_


/*******************************************************************************
*    define & config
*******************************************************************************/
//void iap_write_data(u32* appxaddr,u8 *appbuf,u16 appsize);
void STMFLASH_Read_PrintfToPc(u32 ReadAddr,u16 NumToRead) ;
void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 appsize);
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);

#endif
/******************************** end of file *********************************/


