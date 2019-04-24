#include "siol.h"




void soil_init(void)
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	ADC_InitTypeDef ADC_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_DeInit(ADC1);
	ADC_InitTypeStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitTypeStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitTypeStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitTypeStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitTypeStruct.ADC_NbrOfChannel = 1;
	ADC_InitTypeStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitTypeStruct);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_1Cycles5);
		
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) );
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) );
	
}


float soil_get(void)
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
	return  (float)(3.3/4096)*ADC_GetConversionValue(ADC1);
}








