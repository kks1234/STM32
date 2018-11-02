#include "tpad.h"
#include "stm32f10x.h"
#include "delay.h"

vu16 tpad_val=0;

void tpad_tim5ch2_init(u16 arr,u16 psc)   //初始化
{
	TIM_ICInitTypeDef TIM_ICInitTypeStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  //TIM5
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA_Pin_1
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);

	
	TIM_TimeBaseInitTypeStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeStruct.TIM_Period=arr;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitTypeStruct);   //TIM5时基初始化
	
	TIM_ICInitTypeStruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInitTypeStruct.TIM_ICFilter=0; //无滤波器
	TIM_ICInitTypeStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitTypeStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitTypeStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;   /*******错误****/
	TIM_ICInit(TIM5,&TIM_ICInitTypeStruct);
	
	TIM_Cmd(TIM5,ENABLE);
	
	
}


u16 tpad_get_val()    //得到TPAD充电时时所需要的时间
{
	tpad_reset();
	while(TIM_GetFlagStatus(TIM5,TIM_FLAG_CC2)==RESET)
	{
		if(TIM_GetCounter(TIM5)>TIM_ARR_MAX-500) return  TIM_GetCounter(TIM5);
	}
	
	return TIM_GetCapture2(TIM5);
	
}

void tpad_reset()   //TPAD复位
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);

	delay_ms(5);
	
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update|TIM_IT_CC2);
	TIM_SetCounter(TIM5,0);
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);


}

u16 tpad_get_maxval(u8 num)
{
	u16 temp=0;
	u16 max=0;
	while(num--)
	{	
		max=tpad_get_val();
		if(max>temp)
			temp=max;
	}
	return temp;
	
}


void tpad_init()
{
	u8 i,j;
	u16 number[10];
	u16 val=0;
	tpad_tim5ch2_init(TIM_ARR_MAX,8); //9MHZ
	
	for(i=0;i<10;i++)
	{
		number[i]=tpad_get_val();
		delay_ms(10); 
	}
	
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)   /**************************出错********************/
		{
			if(number[j]>number[j+1])
			{
				u16 temp;
				temp=number[j];
				number[j]=number[j+1];
				number[j+1]=temp;
			}
		}
	}
	for(i=2;i<8;i++)
		val+=number[i];
	val/=6;
	
	tpad_val=val;	
}



u8 tpad_scan(u8 mode)
{
	static u8 flag=0;
	u8 num=3;  //max取样次数
	u8 rel=0;
	u16 temp;
	if(mode)
	{
		flag=0;
		num=6;
	}
	temp=tpad_get_maxval(num);
	
	if(temp>tpad_val+TPAD_FLAG)
	{
		if(flag==0)
			rel=1;	//按键被按下
		flag=2;
	}
	
	if(flag)
		flag--;
	return rel;
	
}


