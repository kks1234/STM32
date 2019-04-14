#include "stm32f10x.h"
#include "sccb.h"
#include "ov7725.h"
#include "lcd.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"

extern uint8_t Ov7725_vsync;
u32 t_flag = 0;

int main()
{
	u8 lightmode=0,effect=0;
	s8 saturation=0,brightness=0,contrast=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	delay_init();
	led_init();
	TFTLCD_Init();
	while(1)
	{
		if(ov7725_init() == 0)
			break;
	}
	OV7725_Light_Mode(lightmode);
	OV7725_Color_Saturation(saturation);
	OV7725_Brightness(brightness);
	OV7725_Contrast(contrast);
	OV7725_Special_Effects(effect);
	while(1)
	{
		/*接收到新图像进行显示*/
		if( Ov7725_vsync == 2 )
		{
			OV_Lcd_Display(40,40,320,240);
			Ov7725_vsync = 0;			
		}
		
		delay_ms(10);
		t_flag ++;
		if(t_flag >= 100)
			t_flag = 0;
		if(t_flag % 50 == 0)
			LED0 = ~LED0;
		
	}		
	
}





