#include "adc.h"
#include "stm32f10x.h"



void adc_init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	ADC_InitTypeDef ADC_InitTypeStruct;
	//初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//GPIOC  PC0
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	
	//ADC 初始化设置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	ADC_DeInit(ADC1);
	
	ADC_InitTypeStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitTypeStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitTypeStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitTypeStruct.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitTypeStruct.ADC_NbrOfChannel = 1;
	ADC_InitTypeStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitTypeStruct);
	//规则通道设置
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_1Cycles5);
	
	ADC_Cmd(ADC1,ENABLE);
	//复位校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

	
}
u16 adc_goon() 
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
	return  ADC_GetConversionValue(ADC1);
}





