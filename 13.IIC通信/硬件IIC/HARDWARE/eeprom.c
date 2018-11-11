#include "eeprom.h"
#include "stm32f10x.h"
#include "delay.h"
#define TIME   time = TIMEOUT;
vu32 time;
//write a byte
void eeprom_write_byte(u16 addr, u8 byte)
{
	TIME
	I2C_GenerateSTART(I2C1,ENABLE);
	//ev5
	while(time&& I2C_CheckEvent( I2C1,I2C_EVENT_MASTER_MODE_SELECT) == RESET ) time--;
	//send iic addr
	I2C_Send7bitAddress(I2C1,0XA0,I2C_Direction_Transmitter);
	TIME
	//ev6
	while(time&&( I2C_CheckEvent( I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == RESET)) time--;
	//send eeprom addr
	I2C_SendData(I2C1,addr);
	TIME
	//ev8
	while(time&&( I2C_CheckEvent( I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) == RESET)) time--;
	
	I2C_SendData(I2C1,byte);
	TIME
	//ev8
	while(time&&( I2C_CheckEvent( I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) == RESET)) time--;
	//stop
	I2C_GenerateSTOP(I2C1,ENABLE);
	
}
//read a byte 
void eeprom_read_str(u16 addr, u8 *byte, u16 number)
{ 
	//TIME
//	while(time&&(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY) == SET)) time--;
	   
	I2C_GenerateSTART(I2C1,ENABLE);
	TIME 
	//ev5 
	while(time&&( I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) == RESET )) time--;
	//send iic addr
	I2C_Send7bitAddress(I2C1,0XA0,I2C_Direction_Transmitter);
	TIME
	//ev6
	while(time&&( I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == RESET )) time--;
	
	I2C_Cmd(I2C1, ENABLE);
	//send eeprom addr
	I2C_SendData(I2C1,addr);
	TIME
	//ev8
	while(time&&( I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) == RESET )) time--;
	//restart
	I2C_GenerateSTART(I2C1,ENABLE);
	TIME
	//ev5 
	while(time&&( I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) == RESET )) time--;
	//send iic addr
	I2C_Send7bitAddress(I2C1,0XA0,I2C_Direction_Receiver);
	TIME
	//ev6
	while(time&&( I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == RESET )) time--;
	
	while(number)
	{
		if(number == 1)
		{
			//no ack
			I2C_AcknowledgeConfig(I2C1,DISABLE);
			//stop
			I2C_GenerateSTOP(I2C1,ENABLE);
		}
		TIME
		while(time&&( I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED) == RESET )) time--;
		//receive
		*byte = I2C_ReceiveData(I2C1);	
		byte++;
		number--;
	}	
}


void eeprom_write_page(u16 addr, u8 len, u8 * bufer)
{
	TIME
	while(time&& (I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY) == SET)) time--;
	
	//start
	I2C_GenerateSTART(I2C1,ENABLE);
	TIME 
	//ev5 
	while(time&&( I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) == RESET )) time--;
	//send iic addr
	I2C_Send7bitAddress(I2C1,0XA0,I2C_Direction_Transmitter);
	TIME
	//ev6
	while(time&&( I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == RESET )) time--;
	//send eeprom addr
	I2C_SendData(I2C1,addr);
	TIME
	//ev8
	while(time&&( I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) == RESET )) time--;
	
	while(len--)
	{
		I2C_SendData(I2C1,*bufer);
		bufer++;
		TIME
		//ev8
		while(time&&( I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) == RESET)) time--;
	}
	I2C_GenerateSTOP(I2C1,ENABLE);
	
}






void eeprom_wait()
{
	delay_ms(30);
}












