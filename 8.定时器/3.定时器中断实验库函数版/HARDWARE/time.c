#include "time.h"
#include  "stm32f10x.h"
#include "misc.h"
#include "led.h"
void tim_init(u16 arr,u16 psc)
{
	NVIC_InitTypeDef NVIC_InitStruce;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruce;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStruce.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruce.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruce.TIM_Period=arr;
	TIM_TimeBaseInitStruce.TIM_Prescaler=psc;
	TIM_TimeBaseInitStruce.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruce);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_InitStruce.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruce.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruce.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruce.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruce);
	
	TIM_Cmd(TIM2,ENABLE);

}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_FLAG_Update)==ENABLE)
	{
		LED0=!LED0;
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
	}	
}

