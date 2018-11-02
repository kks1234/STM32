#include "stm32f10x_rcc.h"
#include "led.h"




void led_init()
{
	GPIO_InitTypeDef GPIO_InitStruce;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStruce.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruce.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruce.GPIO_Mode=GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOB,&GPIO_InitStruce);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
}


