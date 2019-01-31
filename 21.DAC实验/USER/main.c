#include "stm32f10x.h"
#include "adc.h"
#include "dac.h"
#include "key.h"
#include "delay.h"
#include "usart.h"



u8 flag;



int main()
{
	u16 temp;
	float num;
	uart_init(115200);
	delay_init();
	adc_init();
	Dac_Init();
	Key_Init();
	
	while(1)
	{
		flag = Key_Scan(0);
		if(flag == 1)
		{
			temp += 200;
			
			Dac_Set_VVal(temp);
			num = ((float)adc_goon())/4096*3.3;
			printf("Temp : %d \r\nVal : %f\r\n",temp,num);
			
			if(temp > 3300)
				temp = 0;
		}
		delay_ms(100);
	}
	
	
}




