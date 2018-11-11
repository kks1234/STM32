#include "stm32f10x.h"
#include "led.h"
#include "iic.h"
#include "eeprom.h"
#include "delay.h"
#include "usart.h"


int main()
{
	u8 t,t1=75;
	u8 i[10];
	delay_init();
	led_init();
	uart_init(115200);
	iic_init();
	
	
	eeprom_write_page(2,1,&t1);
	
	delay_ms(100);
	eeprom_read_str(2,i,1);
	
	for(t=0;t<5;t++)
		printf("%d  ",i[t]);
		//	printf("%d",i[1]);
	
	while(1)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		delay_ms(100);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		delay_ms(100);
	}
	
	
	
}



