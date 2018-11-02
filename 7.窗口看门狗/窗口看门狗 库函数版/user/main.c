#include "stm32f10x.h"
#include "led.h"
#include "wwdg.h"
#include "delay.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	led_init();
	wwdg_init();
	delay_init();
	LED0=0;
	delay_ms(500);
	
	while(1)
	{
		LED0=1;
		
	}
	
	
	
}




