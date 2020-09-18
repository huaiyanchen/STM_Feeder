#include "dev_flash.h"

/* flash init */
rt_uint8_t dev_flash_init()
{
    rt_hw_fm24cl_init();

    return 1;
}

rt_uint8_t dev_flash_read(IOT_DEVICE_FLASH *p, rt_uint16_t addr, rt_uint8_t *buf, rt_uint8_t len)
{
    rt_uint8_t res = 0;
	static rt_uint8_t mFlashRdLock = 0;

	while( mFlashRdLock );
	
	mFlashRdLock = 1;
    if( 1 == FM_RdData(addr, buf, len) ){
        res = 1;
    }
	mFlashRdLock = 0;
    
    return res;
}

rt_uint8_t dev_flash_write(IOT_DEVICE_FLASH *p, rt_uint16_t addr, rt_uint8_t *buf, rt_uint8_t len)
{
    rt_uint8_t res = 0;
    rt_uint8_t i = 0x00;
    rt_uint8_t mbuf[64] = {0x00};
	static rt_uint8_t mFlashWrLock = 0;

	while(mFlashWrLock);
	
	mFlashWrLock = 1;
    if( 1 == FM_WrData(addr, buf, len) ){
        if( 1 == FM_RdData(addr, mbuf, len) ){
            for(i=0;i<len;i++){
                if(mbuf[i]!=buf[i]){
                    break;
                }
            }
            
            if(i>=len){
                res = 1;
            }
        }
    }
	mFlashWrLock = 0;

    return res;
}
