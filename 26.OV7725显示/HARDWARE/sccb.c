#include "sccb.h"
#include "delay.h"

void sccb_init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG,ENABLE);
	
	//OV SCL
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitTypeStruct);
	
	//OV SDA
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOG, &GPIO_InitTypeStruct);
	
}



void sccb_start()
{
	SCCB_SDA_H;
	SCCB_SCL_H;
	delay_us(50);
	if(!SCCB_SDAIN)
		return;
	SCCB_SDA_L;
	if(SCCB_SDAIN)
		return;
	SCCB_SDA_L;
	delay_us(50);
}


void sccb_stop()
{
	SCCB_SDA_L;
	delay_us(50);
	SCCB_SCL_H;
	delay_us(50);
	SCCB_SDA_H;
	delay_us(50);
}


//0 无应答 1有应答
u8 wait_ack()
{
	SDA_IN();
	SCCB_SCL_L;
	delay_us(50);
	SCCB_SDA_H;
	delay_us(50);
	SCCB_SCL_H;
	delay_us(50);
	if(SCCB_SDAIN)
	{
		SCCB_SCL_L;
		return DISABLE;
	}	
	SCCB_SCL_L;
	SDA_OUT();
	return ENABLE;
}


void sccb_ack()
{
	SCCB_SCL_L;
	delay_us(50);
	SCCB_SDA_L;
	delay_us(50);
	SCCB_SCL_H;
	delay_us(50);
	SCCB_SCL_L;
	delay_us(50);
	
}


void sccb_nack()
{
	SCCB_SCL_L;
	delay_us(50);
	SCCB_SDA_H;
	delay_us(50);
	SCCB_SCL_H;
	delay_us(50);
	SCCB_SCL_L;
	delay_us(50);
}


void sccb_write(u8 data)
{
	char i;
	u8 temp = data;
	for(i=0; i<8; i++)
	{
		SCCB_SCL_L;
		delay_us(50);
		if(temp & 0x80)
			SCCB_SDA_H;
		else
			SCCB_SDA_L;
		delay_us(50);
		SCCB_SCL_H;
		delay_us(50);
		temp <<= 1;
		if(i == 7)
			SCCB_SDA_H;
	}
	SCCB_SCL_L;
}


u8 sccb_read()
{
	u8 temp = 0,i;
	SDA_IN();
	for(i=0; i<8; i++)
	{
		temp <<= 1;
		SCCB_SCL_L;
		delay_us(50);
		SCCB_SCL_H;
		delay_us(50);
		if(SCCB_SDAIN)
			temp ++;
	}
	SCCB_SCL_L;
	return temp;
}


























