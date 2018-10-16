
#include "delay.h"
#include "led.h"
#include "sys.h"
#include "usart.h"	
int main(void)
{
	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	  		//延时初始化
	uart_init(72,115200); 	//串口初始化为115200
	led_init();
	while(1)
	{
		GPIOB->ODR&=(~(1<<5));
		delay_ms(500);
		GPIOB->ODR|=(1<<5);
		
		GPIOE->ODR&=(~(1<<5));
		delay_ms(500);
		GPIOE->ODR|=(1<<5);
		
	}
}

