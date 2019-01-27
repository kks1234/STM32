#include "stm32f10x.h"
#include "delay.h"
#include "light.h"
#include "key.h"
#include "led.h"
#include "usart.h"



u8 Ke ;

int main()
{
	uart_init(115200);
	Led_Init();
	Light_Init();
	delay_init();
	Key_Init();
	
	while(1)
	{
		Ke = Key_Scan(0);	
		if(Ke == 1)
		{
			printf("Val : %d\r\n",Light_Get_Val());
		}
		
		GPIOB->ODR = (u16)(1<<5);
		delay_ms(50);
		GPIOB->ODR = (u16)(0<<5);
		delay_ms(50);
	}
	
}





