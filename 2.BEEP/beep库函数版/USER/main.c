#include "be.h"
#include "sys.h"
//#include "stm32f10x_gpio.h"
#include "delay.h"
int main()
{
	Init();
	delay_init();
	while(1)
	{
		PBout(5)=1;
		PBout(8)=1;
		delay_ms(500);
		PBout(5)=0;
		PBout(8)=0;
		delay_ms(500);
	}
}

