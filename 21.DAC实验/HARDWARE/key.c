#include "key.h"
#include "delay.h"

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	
}


u8 Key_Scan(u8 mode)
{
	static u8 flag = 1;
	if(mode) flag = 1;
	
	if(flag && (WEKUP == 1) )
	{
		delay_ms(5);
		flag = 0;
		if(WEKUP == 1)
		{
			return 1;
		}	
	}else if(WEKUP == 0) flag = 1;
	
	return 0;	
}






