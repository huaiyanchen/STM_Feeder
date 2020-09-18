#include "fm24cl.h"
#include "i2c.h"

/* 初始化 */
void rt_hw_fm24cl_init()
{    
    I2C_GPIOInitConfig();
}

// 写N字节数据，startAddr 0 -- 0x1fff;
// 返回 1 读写正常， 返回 0 读写错误
u8 FM_WrData(uv16 startAddr,uv8 *buff,uv16 len)
{
 		u16 i;
		u8 temp, ret = 0;
	  if(I2C_CheckDevice(I2C_ADDRESS) != 0) {ret = 1; goto Write_END;}
		I2C_Start();
		I2C_SendByte(I2C_ADDRESS | I2C_WR);
	  if( I2C_RecvACK() != 0 ) {I2C_Stop(); ret = 1; goto Write_END;}
		
		temp = (startAddr & 0x1fff) >> 8;
		I2C_SendByte(temp);
		if( I2C_RecvACK() != 0 ) {I2C_Stop(); ret = 1; goto Write_END;}
		
		temp = startAddr & 0x00ff;
		I2C_SendByte(temp);
		if( I2C_RecvACK() != 0 ) {I2C_Stop(); ret = 1; goto Write_END;}		
		for(i=0; i<len; i++)
		{
				I2C_SendByte(buff[i]);
				if(I2C_RecvACK() != 0)
				{
						ret = 1;
						I2C_Stop();
					  goto Write_END;
				}			
		}
		I2C_Stop();
Write_END:		
		if(ret == 1)
        {
//            _log.dev.info.fm24cl_err_code|=(1<<FRAM_HARD_DEFAULT);
            ///rt_hw_us_delay(2000);
            return 0;
        }else{
            //rt_hw_us_delay(2000);
            return 1;	
        }
}


// 写N字节数据，startAddr 0 -- 0x1fff;
// 返回 1 读写正常， 返回 0 读写错误
u8 FM_RdData(uv16 startAddr,uv8 *buff,uv16 len)
{
        u16 i;
        u8 temp, ret = 0;
        
        u8 x = 0;
        u8 ilen = 1;
        
        for(x=0;x<len;x++){
            ret = 0;
            
          if(I2C_CheckDevice(I2C_ADDRESS) != 0) {ret = 1; goto Read_END;}
            I2C_Start();
            I2C_SendByte(I2C_ADDRESS | I2C_WR);
          if( I2C_RecvACK() != 0 ) {I2C_Stop(); ret = 1; goto Read_END;}
            temp = (startAddr+x & 0x1fff) >> 8;
            I2C_SendByte(temp);
            if( I2C_RecvACK() != 0 ) {I2C_Stop(); ret = 1; goto Read_END;}
            temp = startAddr+x & 0x00ff;
            I2C_SendByte(temp);
            if( I2C_RecvACK() != 0 ) {I2C_Stop(); ret = 1; goto Read_END;}
    
            I2C_Start();
            I2C_SendByte(I2C_ADDRESS | I2C_RD);
            if( I2C_RecvACK() != 0 ) {
                I2C_Stop(); ret = 1; goto Read_END;
            }		
            for(i=0; i<ilen; i++)
            {
                buff[x+i] = I2C_RecvByte();
                if(i < (ilen - 1))
                    I2C_SendACK(ACK);
                else 
                    I2C_SendACK(NO_ACK);		
                
    //            DelayXms(1);
            }
            I2C_Stop();
    Read_END:		
            if(ret == 1)
            {
//                _log.dev.info.fm24cl_err_code|=(1<<FRAM_HARD_DEFAULT);
                      continue; //return 0;
            }
            else 
                continue; //return 1;	
        }
        
        return 1;	
}

// 清零FRAM的一片区域, startAddr 0 -- 0x1fff;
u8 FM_ClearArea(u16 startAddr,u16 len)
{
 		u16 i;
		u8 temp, ret = 0;
	  if(I2C_CheckDevice(I2C_ADDRESS) != 0) {ret = 1; goto Write_END;}
		I2C_Start();
		I2C_SendByte(I2C_ADDRESS | I2C_WR);
	  if( I2C_RecvACK() != 0 ) {I2C_Stop(); ret = 1; goto Write_END;}
		
		temp = (startAddr & 0x1fff) >> 8;
		I2C_SendByte(temp);
		if( I2C_RecvACK() != 0 ) {I2C_Stop(); ret = 1; goto Write_END;}
		
		temp = startAddr & 0x00ff;
		I2C_SendByte(temp);
		if( I2C_RecvACK() != 0 ) {I2C_Stop(); ret = 1; goto Write_END;}		
		for(i=0; i<len; i++)
		{
				I2C_SendByte(0x00);
				if(I2C_RecvACK() != 0)
				{
						ret = 1;
						I2C_Stop();
					  goto Write_END;
				}			
		}
		I2C_Stop();
Write_END:		
		if(ret == 1)
    {
//        _log.dev.info.fm24cl_err_code|=(1<<FRAM_HARD_DEFAULT);
			  return 0;
		}
    else return 1;	
}
