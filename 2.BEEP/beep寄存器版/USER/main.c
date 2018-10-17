#include "sys.h"
#include "usart.h"
#include "be.h"
#include "delay.h"


int main()
{

	delay_init(72);
	Stm32_Clock_Init(9);
	beinit();
//	uart_init(72,115200);
	while(1)
	{
		GPIOB->BRR |=1<<5;
		GPIOB->BSRR |=1<<8;
		delay_ms(500);
		GPIOB->BSRR|=1<<5;
		GPIOB->BRR|=1<<8;
		delay_ms(500);
	}
}

	

