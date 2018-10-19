#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "beep.h"


#define led0 PBout(5)
#define led1 PEout(5)
#define BEEP PBout(8)

int main()
{
	Stm32_Clock_Init(9);
	delay_init(72);
	uart_init(72,115200);
	led_init();
	beep_init();
	key_init();
	while(1)
	{
		u8 temp=keyscan(0);
		if(temp)
		switch(temp)
		{
			case 1: led0=~led0; break;
			case 2: led1=~led1; break;
			case 3: led0=0; led1=0; break;
			case 4: BEEP=~BEEP; break;
		}
	}
	
	
}

