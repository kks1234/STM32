#include "PWM.H"
#include "stm32f10x.h"


void pwm_init(u16 arr,u16 psc)
{
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period=arr;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInitTypeStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitTypeStruct);
	
	TIM_OCInitTypeStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypeStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitTypeStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitTypeStruct);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3,ENABLE);

}


