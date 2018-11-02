#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "stdio.h"
#include "delay.h"
#include "sys.h"
u16 USART_RX_STA=0;
u8  USART_RX_BUF[200];
u16 num=0;
u16 len,t;
int main()
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	led_init();
	usart_init();
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			len=USART_RX_STA&0x3fff;
			printf("打印的信息为：\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1,USART_RX_BUF[t]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
			}
			printf("\r\n\r\n");
			USART_RX_STA=0;
		}
		else
		{
			num++;
			if(num%500==0)
				printf("请输入\r\n\r\n");
			if(num%30==0)	LED0=~LED0;
			if(num>=60000)
				num=0;
			delay_ms(10);
		}
	}
}

