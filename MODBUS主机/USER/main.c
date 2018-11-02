#include"stdio.h"
#include"usart.h"
#include"TIM.h"
#include"modbusCRC.h"
#include"modbus.h"
void UART1_PUTC(unsigned char c)
{  
    while(!(UART1_SR&(1<<6))&&(!(UART1_SR&(1<<7))));
	UART1_DR=c;
}	
int fputc(int ch,FILE *f)
{
    UART1_PUTC(ch);
	return (ch);
}

unsigned volatile char flag=0;

void TIM3_IRQHandler(void)
{
 if((TIM3_SR&1)==1)
	{
		TIM3_SR=0;
		if(modbus.timrun!=0)  //定时器开始计时
		{
			modbus.timout++;  //每一毫秒加一次（达到4毫秒就认为一帧数据已收到）
			if(modbus.timout>=8)//间隔时间达到了时间
			{
				modbus.timrun=0;//关闭定时器--停止定时
				modbus.reflag=1;//收到一帧数据
			}
				
		}
	}	

}
/*每收到一个字节触发一次中断*/
void USART2_IRQHandler(void)
{
	if(UART2_SR&1<<5)
	{
		flag=UART2_DR;
		if(modbus.reflag==1)//有数据包正在处理
		{
			return;
		}
		modbus.rcbuf[modbus.recount++]=flag;
		modbus.timout=0;//每收到一个字节，数据断续时间就要清0
		if(modbus.recount==1)//收到主机发来的一帧数据的第一字节
		{
			modbus.timrun=1;//启动定时
		}
	}
}


int main(void)
{
    
    Modbus_Init();
    UART1_Init();
	TIM3_Init();
	while(1)
	{	
		Modbus_fun3(2,0X2A,1);
		Modbus_Event();//处理Modbus数据
	}	
}
