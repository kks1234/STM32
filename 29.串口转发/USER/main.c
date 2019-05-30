#include "stm32f10x.h"
#include "string.h"
#include "delay.h"
#include "usart.h"
#include "usart2.h"

RECV_BUF rec_buf;
u8 flag = 0;
int main()
{
	rec_buf.num_buf = 0;
	memset(rec_buf.recv_buf,0,sizeof(rec_buf.recv_buf));
	u8 temp;
	uart_init(9600);
	usrt2_init();
	delay_init();
	while(1)
	{

//			for(int i = 0; i< 4; i++) 
//		{
//				USART_SendData(USART2,'a');
//		
//				while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
//		}
	}
	
}




