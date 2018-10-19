#include "beep.h"


void beep_init()
{
	RCC->APB2ENR|=1<<3;
	GPIOB->CRH&=0xFFFFFFF0;
	GPIOB->CRH|=0x00000003;
	
	GPIOB->BRR=1<<8;
	
}
