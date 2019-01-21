#include "stm32f10x.h"
#include "adc.h"
#include "usart.h"

float num;
u16 val;

int main()
	
{
	uart_init(115200);
	adc_init();
	
	while(1)
	{
		val = adc_goon();
		printf("val = %d",val);
		printf("\r\n------------------\r\n");
		num = (float)(3.3/4096)*val;
		printf("V : %f\r\n",num);
		
	}

}




