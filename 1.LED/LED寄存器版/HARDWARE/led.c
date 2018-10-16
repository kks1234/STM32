#include"led.h"
#include"stm32f10x.h"
void led_init(void)
{
	RCC->APB2ENR|=1<<3;//GPIOB
	RCC->APB2ENR|=1<<6;//GPIOE
	
	GPIOB->CRL&=0XFF0FFFFF;
	GPIOB->CRL|=0x00300000;
	GPIOB->ODR|=1<<5;
	
	GPIOE->CRL&=0XFF0FFFFF;
	GPIOE->CRL|=0x00300000;
	GPIOE->ODR|=1<<5;
	
	
	
	
}

