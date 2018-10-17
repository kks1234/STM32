#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Init()
{
	GPIO_InitTypeDef init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	init.GPIO_Mode = GPIO_Mode_Out_PP;
	init.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_8;
	init.GPIO_Speed =GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&init);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_8);
	
}


