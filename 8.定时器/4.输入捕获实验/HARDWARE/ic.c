#include "ic.h"
#include "stm32f10x.h"

u8 flag=0;
u16 num;

void ic_init(u16 arr,u16 psc)
{
	NVIC_InitTypeDef NVIC_InitTypeStruct;
	TIM_ICInitTypeDef TIM_ICInitTypeStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period=arr;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInitTypeStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitTypeStruct);
	
	TIM_ICInitTypeStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitTypeStruct.TIM_ICFilter=0;
	TIM_ICInitTypeStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitTypeStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitTypeStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM5,&TIM_ICInitTypeStruct);
	
	TIM_ITConfig(TIM5,TIM_IT_CC1|TIM_IT_Update,ENABLE);
	
	NVIC_InitTypeStruct.NVIC_IRQChannel=TIM5_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitTypeStruct);
	
	TIM_Cmd(TIM5,ENABLE);
	
}

void TIM5_IRQHandler(void)
{

	if(!(flag&0x80)) //捕获未完成
	{
		if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET)
		{
			if(flag&0x40) //已经捕获到高电平
			{
				
				if((flag&0x3f)==0x3f) //flag太大
				{
					flag|=0x80;
				}
				else
					flag++;
			}
		}

	if(TIM_GetITStatus(TIM5,TIM_IT_CC1)==SET)
	{
		if(flag&0x40)  //捕获到下降沿
		{
			flag|=0x80;
			num=TIM_GetCapture1(TIM5);
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);
		}
		else
		{
			flag=0;
			num=0;
			TIM_SetCounter(TIM5,0);
			flag|=0x40;
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);
		}
	}
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update|TIM_IT_CC1);
	
}
