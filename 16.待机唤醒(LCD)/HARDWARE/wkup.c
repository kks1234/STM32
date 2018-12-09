#include "wkup.h"


//实现按键3秒 开启相应功能
u8 Wkup_Keydelay(void)
{
	u8 t = 0;
	LED = 0;   //复位开启状态灯
	while(1)
	{
		
		if(WKUP)
		{
			delay_ms(30);
			t++;
			if(t >= 100)
			{
				LED = 0; //开启状态灯
				return 1;
			}
		}
		else
		{
			LED = 1;
			return 0;
		}
		
	}	
}


//WKUP  Init
void Wkup_Init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	EXTI_InitTypeDef EXTI_InitTypeStruct;
	NVIC_InitTypeDef NVIC_InitTypeStruct;

	//RCC GPIOA  AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	//PA0 IUD
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	// Config EXTI
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_InitTypeStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitTypeStruct);
	
	//IT config
	NVIC_InitTypeStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitTypeStruct);
	
	if(Wkup_Keydelay() == 0)  Wkup_Standby();
}

void Wkup_Standby(void)
{
	//复位全部IO
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA|
						   RCC_APB2Periph_GPIOB|
						   RCC_APB2Periph_GPIOC|
						   RCC_APB2Periph_GPIOD|
						   RCC_APB2Periph_GPIOE|
						   RCC_APB2Periph_GPIOF|
						   RCC_APB2Periph_GPIOG,ENABLE);
	//RCC PWR
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	//WKUP Cmd
	PWR_WakeUpPinCmd(ENABLE);
	//进入待机模式
	PWR_EnterSTANDBYMode();
	
}

void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);
	
	if(Wkup_Keydelay())
	{
		Wkup_Standby();
	}
	
}







