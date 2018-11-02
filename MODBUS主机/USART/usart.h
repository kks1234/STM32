#ifndef _usart_
#define _usart_

/****RCC寄存器组定义***********/
#define RCC_CR       *((unsigned volatile int*)0X40021000)
#define RCC_CFGR     *((unsigned volatile int*)0X40021004)
#define RCC_APB1ENR  *((unsigned volatile int*)0X4002101C)	
#define RCC_APB2ENR  *((unsigned volatile int*)0X40021018)	
/****GPIO寄存器组定义**********/
#define GPIOA_CRH    *((unsigned volatile int*)0X40010804)	
#define GPIOA_CRL    *((unsigned volatile int*)0X40010800)	
#define GPIOB_ODR    *((unsigned volatile int*)0X40010C0C)
#define GPIOE_ODR    *((unsigned volatile int*)0X4001180C)
#define GPIOB_CRL    *((unsigned volatile int*)0X40010C00)
#define GPIOB_CRH    *((unsigned volatile int*)0X40010C04)
#define GPIOE_CRL    *((unsigned volatile int*)0X40011800)
#define GPIOD_CRL    *((unsigned volatile int*)0X40011400)
#define GPIOD_ODR    *((unsigned volatile int*)0X4001140C)

/****FLASH访问寄存器组定义******/
#define FLASH_ACR    *((unsigned volatile int*)0X40022000)
/****串口配置寄存器组定义*******/
#define UART1_SR     *((unsigned volatile int *)0X40013800)
#define UART1_DR 	 *((unsigned volatile int *)0X40013804)
#define UART1_BRR    *((unsigned volatile int *)0X40013808)
#define UART1_CR1    *((unsigned volatile int *)0x4001380C)

#define UART2_SR     *((unsigned volatile int *)0X40004400)
#define UART2_DR 	 *((unsigned volatile int *)0X40004404)
#define UART2_BRR    *((unsigned volatile int *)0X40004408)
#define UART2_CR1    *((unsigned volatile int *)0x4000440C)
///****中断使能寄存器定义********/
#define NVIC_ISER1   *((unsigned volatile int *)0XE000E104)
	
#define RS485_1     GPIOD_ODR|=1<<7
#define RS485_0     GPIOD_ODR&=~(1<<7)

void RS485_Init(void);

void LED_Init(void);
void RS485_Send_Data(char data);

void UART1_Init(void);

void Delay(long counter);

#endif

