#include "pwm.h"
#include "stm32f10x.h"
#include "misc.h"
#include "gpio.h"
#include "sys.h"

u8 num=0;

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	gpio_init();
	pwm_tim3_init(2500,0); //pwm调节
	
	PEout(9)=1;
	PEout(10)=1;
	tim2_init(4999,7199);  //来回定时
	TIM_SetCompare1(TIM3,400);
	while(1);
}



void TIM2_IRQHandler (void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==ENABLE)
	{
		num++;
		if(num>=21)
		{
			num=0;
			//电机反转设置
				PEout(10)=~PEout(10);
				TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
			
		}
		else
			TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
	}
}
