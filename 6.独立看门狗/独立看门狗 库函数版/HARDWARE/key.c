#include "key.h"
#include "delay.h"
void key_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
}

u8 key_scan(u8 mode)
{
	static u8 flag=1;
	if(mode)
		flag=1;
	if(flag&&KEY0==0)
	{
		flag=0;
		delay_ms(10);
		if(KEY0==0)
			return 1;
	}
	else if(KEY0==1) 
			flag=1;
	return 0;
	
}

