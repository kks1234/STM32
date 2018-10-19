#include "led.h"
#include  "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void led_init()
{
	GPIO_InitTypeDef init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);
	
	init.GPIO_Mode =GPIO_Mode_Out_PP;
	init.GPIO_Pin =GPIO_Pin_5;
	init.GPIO_Speed =GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&init);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_Init(GPIOE,&init);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
	
}

