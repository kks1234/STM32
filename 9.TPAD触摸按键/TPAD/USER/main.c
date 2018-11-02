#include "stm32f10x.h"
#include "tpad.h"
#include "delay.h"
#include "led.h"
#include "sys.h"

#define LED0 PBout(5)
#define LED1 PEout(5)
extern vu16 tpad_val;
u8 t=0;

int main()
{
	delay_init();
	
	led_init();
	
	tpad_init();
	while(1)
	{
		if(tpad_scan(0))
		{
			LED1=~LED1;
		}
		t++;
		if(t==15)
		{
			t=0;
			LED0=~LED0;
		}
		
		delay_ms(10);
		
	}
	
	
}

