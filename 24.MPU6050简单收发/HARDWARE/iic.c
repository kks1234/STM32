#include "iic.h"





void IIC_Gpio_Config_Init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitTypeStruct);
	
	iic1_stop();
	iic2_stop();
	iic3_stop();
	iic4_stop();
	
}

void IIC_Delay(void)
{
	u8 i;
	for(i=0; i<10; i++);
}

/************************* IIC 1 ***************************************/
void iic1_start(void)
{
	SDA1_1;
	SCL1_1;
	IIC_Delay();
	if(R_SDA1 == 0) return ;
	SDA1_0;
	if(R_SDA1 == 1) return ;
	IIC_Delay();
	SCL1_0; 
}

void iic1_stop(void)
{
	SDA1_0;
	SCL1_1;
	IIC_Delay();
	SDA1_1;
}

void iic1_ack(void)
{
	SDA1_0;
	IIC_Delay();
	SCL1_1;
	IIC_Delay();
	SCL1_0;
	IIC_Delay();
	SDA1_1;
}

void iic1_nack(void)
{
	SDA1_1;
	IIC_Delay();
	SCL1_1;
	IIC_Delay();
	SCL1_0;
	IIC_Delay();
}

u8 iic1_wait_ack(void)
{
	u8 flag;
	SDA1_1;
	SCL1_1;
	IIC_Delay();
	if(R_SDA1 == 0)
		flag = 1;
	else 
		flag = 0;
	SCL1_0;
	IIC_Delay();
	return flag;
}

void iic1_write_byte(u8 byte)
{
	u8 i;
	for(i=0; i<8; i++)
	{
		if(byte&0x80)
		{
			SDA1_1;
		}
		else
		{
			SDA1_0;
		}
		IIC_Delay();
		
		SCL1_1;
		IIC_Delay();
		SCL1_0;
		IIC_Delay();
		byte <<= 1;
		if(i == 7)
			SDA1_1;
	}	
}

u8 iic1_read_byte(u8 ack)
{
	u8 i,temp = 0;
	
	for(i=0; i<8; i++)
	{
		temp <<= 1;
		SCL1_1;
		IIC_Delay();
		if(R_SDA1)
			temp ++;
		SCL1_0;
		IIC_Delay();
	}
	if(ack == 1)
		iic1_ack();
	else
		iic1_nack();
	return temp;
}


/************************* IIC 2 ***************************************/


void iic2_start(void)
{
	SDA2_1;
	SCL2_1;
	IIC_Delay();
	if(R_SDA2 == 0) return ;
	SDA2_0;
	if(R_SDA2 == 1) return ;
	IIC_Delay();
	SCL2_0; 
}

void iic2_stop(void)
{
	SDA2_0;
	SCL2_1;
	IIC_Delay();
	SDA2_1;
}

void iic2_ack(void)
{
	SDA2_0;
	IIC_Delay();
	SCL2_1;
	IIC_Delay();
	SCL2_0;
	IIC_Delay();
	SDA2_1;
}

void iic2_nack(void)
{
	SDA2_1;
	IIC_Delay();
	SCL2_1;
	IIC_Delay();
	SCL2_0;
	IIC_Delay();
}

u8 iic2_wait_ack(void)
{
	u8 flag;
	SDA2_1;
	SCL2_1;
	IIC_Delay();
	if(R_SDA2 == 0)
		flag = 1;
	else 
		flag = 0;
	SCL2_0;
	IIC_Delay();
	return flag;
}

void iic2_write_byte(u8 byte)
{
	u8 i;
	for(i=0; i<8; i++)
	{
		if(byte&0x80)
		{
			SDA2_1;
		}
		else
		{
			SDA2_0;
		}
		IIC_Delay();
		
		SCL2_1;
		IIC_Delay();
		SCL2_0;
		IIC_Delay();
		byte <<= 1;
		if(i == 7)
			SDA2_1;
	}	
}

u8 iic2_read_byte(u8 ack)
{
	u8 i,temp = 0;
	
	for(i=0; i<8; i++)
	{
		temp <<= 1;
		SCL2_1;
		IIC_Delay();
		if(R_SDA2)
			temp ++;
		SCL2_0;
		IIC_Delay();
	}
	if(ack == 1)
		iic2_ack();
	else
		iic2_nack();
	return temp;
}







