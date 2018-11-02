#include "led.h"
#include "stm32f10x.h"

void led_init()
{
	//RCC->APB2ENR&=0x00000000;   /*不要复位寄存器，否则将会影响其他配置*/
	RCC->APB2ENR|=1<<3;
	
	GPIOB->CRL&=0XFF0FFFFF;
	GPIOB->CRL|=0X00300000;
	
	GPIOB->BSRR|=1<<5;
	
	
}

