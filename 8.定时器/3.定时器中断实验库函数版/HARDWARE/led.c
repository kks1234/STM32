#include "led.h"
#include "stm32f10x.h"
void led_init()
{
	GPIO_InitTypeDef GPIO_InitStruce;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStruce.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruce.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruce.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruce);
	
	GPIO_InitStruce.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruce.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruce);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
	
}

