#include "tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"

u8 t=0;
u8 miao=0;
u8 fen=0;
u8 shi=0;

void tim_init(u16 arr ,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	NVIC_InitTypeDef NVIC_InitTypeStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period=arr;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler=psc;
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitTypeStruct);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	
	NVIC_InitTypeStruct.NVIC_IRQChannel=TIM6_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitTypeStruct);
	
	TIM_Cmd(TIM6,ENABLE);
	
}

void TIM6_IRQHandler(void)   //Èí¼þÊ±ÖÓ
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET)
	{
		t++;
		if(t>=2)
		{
			t=0;
			miao++;
			if(miao>=60)
			{
				miao=0;
				fen++;
				if(fen>=60)
				{
					fen=0;
					shi++;
					if(shi>=24)
						shi=0;
				 }
			 }
		 }
		
	}

	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	
}


