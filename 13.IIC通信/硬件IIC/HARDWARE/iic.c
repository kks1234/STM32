#include "iic.h"
#include "stm32f10x.h"

void iic_init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	I2C_InitTypeDef I2C_InitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//PB6   SCL
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_AF_OD;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitTypeStruct);
	
	//PB7   SDA
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_AF_OD;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitTypeStruct);
	
	// I2C1 init
	I2C_InitTypeStruct.I2C_Ack=I2C_Ack_Enable;
	I2C_InitTypeStruct.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_InitTypeStruct.I2C_ClockSpeed=400000;
	I2C_InitTypeStruct.I2C_DutyCycle=I2C_DutyCycle_2;
	I2C_InitTypeStruct.I2C_Mode=I2C_Mode_I2C;
	I2C_InitTypeStruct.I2C_OwnAddress1=0x5f;
	I2C_Init(I2C1,&I2C_InitTypeStruct);
	
	//I2C1 cmd
	I2C_Cmd(I2C1,ENABLE);
	
}






