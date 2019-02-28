#include "stm32f10x.h"
#include "iic.h"
#include "mpu6050.h"
#include "delay.h"
#include "usart.h"

short ACC1_data[3];
short ACC2_data[3];
short ACC3_data[3];
short ACC4_data[3];

int main()
{
	uart_init(115200);
	delay_init();
	IIC_Gpio_Config_Init();
	MPU1_Init();
	MPU2_Init();
	MPU3_Init();
	MPU4_Init();
	
	
	while(1)
	{
		MPU1_Read_Acc(ACC1_data);
		MPU2_Read_Acc(ACC2_data);
		MPU3_Read_Acc(ACC3_data);
		MPU4_Read_Acc(ACC4_data);
		printf("第一个 x= %d y= %d z= %d\r\n",ACC1_data[0],ACC1_data[1],ACC1_data[2]);
		printf("第二个 x= %d y= %d z= %d\r\n",ACC2_data[0],ACC2_data[1],ACC2_data[2]);
		printf("第三个 x= %d y= %d z= %d\r\n",ACC3_data[0],ACC3_data[1],ACC3_data[2]);
		printf("第四个 x= %d y= %d z= %d\r\n",ACC4_data[0],ACC4_data[1],ACC4_data[2]);
		delay_ms(100);
	}
	
	
	
	
}







