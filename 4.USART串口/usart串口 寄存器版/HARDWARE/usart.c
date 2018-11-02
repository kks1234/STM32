#include "usart.h"
#include "stm32f10x.h"
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
	//RCC->APB2ENR&=0x00000000;                                    /*不要复位相关寄存器 ，否则可能影响其他*/
	RCC->APB2ENR|=1<<2|1<<14;  //GPIOB USART1                      /*相关配置*/    
	
	GPIOA->CRH&=0xFFFFF00F;  //GPIOB USART1                          
	GPIOA->CRH|=0x000004B0;
	
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位
	
	USART1->BRR=0x0271; //115200
	//USART1->CR1&=0x0000; //RESET
	//USART1->CR1|=0x212B; 
	USART1->CR1|=0X202C; // UE=1 M_len=8 校验无 中断使能 RXNEIE=1 TE/RE=1 
	//USART1->CR1|=1<<5;
	/******出错地方*****/
	/****CR1寄存器TX与RX配置错误导致没有开启RX接收***/
	
	
	USART1->CR2&=0x0000; //RESET
	USART1->CR3&=0x0000; //RESET
	
	//NVIC->ISER[1]&=0xFFFFFFDFF;
	NVIC->ISER[1]|=1<<(USART1_IRQn%32);   //SET ENABLE USAT1
	
	NVIC->IP[37]=0x50; //  1  :  1	
	
}