/************************* IIC 3 ***************************************/



void iic3_start(void)
{
	SDA3_1;
	SCL3_1;
	IIC_Delay();
	if(R_SDA3 == 0) return ;
	SDA3_0;
	if(R_SDA3 == 1) return ;
	IIC_Delay();
	SCL3_0; 
}

void iic3_stop(void)
{
	SDA3_0;
	SCL3_1;
	IIC_Delay();
	SDA3_1;
}

void iic3_ack(void)
{
	SDA3_0;
	IIC_Delay();
	SCL3_1;
	IIC_Delay();
	SCL3_0;
	IIC_Delay();
	SDA3_1;
}

void iic3_nack(void)
{
	SDA3_1;
	IIC_Delay();
	SCL3_1;
	IIC_Delay();
	SCL3_0;
	IIC_Delay();
}

u8 iic3_wait_ack(void)
{
	u8 flag;
	SDA3_1;
	SCL3_1;
	IIC_Delay();
	if(R_SDA3 == 0)
		flag = 1;
	else 
		flag = 0;
	SCL3_0;
	IIC_Delay();
	return flag;
}

void iic3_write_byte(u8 byte)
{
	u8 i;
	for(i=0; i<8; i++)
	{
		if(byte&0x80)
		{
			SDA3_1;
		}
		else
		{
			SDA3_0;
		}
		IIC_Delay();
		
		SCL3_1;
		IIC_Delay();
		SCL3_0;
		IIC_Delay();
		byte <<= 1;
		if(i == 7)
			SDA3_1;
	}	
}

u8 iic3_read_byte(u8 ack)
{
	u8 i,temp = 0;
	
	for(i=0; i<8; i++)
	{
		temp <<= 1;
		SCL3_1;
		IIC_Delay();
		if(R_SDA3)
			temp ++;
		SCL3_0;
		IIC_Delay();
	}
	if(ack == 1)
		iic3_ack();
	else
		iic3_nack();
	return temp;
}







/************************* IIC 4 ***************************************/




void iic4_start(void)
{
	SDA4_1;
	SCL4_1;
	IIC_Delay();
	if(R_SDA4 == 0) return ;
	SDA4_0;
	if(R_SDA4 == 1) return ;
	IIC_Delay();
	SCL4_0; 
}

void iic4_stop(void)
{
	SDA4_0;
	SCL4_1;
	IIC_Delay();
	SDA4_1;
}

void iic4_ack(void)
{
	SDA4_0;
	IIC_Delay();
	SCL4_1;
	IIC_Delay();
	SCL4_0;
	IIC_Delay();
	SDA4_1;
}

void iic4_nack(void)
{
	SDA4_1;
	IIC_Delay();
	SCL4_1;
	IIC_Delay();
	SCL4_0;
	IIC_Delay();
}

u8 iic4_wait_ack(void)
{
	u8 flag;
	SDA4_1;
	SCL4_1;
	IIC_Delay();
	if(R_SDA4 == 0)
		flag = 1;
	else 
		flag = 0;
	SCL4_0;
	IIC_Delay();
	return flag;
}

void iic4_write_byte(u8 byte)
{
	u8 i;
	for(i=0; i<8; i++)
	{
		if(byte&0x80)
		{
			SDA4_1;
		}
		else
		{
			SDA4_0;
		}
		IIC_Delay();
		
		SCL4_1;
		IIC_Delay();
		SCL4_0;
		IIC_Delay();
		byte <<= 1;
		if(i == 7)
			SDA4_1;
	}	
}

u8 iic4_read_byte(u8 ack)
{
	u8 i,temp = 0;
	
	for(i=0; i<8; i++)
	{
		temp <<= 1;
		SCL4_1;
		IIC_Delay();
		if(R_SDA4)
			temp ++;
		SCL4_0;
		IIC_Delay();
	}
	if(ack == 1)
		iic4_ack();
	else
		iic4_nack();
	return temp;
}










