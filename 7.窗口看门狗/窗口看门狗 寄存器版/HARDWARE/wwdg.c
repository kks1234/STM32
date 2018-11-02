#include "wwdg.h"
#include "stm32f10x.h"
#include "led.h"


void wwdg_init()
{
	RCC->APB1ENR|=1<<11;
	WWDG->CFR&=0xFC00;
	WWDG->CFR|=0<<9|3<<7|0x5F;
	
	WWDG->CR|=1<<7;
	WWDG->SR=0;
	
	NVIC->ISER[WWDG_IRQn/32]=1<<WWDG_IRQn;
	NVIC->IP[WWDG_IRQn]=0x50;
	
	WWDG->CFR|=1<<9;
	
}

void NVIC_groupconfig()
{
	u32 temp=0x05FA0000;
	temp|=0x0500;
	
	SCB->AIRCR|=temp;

}


void WWDG_IRQHandler(void)
{
	WWDG->CR=0x7f;
	WWDG->SR=0;
	LED1=!LED1;
	
}


