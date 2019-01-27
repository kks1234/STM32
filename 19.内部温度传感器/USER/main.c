#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "temper.h"


u8 Fl;

int main()
{
	uart_init(115200);
	delay_init();
	Led_Init();
	Temp_Init();
	Key_Init();
	
	while(1)
	{
		Fl = Key_Scan(0);
		if(Fl == 1)
		{
			printf("Tem : %f\r\n" ,Temp_Val());
		}
		
		GPIOB->ODR = (u16)(1<<5);
		delay_ms(50);
		GPIOB->ODR = (u16)(0<<5);
		delay_ms(50);
		
	}
}






