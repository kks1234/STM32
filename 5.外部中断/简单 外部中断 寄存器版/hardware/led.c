#include "led.h"
#include "stm32f10x.h"

void led_init()
{
	RCC->APB2ENR|=1<<3;
	
	GPIOB->CRL&=0xFF0FFFFF;
	GPIOB->CRL|=0x00300000;
	
	GPIOB->BSRR|=1<<5;
	
	
}

