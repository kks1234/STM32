#include "stm32f10x.h"
#include "misc.h"
#include "ic.h"
#include "usart.h"
#include "stdio.h"

extern u8 flag;
extern u16 num;
u32 temp=0;

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	ic_init(0xFFFF,71);
	uart_init(115200);
	while(1)
	{
		if(flag&0x80)
		{
			temp=num+(flag&0x3f)*65536;
			printf("t=%d us\r\n",temp);
			flag=0;
;		}
	}
	
	
}


