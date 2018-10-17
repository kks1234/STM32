#include "stm32f10x.h"
#include "be.h"

void beinit ()
{
	RCC->APB2ENR|=1<<3;
	
	GPIOB->CRL&=0xFF0FFFFF;
	GPIOB->CRL|=0X00300000;
	GPIOB->CRH&=0XFFFFFFF0;
	GPIOB->CRH|=0X00000003;
	
	GPIOB->ODR|=1<<5;
	GPIOB->ODR|=1<<8;
}
