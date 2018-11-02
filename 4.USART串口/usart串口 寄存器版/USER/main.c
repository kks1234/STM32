#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"
#include "stdio.h"
#define TC (u16)(1<<6)


u16 IT_flag=0;
u8 num[200];
u16 t;
u16 num1=0;
int  main()
{
	Stm32_Clock_Init(9);
	SCB->AIRCR&=0x0000F8FF;
	SCB->AIRCR|=0x05FA0500;  /**要写入钥匙*/
	usart_init();
	led_init();
	delay_init(72);
	while(1)
	{
		if(IT_flag&0x8000)
		{
			printf("打印的字符为：\r\n\r\n");
			for(t=0;t<(IT_flag&0x3FFF);t++)
			{
				USART1->DR=num[t];
				while((TC&USART1->SR)==0);
			}
			printf("\r\n\r\n");
			IT_flag=0;   /*CHU CUO*/
		}
		else
		{
			num1++;
			if(num1%200==0) printf("请输入：\r\n");
			if(num1%30==0) LED0=~LED0;
			delay_ms(10);
			if(num1>=60000)
				num1=0;
		}
	}
}


