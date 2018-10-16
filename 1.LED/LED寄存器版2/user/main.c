#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
int main()
{
	Stm32_Clock_Init(9);
	delay_init(72);
	
	//uart_init(72,115200);
	Led_Init();
	while(1)
	{
		GPIOB->BSRR|=(1<<5);
		delay_ms(100);
		GPIOB->BRR|=(1<<5);
		GPIOE->BSRR|=(1<<5);
		delay_ms(100);
		GPIOE->BRR|=(1<<5);
		
	}
}
	

