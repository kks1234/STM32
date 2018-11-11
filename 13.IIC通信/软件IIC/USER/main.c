#include "stm32f10x.h"
#include "iic.h"
#include "delay.h"
#include "usart.h"


u8 temp,i;
u8 sendbuf[256];
u8 recebuf[256];


int main()
{
	delay_init();
	uart_init(115200);
	iic_init();
	
	
	
/*	eeprom_write_onebyte(45,3);
	delay_ms(10);
	temp = eeprom_read_onebyte(45);
	printf("%d  ",temp);
	*/
	
	for(i=0;i<255;i++)
		sendbuf[i] = i;
	
	for(i=0;i<255;i++)
		printf("%d ",sendbuf[i]);
	
	printf("\r\n");
	
	eeprom_write_string(0,sendbuf,255);
//	eeprom_write_stringpage(0, sendbuf, 255);   /*Ò³Ð´Èë£¬ÓÐ´íÎó*/
	
	eeprom_read_string(0,recebuf, 255);
	
	for(i=0;i<255;i++)
		printf("%d ",recebuf[i]);
	
	while(1); 
}



