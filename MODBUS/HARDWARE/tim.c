#include "tim.h"
#include "modbus.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"

extern  Modbus modbus;

void tim3_init(u16 arr,u16 psc)  //arr 999 psc 71
{
	NVIC_InitTypeDef NVIC_InitTypeStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); // tim3 enable
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period=arr;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInitTypeStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitTypeStruct);   // tim3 base set
		
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   //tim3 it set
	
	NVIC_InitTypeStruct.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitTypeStruct);   //tim3 nvic  set
	
	TIM_Cmd(TIM3,ENABLE);  //tim3 cmd set
	
}


void TIM3_IRQHandler()   //tim it 
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		if(modbus.timrun==1) //定时器开始计时
		{
			modbus.timflag++; 
			if(modbus.timflag>=8)   //8ms 计时   默认8ms接收完成
			{
				modbus.timrun=0;  //关闭计时
				modbus.reflag=1;   //接收到一帧数据标志 
			} 	
		}		
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}




