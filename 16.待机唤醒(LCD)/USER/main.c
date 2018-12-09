#include "led.h"
#include "lcd.h"
#include "wkup.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	uart_init(115200);
	delay_init();
	Led_Init();
	Wkup_Init();
	TFTLCD_Init();
	
	LCD_ShowString(2,2,320,24,24,"WKUP SET TEXT");
	
	while(1)
	{
		LED = !LED;
		delay_ms(200);
	}
	
}




