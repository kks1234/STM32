#include "led.h"
#include "misc.h"
#include "time.h"
#include "delay.h"
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	delay_init();
	led_init();
	tim_init(4999,7199); //500ms
	
	while(1)
	{
		LED1=!LED1;
		delay_ms(800);
	}
	
}



