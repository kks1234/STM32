#include "stm32f10x.h"
#include "led.h"
#include "lcd.h"
#include "rtc.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"

extern timer  time_struct;
extern u8 *week_set[7];

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	led_init();
	uart_init(115200);
	TFTLCD_Init();
	rtc_init();
	rtc_alarm_time(2018,12,1,19,51,10); //ƒ÷÷” ¥Æø⁄œ‘ æ
	LCD_ShowChar(136,110,':',24,1);
	LCD_ShowChar(170,110,':',24,1);
	LCD_ShowChar(150,50,'.',24,1);
	while(1)
	{
		led_OSstatus();
		
		LCD_ShowNum(136,20,time_struct.year,4,24,0);
		LCD_ShowNum(126,50,time_struct.month,2,24,0);
		LCD_ShowNum(162,50,time_struct.day,2,24,0);
		LCD_ShowNum(112,110,time_struct.hour,2,24,0);
		LCD_ShowNum(148,110,time_struct.minute,2,24,0);
		LCD_ShowNum(182,110,time_struct.second,2,24,0);
		
		
		LCD_ShowString(122,80,100,24,24,week_set[time_struct.week]);
	/*	switch(time_struct.week)
		{
			case 0 :	LCD_ShowString(122,80,100,24,24,"Sunday");
						break;
			case 1 :	LCD_ShowString(122,80,100,24,24,"Monday");
						break;
			case 2 :	LCD_ShowString(122,80,100,24,24,"Tuesday");
						break;
			case 3 :	LCD_ShowString(122,80,100,24,24,"Wednesday");
						break;
			case 4 :	LCD_ShowString(122,80,100,24,24,"Thursday");
						break;
			case 5 :	LCD_ShowString(122,80,100,24,24,"Friday");
						break;
			case 6 :	LCD_ShowString(122,80,100,24,24,"Saturday");
						break;
		}*/	
		//delay_ms(50);
	}
}


