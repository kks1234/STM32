#include "stm32f10x.h"


void USART_TR(void)
{
	GPIO_InitTypeDef GPIO_InitStruce;
	USART_InitTypeDef USART_InitStruce;
	NVIC_InitTypeDef NVIC_InitStruce;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能串口1的时钟
	
	GPIO_InitStruce.GPIO_Mode=GPIO_Mode_AF_PP; //配置PA9  TX  复用推挽输出
	GPIO_InitStruce.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruce.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruce);
	
	GPIO_InitStruce.GPIO_Mode=GPIO_Mode_IN_FLOATING; //配置PA10 RX  浮空输入或者上拉输入
	GPIO_InitStruce.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruce.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruce);
	
	USART_DeInit(USART1); //串口复位
	USART_InitStruce.USART_BaudRate=115200;    //串口初始化   波特率115200
	USART_InitStruce.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //硬件流控制
	USART_InitStruce.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;  //usart发送接收使能
	USART_InitStruce.USART_Parity=USART_Parity_No;  //奇偶校验位控制
	USART_InitStruce.USART_StopBits=USART_StopBits_1;  //停止位设置
	USART_InitStruce.USART_WordLength=USART_WordLength_8b;  //数据宽度

	USART_Init(USART1,&USART_InitStruce); //USART初始化
	
	USART_Cmd(USART1,ENABLE);   //串口使能
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); //串口中断设置 
	
	
	NVIC_InitStruce.NVIC_IRQChannel=USART1_IRQn;  //通道
	NVIC_InitStruce.NVIC_IRQChannelCmd=ENABLE;  //通道使能
	NVIC_InitStruce.NVIC_IRQChannelPreemptionPriority=1;  //
	NVIC_InitStruce.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruce);
	
	
}

void USART1_IRQHandler(void)
{
	u8 temp;
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{	temp=USART_ReceiveData(USART1);
	
		USART_SendData(USART1,temp);
	}
	
}


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART_TR();
	while(1);
}

