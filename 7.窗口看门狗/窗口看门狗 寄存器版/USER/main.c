#include "stm32f10x.h"
#include "led.h"
#include "wwdg.h"
#include "delay.h"
#include "sys.h"


int main()
{
	Stm32_Clock_Init(72);
	/*NVIC FEN ZU*/
	NVIC_groupconfig();
	delay_init(72);
	led_init();
	wwdg_init();
	LED0=0;
	delay_ms(500);
	while(1)
	{
		LED0=1;
	}
}

