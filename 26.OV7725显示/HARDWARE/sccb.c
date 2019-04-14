#include "sccb.h"
#include "delay.h"

void sccb_init()
{
//	GPIO_InitTypeDef GPIO_InitTypeStruct;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG,ENABLE);
//	
//	//OV SCL
//	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_3;
//	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOD, &GPIO_InitTypeStruct);
//	GPIO_SetBits(GPIOD,GPIO_Pin_3);
//	//OV SDA
//	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_13;
//	GPIO_Init(GPIOG, &GPIO_InitTypeStruct);
//	GPIO_SetBits(GPIOG,GPIO_Pin_13);	
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG, ENABLE);	 //使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 // 端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //输入
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOG,GPIO_Pin_13);						 // 输出高

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 // 端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //输输出
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOD,GPIO_Pin_3);						 // 输出高
 
	SDA_OUT();	 
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
	SCCB_SCL_L;
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
	u8 res;
	SDA_IN();		//设置SDA为输入 
	delay_us(50);
	SCCB_SCL_H;		//接收第九位,以判断是否发送成功
	delay_us(50);
	if(SCCB_SDAIN)res=1;  //SDA=1发送失败，返回1
	else res=0;         //SDA=0发送成功，返回0
	SCCB_SCL_L;			 
	SDA_OUT();		//设置SDA为输出 
	return res;
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

	delay_us(50);	
	SCCB_SDA_H;SCCB_SCL_H;
	delay_us(50);
	SCCB_SCL_L;
	delay_us(50);
	SCCB_SDA_L;
	delay_us(50);
}


void sccb_write(u8 data)
{
	char i;
	u8 temp = data;
	for(i=0; i<8; i++)
	{
		if(temp & 0x80) SCCB_SDA_H;
		else SCCB_SDA_L;
		delay_us(50);
		SCCB_SCL_H;
		delay_us(50);
		temp <<= 1;
		SCCB_SCL_L;
	}
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
		if(SCCB_SDAIN)
			temp ++;
		delay_us(50);	
	}
	SDA_OUT();
	SCCB_SCL_L;
	return temp;
}


























