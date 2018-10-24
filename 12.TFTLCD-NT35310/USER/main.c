#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "led.h"
#include "sys.h"

/*TCTLCD IC : NT35310  显示测试实验*/
int main()
{
	u8 temp[]="My Name Is YCK.";
	u16 t=0;
	u32 i;
	led_init();
	delay_init();
	uart_init(115200);
	TFTLCD_Init();

	LCD_Draw_Circle(100,100,50); //画一个圆
	LCD_DrawLine(10,10,200,100); //画一条直线
	LCD_DrawRectangle(200,200,300,250); //画矩形

	/**********检验LCD_Set_Window*************/
	LCD_Set_Window(200,0,50,50);
	LCD_SetCursor(200,0);
	LCD_WriteRam_Start();
	for(i=0;i<3000;i++)
		LCD_WriteRam(BLUE);
	/*****************************************/
	LCD_Fill(200,400,250,450,BLACK);
	while(1)
	{
		LCD_ShowNum(200,100,t,3,24,1);
		
		LCD_Fill(0,350,320,374,WHILE);
		LCD_ShowString(0,350,320,24,24,temp);
		delay_ms(500);
		LCD_Fill(0,350,320,374,WHILE);
		LCD_ShowString(0,350,320,24,16,temp);
		delay_ms(500);
		LCD_Fill(0,350,320,374,WHILE);
		LCD_ShowString(0,350,320,24,12,temp);
		delay_ms(500);
		
		t++;
		if(t>=1000)
			t=0;
		PBout(5)=~PBout(5);
	}
}





