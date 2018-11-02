#include "rs485.h"
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "misc.h"

u8 TR_BUF[64]; //接受缓冲
u8 LEN; //接受长度

void rs485_init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	NVIC_InitTypeDef NVIC_InitTypeStruct;
	USART_InitTypeDef USART_InitTypeStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitTypeStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);                    //LED
	
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitTypeStruct);               //控制rs485发送或接收
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);         //USART2 TX
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);            //USART2 RX

	
//	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//复位串口2
//	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//停止复位
	USART_InitTypeStruct.USART_BaudRate=9600;
	USART_InitTypeStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitTypeStruct.USART_WordLength=USART_WordLength_8b;
	USART_InitTypeStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitTypeStruct.USART_Parity=USART_Parity_No;
	USART_InitTypeStruct.USART_StopBits=USART_StopBits_1;
	USART_Init(USART2,&USART_InitTypeStruct);
	
	NVIC_InitTypeStruct.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitTypeStruct);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE);
	GPIO_ResetBits(GPIOD,GPIO_Pin_7); //默认为接收
	
}

void rs485_send_data(u8*buf,u8 len)
{
	u8 i;
	RS485_T_R=1;//发送模式
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2,buf[i]);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
		
	}
	LEN=0;
	RS485_T_R=0;
	
}
/*void rs485_send_data(u8*buf,u8 len)
{	u8 t;
	RS485_T_R=1;			//设置为发送模式
  	for(t=0;t<len;t++)		//循环发送数据
	{		   
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	  
		USART_SendData(USART2,buf[t]);
	}	 
 
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);		
	LEN=0;	  
	RS485_T_R=0;				//设置为接收模式
}*/
void rs485_receive_data(u8*buf,u8*len)
{
	u8 i;
	RS485_T_R=0;
	*len=LEN;
	delay_ms(10);
	if(*len==LEN&&*len)
	{
		for(i=0;i<*len;i++)
		{
			buf[i]=TR_BUF[i];
		}
	}
	*len=LEN;
	LEN=0; //清零计数器
}

void USART2_IRQHandler(void)
{
	u8 temp;
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{
		temp=USART_ReceiveData(USART2);
		if(LEN<64)
		{
			TR_BUF[LEN]=temp;
			LEN++;
		}
	}
		
}


