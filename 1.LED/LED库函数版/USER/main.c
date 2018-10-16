#include"stm32f10x.h"
#include"led_init.h" 
#include"delay.h"
#include "sys.h"
#define BEEP PBout(8)
void delay500(void)
{
  int  i;
  for(i=230;i>0;i--);
}
int main(void)
{
	u8 i,j;
	delay_init();
	led_init();
	while(1)
	{
		/*for(j=200;j>0;j--)
		{
			BEEP=~BEEP;       //输出频率1KHz
			delay500();       //延时500us
		}

		for(j=200;j>0;j--)
		{
			BEEP=~BEEP;       //输出频率500Hz
			delay500();       //延时1ms
			delay500();
		}*/
		
		PCout(13)=~PCout(13);
		delay_ms(500);
	
	}
}

