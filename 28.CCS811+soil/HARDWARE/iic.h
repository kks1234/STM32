#ifndef _IIC_H
#define _IIC_H
#include "stm32f10x.h"

/* ·½±ãÒÆÖ² */

#define   RCC_IIC_CLK              RCC_APB2Periph_GPIOC
#define   IIC_GPIO                 GPIOC
#define   IIC_GPIO_PIN_SDA         GPIO_Pin_0
#define   IIC_GPIO_PIN_SCL         GPIO_Pin_1







#define SCL_H         IIC_GPIO->BSRR = IIC_GPIO_PIN_SCL
#define SCL_L         IIC_GPIO->BRR  = IIC_GPIO_PIN_SCL
   
#define SDA_H         IIC_GPIO->BSRR = IIC_GPIO_PIN_SDA
#define SDA_L         IIC_GPIO->BRR  = IIC_GPIO_PIN_SDA

#define SCL_read      GPIO_ReadInputDataBit(IIC_GPIO,IIC_GPIO_PIN_SCL)
#define SDA_read      GPIO_ReadInputDataBit(IIC_GPIO,IIC_GPIO_PIN_SDA)





void I2C_GPIO_Config(void);
u8 I2C_Start(void);
void I2C_Stop(void);
void I2C_SendACK(u8 i);
u8 I2C_WaitAck(void);
void I2C_SendByte(u8 dat);
u8 I2C_RecvByte(void);

#endif
