#include "exti.h"
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
void key_init()
{	
	
	RCC->APB2ENR|=1<<6;
	GPIOE->CRL&=0xFFF0FFFF;
	GPIOE->CRL|=0x00080000;
	GPIOE->ODR|=1<<4;
	
}

void exti_init()
{
	/*zhong duan you xain ji fen zu*/
 	SCB->AIRCR&=0x0000F8FF;
	SCB->AIRCR|=0x05FA0000;
	SCB->AIRCR|=0x00005000;
	
	key_init();  // an jian chu shi hua
	RCC->APB2ENR|=1<<0; //AFIO
	AFIO->EXTICR[1]&=0xFFFFFFF0; //wai bu zhong duan ying she
	AFIO->EXTICR[1]|=0x00000004;
	
	EXTI->IMR|=1<<4;
	EXTI->FTSR|=1<<4;
	
	NVIC->ISER[EXTI4_IRQn/32]|=1<<(EXTI4_IRQn%32);
	NVIC->IP[EXTI4_IRQn]=0x50;	
	
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);
	if(KEY0==0)
	{
		LED0=~LED0;
	}
	EXTI->PR|=1<<4;
		
}


