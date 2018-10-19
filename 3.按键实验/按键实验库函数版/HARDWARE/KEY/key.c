#include "key.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"
#include "sys.h"

void key_init()
{
	GPIO_InitTypeDef  init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	
	init.GPIO_Mode=GPIO_Mode_IPU;
	init.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;
	
	GPIO_Init(GPIOE,&init);
	
	init.GPIO_Mode=GPIO_Mode_IPD;
	init.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&init);
	
}

u8 key_scan(u8 mode)
{
	static char flag=1;
	if(mode==1) 
			flag=1;
	if((flag==1)&&(key0==0||key1==0||key2==0||key_up==1))
	{
		delay_ms(10);
		flag=0;
		if(key0==0) return k1;
		else if(key1==0) return k2;
		else if(key2==0) return k3;
		else if(key_up==1) return k4;
	}else if(key0==1&&key1==1&&key2==1&&key_up==0) flag=1;
	
	return 0;
}


