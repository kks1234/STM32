#include "key.h"
#include "delay.h"
void key_init()
{
	RCC->APB2ENR|=1<<6;  //GPIO E  A
	RCC->APB2ENR|=1<<2;
	
	GPIOE->CRL&=0xFFF000FF;
	GPIOE->CRL|=0x000888FF;
	GPIOE->BSRR|=(1<<2)|(1<<3)|(1<<4);
	
	GPIOA->CRL&=0xFFFFFFF0;
	GPIOA->CRL|=0x00000008;
	GPIOA->BRR|=1<<0;
	
}

u8  keyscan(u8 mode)
{
	static u8 temp;
	if(mode)
		temp=1;
	if(temp&&(LED0==0||LED1==0||LED2==0||WEP==1))
	{
		temp=0;
		delay_ms(10);
		
		if(LED0==0) return 1;
		else if(LED1==0) return 2;
		else if(LED2==0)  return 3;
		else if(WEP==1) return 4;
	}else if(LED0==1&&LED1==1&&LED2==1&&WEP==0)  temp=1;
	
	return 0;
	
}

