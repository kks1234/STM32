#include "wwdg.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_wwdg.h"
#include "misc.h"
#include "led.h"

void wwdg_init()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	
	WWDG_SetWindowValue(0x5F);
	WWDG_Enable(0x7F);
	
	//WWDG_SetCounter(0x7F);  在到达窗口之前刷新了
	
	WWDG_ClearFlag();
	
	NVIC_InitStruct.NVIC_IRQChannel=WWDG_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	WWDG_EnableIT();
}



void WWDG_IRQHandler(void)
{
	
	WWDG_SetCounter(0x7F);
	WWDG_ClearFlag();
	LED1=~LED1;


	
}

