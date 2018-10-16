#include"led_init.h"
#include"stm32f10x.h"
void led_init(void)
{
	GPIO_InitTypeDef led_it;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	led_it.GPIO_Pin=GPIO_Pin_13;
	led_it.GPIO_Speed=GPIO_Speed_50MHz;
	led_it.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&led_it);	
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	
	
	led_it.GPIO_Pin=GPIO_Pin_5;
	led_it.GPIO_Speed=GPIO_Speed_50MHz;
	led_it.GPIO_Mode=GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOE,&led_it);
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);

}

