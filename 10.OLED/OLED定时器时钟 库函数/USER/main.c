#include "led.h"
#include "tim.h"
#include "oled.h"
#include "delay.h"
#include "stm32f10x.h"

extern u8 GRAM_NUM[128][8];
extern u8 t;
extern u8 t;
extern u8 miao;
extern u8 fen;
extern u8 shi;

u8 a[]="Shi Jian";
u8 b[]="YCK";
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	led_init();
	tim_init(5000,7199);   //—” ±500ms
	OLED_init();
	
	OLED_ShowString(32,0,a,16);
	OLED_ShowString(104,48,b,16);
	OLED_ShowChar(39,27,':',24,1);	
	OLED_ShowChar(75,27,':',24,1);
	
	OLED_Refresh_Gram();
	while(1)	
	{
		
		OLED_ShowNum(17,27,shi,2,24);
		OLED_ShowNum(51,27,fen,2,24);
		OLED_ShowNum(87,27,miao,2,24);
		OLED_Refresh_Gram();
		delay_ms(50);
		LED0=!LED0;	
	}


}



