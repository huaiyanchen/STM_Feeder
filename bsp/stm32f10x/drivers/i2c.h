#ifndef _I2C_H_
#define _I2C_H_

#include <stm32f10x.h>
extern void Delay500ns(void);

#define I2C_WR	       0		  /* 写控制bit  */
#define I2C_RD	       1		  /* 读控制bit  */
#define I2C_ADDRESS    0xA0   /* 从设备地址 */
#define ACK            0
#define NO_ACK         1

/********************* delay time configuration ************************/
#define I2C_Delay()    Delay500ns()

/********************* hardware configuration **************************/
#define GPIO_PORT_I2C	GPIOB			              /* GPIO端口 */
#define RCC_I2C_PORT 	RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define I2C_SCL_PIN		GPIO_Pin_3			        /* 连接到SCL时钟线的GPIO */
#define I2C_SDA_PIN		GPIO_Pin_5		        /* 连接到SDA数据线的GPIO */
/*******************end hardware configuration**************************/

#if 0	/* 条件编译： 1 选择GPIO的库函数实现IO读写 */
	#define I2C_SCL_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SCL_PIN)		  /* SCL = 1 */
	#define I2C_SCL_0()  GPIO_ResetBits(GPIO_PORT_I2C, I2C_SCL_PIN)		/* SCL = 0 */
	
	#define I2C_SDA_1()  GPIO_SetBits(GPIO_PORT_I2C, I2C_SDA_PIN)		  /* SDA = 1 */
	#define I2C_SDA_0()  GPIO_ResetBits(GPIO_PORT_I2C, I2C_SDA_PIN)		/* SDA = 0 */
	
	#define I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SDA_PIN)	/* 读SDA口线状态 */
#else	/* 这个分支选择直接寄存器操作实现IO读写 */
    /*　注意：如下写法，在IAR最高级别优化时，会被编译器错误优化 */
	#define I2C_SCL_1()  GPIO_PORT_I2C->BSRR = I2C_SCL_PIN				    /* SCL = 1 */
	#define I2C_SCL_0()  GPIO_PORT_I2C->BRR = I2C_SCL_PIN				      /* SCL = 0 */
	
	#define I2C_SDA_1()  GPIO_PORT_I2C->BSRR = I2C_SDA_PIN				    /* SDA = 1 */
	#define I2C_SDA_0()  GPIO_PORT_I2C->BRR = I2C_SDA_PIN				      /* SDA = 0 */
	
	#define I2C_SDA_READ()    ((GPIO_PORT_I2C->IDR & I2C_SDA_PIN) != 0)	/* 读SDA口线状态 */
#endif

void I2C_GPIOInitConfig(void);
void SDA_OUT(void);
void SDA_IN(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendACK(u8 ack);
u8 I2C_RecvACK(void);
void I2C_SendByte(u8 dat);
u8 I2C_RecvByte(void);
u8 I2C_CheckDevice(uint8_t _Address);

#endif
