#include "stm32f10x.h"
#include "iic.h"
#include "ccs811.h"
#include "delay.h"
#include "usart.h"


extern ccs811_measurement_t CCS;
extern u8 Information[10];
extern u8 MeasureMode,Status,Error_ID;
extern u8 temp;
extern u8 BUF[12];
int main()
{
	uart_init(115200);
	delay_init();
	I2C_GPIO_Config();
	CCS811_Init();

	while(1)
	{
		CCS811_Getval();
		printf("eco2=%d  tvoc=%d\r\n",CCS.eco2,CCS.tvoc);

		delay_ms(100);
	}
	
	
	
}






