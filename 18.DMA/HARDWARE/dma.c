#include "dma.h"
#include "stm32f10x.h"

u8 buff[SIZEBUFF];


//  存储器到外设（串口）
void dma_init()
{
	DMA_InitTypeDef DMA_InitTypeStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_DeInit(DMA1_Channel4);   //将DMA的通道1寄存器重设为缺省值
	DMA_InitTypeStruct.DMA_BufferSize = SIZEBUFF;
	DMA_InitTypeStruct.DMA_DIR = DMA_DIR_PeripheralDST; //外设作为目标
	DMA_InitTypeStruct.DMA_M2M = DMA_M2M_Disable;  //存储器到存储器模式关
	DMA_InitTypeStruct.DMA_MemoryBaseAddr = (u32)buff; //存储器基地址
	DMA_InitTypeStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //存储器出传输大小 字节
	DMA_InitTypeStruct.DMA_MemoryInc =  DMA_MemoryInc_Enable; //存储器增量模式
	DMA_InitTypeStruct.DMA_Mode =  DMA_Mode_Normal; //DMA模式  单次
	DMA_InitTypeStruct.DMA_PeripheralBaseAddr = (u32) &USART1->DR; //外设基地址
	DMA_InitTypeStruct.DMA_PeripheralDataSize =  DMA_PeripheralDataSize_Byte;  //外设传输大小 字节
	DMA_InitTypeStruct.DMA_PeripheralInc =  DMA_PeripheralInc_Disable; //外设增量模式
	DMA_InitTypeStruct.DMA_Priority =  DMA_Priority_Medium;  //通道优先级
	DMA_Init(DMA1_Channel4,&DMA_InitTypeStruct);
	
}


void dma_goon()
{
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	DMA_Cmd(DMA1_Channel4,ENABLE);
	DMA_SetCurrDataCounter(DMA1_Channel4,SIZEBUFF);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC4) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC4);//清除通道4传输完成标志
	
	DMA_Cmd(DMA1_Channel4,DISABLE);
	USART_DMACmd(USART1,USART_DMAReq_Tx,DISABLE);
}











