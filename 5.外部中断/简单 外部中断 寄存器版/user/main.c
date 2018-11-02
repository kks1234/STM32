#include "led.h"
#include "exti.h"
#include "delay.h"
#include "stm32f10x.h"
#include "sys.h"

int main()
{
	Stm32_Clock_Init(9);
	delay_init(72);
	led_init();
	exti_init();
	LED0=0;
	
	while(1);
	
		
		
	
}

