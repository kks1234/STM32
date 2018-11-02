#include "usart.h"


/********usart1初始化函数***********/
void UART1_Init(void)
{
    //使能USART1的时钟 使能GPIOA时钟
    RCC_APB2ENR|=1<<14|1<<2;
	//PA9设置为复用推挽输出，PA10设置为浮空输入
	GPIOA_CRH=9<<4|4<<8;
	//串口参数初始化，设置字长和停止位
	UART1_CR1|=0<<12|0<<10;
	//波特率设置为9600
	UART1_BRR|=468<<4|12;
	//开启中断
//	NVIC_ISER1|=1<<5;
	//设置USART1收发使能,使能接收中断
	UART1_CR1|=1<<2|1<<3;
	//开启USART1使能开关
	UART1_CR1|=1<<13;
 } 

/********RS485初始化函数***********/
void RS485_Init(void)
{
    //使能USART2的时钟 
    RCC_APB1ENR|=1<<17;
	//使能GPIOA、GPIOD时钟
	RCC_APB2ENR|=1<<2|1<<5;
	//PA2设置为复用推挽输出，PA3设置为浮空输入
	GPIOA_CRL=9<<8|4<<12;
	//配置PD7为推挽输出
	GPIOD_CRL=1<<28;
	//串口参数初始化，设置字长和停止位
	UART2_CR1|=0<<12|0<<10;
	//波特率设置为9600
	UART2_BRR|=234<<4|6;
	//开启中断
	NVIC_ISER1|=1<<6;
	//设置USART1收发使能,使能接收中断
	UART2_CR1|=1<<2|1<<3|1<<5;
	UART2_SR=0;
	//开启USART1使能开关
	UART2_CR1|=1<<13;
     RS485_0 ;   

}
/********RS485发送数据函数***********/
void RS485_Send_Data(char data)
{
	UART2_DR=data;
	while(!(UART2_SR&(1<<6)));//等待发送完成
}

void LED_Init(void)
{
	//初始化GPIOB和GPIOE	
	RCC_APB2ENR|=(1<<3)|(1<<6);   
	//设置PB5,PE5为通用推挽输出，最大速度为2MHz
	GPIOB_CRL=2<<20;
	GPIOE_CRL=2<<20;
	//设置PB8为推挽输出，最大速度为2MHZ
	GPIOB_CRH=2<<0;
}

void Delay(long counter)
{
while(counter--);
} 	
