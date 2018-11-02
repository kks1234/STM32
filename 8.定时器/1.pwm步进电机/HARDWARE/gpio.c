#include "gpio.h"
#include "stm32f10x.h"

void gpio_init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitTypeStruct);  //PE9
	
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOE,&GPIO_InitTypeStruct);   //PE10
	
	GPIO_SetBits(GPIOE,GPIO_Pin_9);
	GPIO_SetBits(GPIOE,GPIO_Pin_9);
	
}

