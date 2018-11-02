#include "stm32f10x.h"
#include "PWM.H"
#include "delay.h"

int  main()
{
	u16 a=24;
	pwm_init(200,7199); //20ms
	delay_init();
	while(1)
	{
		for(a=6;a<=24;a++)
		{
			delay_ms(100);
			TIM_SetCompare1(TIM3,a);
		}
		for(a=24;a>=6;a--)
		{
			delay_ms(100);
			TIM_SetCompare1(TIM3,a);
		}
	}
	
}

