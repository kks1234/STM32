#include "pwm.h"
#include "stm32f10x.h"

void pwm_tim3_init(u16 arr,u16 psc)
{
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);     //GPIO  tim3_ch1 PA6 
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);  //tim3 时基初始化
	
	TIM_OCInitTypeStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypeStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypeStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM3,&TIM_OCInitTypeStruct);  //oc1 初始化
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3,ENABLE);

}

void tim2_init(u16 arr,u16 psc)
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

