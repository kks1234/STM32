#include "delay.h"
#include "stm32f10x.h"
#include "led.h"
#include "extern_it.h"

int main()
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	led_init();
	exit_init();
	LED0=0;
	while(1);	
}

