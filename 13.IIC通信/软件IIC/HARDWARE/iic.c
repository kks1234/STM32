#include "iic.h"
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "stdio.h"




void iic_delay()
{
	u8 i;
	for(i=0;i<10;i++); 
}

// i2c init
void iic_init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitTypeStruct);
	/* 给一个停止信号, 复位I2C总线上的所有设备到待机模式 */
	iic_stop();
}

//起始信号
void iic_start()
{
	SCL_1
	SDA_1
	iic_delay();
	SDA_0
	iic_delay();
	SCL_0
	iic_delay();
}

//结束信号
void iic_stop()
{
	SDA_0
	SCL_1
	iic_delay();
	SDA_1
}

//应答信号
void iic_ack()
{
	SDA_0
	iic_delay();
	SCL_1
	iic_delay();
	SCL_0
	iic_delay();
	SDA_1
}

//非应答信号
void iic_nack()
{
	SDA_1
	iic_delay();
	SCL_1
	iic_delay();
	SCL_0
	iic_delay();
}


//  send a byte
void iic_send_byte(u8 byte)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		if(byte&0x80)
			SDA_1
		else
			SDA_0
		iic_delay();
		SCL_1
		iic_delay();
		SCL_0
		if(i==7)  //释放总线
			SDA_1
		byte<<=1;
		iic_delay();
	}
}

//receive a byte
u8 iic_receive_byte()
{
	u8 temp=0,i;

	for(i=0;i<8;i++)
	{
		temp<<=1;
		SCL_1
		iic_delay();
		if(SDA_READ)
			temp++;
		SCL_0
		iic_delay();
	}
	return temp;
}
// 0 ack  1 nack
u8   iic_waitack(void)
{
	u8 t;
	SDA_1  //cpu释放sda总线
	//iic_delay();
	SCL_1
	iic_delay();
	if(SDA_READ)
		t=1;
	else
		t=0;
	SCL_0
	iic_delay();
	return t;
		
}

/************AT24C02************/

void eeprom_write_onebyte(u16 addr, u8 byte)
{
	iic_start();
	iic_send_byte(0XA0);
	
	if(iic_waitack() == 1)
		iic_stop();
	iic_send_byte((u8)addr);
	
	if(iic_waitack() == 1)
		iic_stop();
	iic_send_byte(byte);
	
	if(iic_waitack() == 1)
		iic_stop();
	iic_stop();
	delay_ms(10);
}

//读一个字节
u8 eeprom_read_onebyte(u16 addr)
{
	u8 temp;
	iic_start();
	iic_send_byte(0XA0);
	
	if(iic_waitack() == 1)
		iic_stop();
	iic_send_byte((u8)addr);
	
	if(iic_waitack() == 1)
		iic_stop();
	iic_start();
	iic_send_byte(0XA1);
	
	if(iic_waitack() == 1)
		iic_stop();
	temp = iic_receive_byte();

	iic_nack();	
	iic_stop();
	return temp;
}

//写入等待
void eeprom_wait(void)
{
	
}

/*******写入字符串********/
void eeprom_write_string(u16 addr, u8* byte, u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		eeprom_write_onebyte(addr+i, *byte);
		byte++;
	}
}

void eeprom_read_string(u16 addr, u8* buf, u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		*buf++ = eeprom_read_onebyte(addr++);
	}
}

/*****页写入有错***/
void eeprom_write_stringpage(u16 addr, u8* byte, u8 len)
{
	u8 i;
	iic_start();
	iic_send_byte(0XA0);
	if(iic_waitack() == 1)
		iic_stop();
	
	iic_send_byte(addr);
	if(iic_waitack() == 1)
		iic_stop();
	for(i=0; i<len ;i++)
	{	
		iic_send_byte(*byte++);
		if(iic_waitack() == 1)
			iic_stop();
	}
	iic_stop();
}


























