#include "stm32f10x.h"
#include "tim.h"
#include "modbus.h"
#include "misc.h"
#include "usart.h"

vu8 temp;

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(72);
	tim3_init(999,71);
	modbus_init();
	while(1)
	{
		modbus_fun3(0x02,0x2A,0x01);  //发送指令
		modbus_event();  //处理数据
	}
}



