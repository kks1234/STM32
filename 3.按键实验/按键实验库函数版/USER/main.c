#include "led.h"
#include "key.h"
#include "beep.h"
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

int main()
{
	u8 num=0;
	beep_init();
	led_init();
	key_init();
	delay_init();
	
	LED0=0;
	//LED1=0;
	//beep=1;
	
	
	while(1)
	{
		num=key_scan(0);
		if(num)
		{
			switch(num)
			{
				case 1: LED0=!LED0; break;
				case 2: LED1=!LED1; break;
				case 3: beep=!beep;break;
				case 4: LED0=0;LED1=0;break;
			}
		}
		 else delay_ms(10);
	}
}


