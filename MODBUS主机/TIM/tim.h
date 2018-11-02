#ifndef _TIM_
#define _TIM_

/****RCC寄存器组定义***********/
#define RCC_CR       *((unsigned volatile int*)0X40021000)
#define RCC_CFGR     *((unsigned volatile int*)0X40021004)
#define RCC_APB2ENR  *((unsigned volatile int*)0X40021018)	
#define RCC_APB1ENR  *((unsigned volatile int*)0X4002101C)
/****GPIO寄存器组定义**********/
#define GPIOA_CRH    *((unsigned volatile int*)0X40010804)	
#define GPIOB_ODR    *((unsigned volatile int*)0X40010C0C)
#define GPIOE_ODR    *((unsigned volatile int*)0X4001180C)
#define GPIOB_CRL    *((unsigned volatile int*)0X40010C00)
#define GPIOB_CRH    *((unsigned volatile int*)0X40010C04)
#define GPIOE_CRL    *((unsigned volatile int*)0X40011800)
/****FLASH访问寄存器组定义******/
#define FLASH_ACR    *((unsigned volatile int*)0X40022000)
/****串口配置寄存器组定义*******/	
#define UART1_SR     *((unsigned volatile int *)0X40013800)
#define UART1_DR 	 *((unsigned volatile int *)0X40013804)
#define UART1_BRR    *((unsigned volatile int *)0X40013808)
#define UART1_CR1    *((unsigned volatile int *)0x4001380C)
/****中断使能寄存器定义********/
#define NVIC_ISER1   *((unsigned volatile int *)0XE000E104)
#define NVIC_ISER0   *((unsigned volatile int *)0XE000E100)	
/****定时器配置寄存器组定义*****/
#define TIM3_CR1     *((unsigned volatile int *)0X40000400)	
#define TIM3_DIER    *((unsigned volatile int *)0X4000040C)
#define TIM3_SR      *((unsigned volatile int *)0X40000410)
#define TIM3_PSC     *((unsigned volatile int *)0X40000428)
#define TIM3_ARR     *((unsigned volatile int *)0X4000042C)		        
void TIM3_Init(void);                        


#endif 

