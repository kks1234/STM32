#include "tim.h"
/*****精确为1ms的定时器*****/
void TIM3_Init(void)
{
//使能定时器3的时钟
	RCC_APB1ENR|=1<<1;
//设置预分频数
	TIM3_PSC=71;
//设置自动重装载寄存器值
	TIM3_ARR=999;
//使能计数器并设置计数方式为向上计数
	TIM3_CR1|=1<<0|0<<4;
//设置溢出更新中断
	TIM3_CR1|=1<<2;
	TIM3_DIER=1<<0;
//开启中断
	NVIC_ISER0|=1<<29;
//更新中断等待响应
	TIM3_SR=1<<0;
}

	
