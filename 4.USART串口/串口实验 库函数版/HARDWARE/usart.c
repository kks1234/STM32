#include "usart.h"
#include "stdio.h"


#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

void usart_init()
{
	GPIO_InitTypeDef  GPIO_InitStruce;
	USART_InitTypeDef  USART_InitStruce;
	NVIC_InitTypeDef  NVIC_InitStruce;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStruce.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruce.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruce.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruce);
	
	GPIO_InitStruce.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruce.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruce);
	
	USART_InitStruce.USART_BaudRate=115200;
	USART_InitStruce.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruce.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruce.USART_Parity=USART_Parity_No;
	USART_InitStruce.USART_StopBits=USART_StopBits_1;
	USART_InitStruce.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStruce);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
	
	NVIC_InitStruce.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruce.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruce.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruce.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruce);
	
	
}

