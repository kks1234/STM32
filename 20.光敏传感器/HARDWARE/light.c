#include "light.h"
#include "stm32f10x.h"
#include "delay.h"

//ADC3 初始化
void Light_Init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	ADC_InitTypeDef ADC_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitTypeStruct);
	
	ADC_DeInit(ADC3);
	ADC_InitTypeStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitTypeStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitTypeStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitTypeStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitTypeStruct.ADC_NbrOfChannel = 1;
	ADC_InitTypeStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC3,&ADC_InitTypeStruct);
	
	ADC_RegularChannelConfig(ADC3,ADC_Channel_6,1,ADC_SampleTime_1Cycles5);   //ADC_Channel_6
	
	ADC_Cmd(ADC3,ENABLE);
	
	ADC_ResetCalibration(ADC3);
	while(ADC_GetResetCalibrationStatus(ADC3));
	ADC_StartCalibration(ADC3);
	while(ADC_GetCalibrationStatus(ADC3));
	
}


//开始
u16 Light_Goon()
{
	ADC_SoftwareStartConvCmd(ADC3,ENABLE);
	while( ADC_GetFlagStatus(ADC3,ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC3);
}


//计算
u8 Light_Get_Val() 
{
	u8 i;
	u32 val;
	for(i=0 ; i<10 ; i++)
	{
		val += Light_Goon();
		delay_ms(5);
	}
	val /= 10;
	if(val > 4000) val = 4000;
	return (u8)(100 - val/40); 
} 






