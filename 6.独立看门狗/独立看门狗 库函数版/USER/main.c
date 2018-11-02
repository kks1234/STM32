#include "led.h"
#include "key.h"
#include "iwdg.h"
#include "delay.h"


int main()
{
	delay_init();
	led_init();
	key_init();
	iwdg_init();
	
	delay_ms(200);
	LED0=0;
	
	while(1)
	{
		u8 temp=key_scan(0);
		
		if(temp)
			IWDG_ReloadCounter();
	}
	
}


