#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "can.h"
#include "key.h"
#include "led.h"



extern u8 Sdata[DATA_MAX];
extern u8 Rdata[DATA_MAX];




int main()
{
	u8 i,key_flag,r_flag;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÖÐ¶Ï·Ö×é
	uart_init(115200);
	delay_init();
	Can_Init();
	key_init();
	led_init();
	
	for(i=0; i<8; i++)
	{	Sdata[i] = i; Rdata[i] = 0;}
	
	while(1)
	{
		
		key_flag = key_scan(0);
		if(key_flag == 1)
		{
			Can_SendMessages(Sdata,8);
		}
		
		r_flag = Can_ReceiveMessages(Rdata);
		if( r_flag )
		{
			for(i=0; i<r_flag; i++)
				printf("0x0%d ",Rdata[i]);
			printf("\r\n");				
		}

		led_status();
	}
}



