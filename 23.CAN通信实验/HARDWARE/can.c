#include "can.h"


u8 Sdata[DATA_MAX];
u8 Rdata[DATA_MAX];




static void Can_Gpio_Config(void)
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);  //使能CAN1 
	//CAN1 Rx
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	//CAN1 Tx
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitTypeStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeStruct);
	
}
static void Can_Mode_Config(void)
{
	CAN_InitTypeDef CAN_InitTypeStruct;
#if CAN_Rx_INT_ENABLE	
	NVIC_InitTypeDef NVIC_InitTypeStruct;
#endif
	
	CAN_InitTypeStruct.CAN_Mode = CAN_Mode_LoopBack; //回环模式
	CAN_InitTypeStruct.CAN_NART = DISABLE; //禁止报文自动重传 disable 不禁止
	CAN_InitTypeStruct.CAN_RFLM = DISABLE; //接受FIFO锁定模式
	CAN_InitTypeStruct.CAN_TTCM = DISABLE; //时间触发通信模式
	CAN_InitTypeStruct.CAN_TXFP = DISABLE; //报文发送优先级
	CAN_InitTypeStruct.CAN_ABOM = DISABLE; //自动离线管理
	CAN_InitTypeStruct.CAN_AWUM = ENABLE;  //自动唤醒模式
	
	CAN_InitTypeStruct.CAN_Prescaler = 4;  //4/36MHz = 1/9MHz
	CAN_InitTypeStruct.CAN_BS1 = CAN_BS1_5tq;
	CAN_InitTypeStruct.CAN_BS2 = CAN_BS2_3tq;
	CAN_InitTypeStruct.CAN_SJW = CAN_SJW_2tq;
	CAN_Init(CAN1,&CAN_InitTypeStruct);
	
#if CAN_Rx_INT_ENABLE
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
	NVIC_InitTypeStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitTypeStruct);
	
#endif
}
static void Can_Filter_Config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitTypeStruct;
	
	CAN_FilterInitTypeStruct.CAN_FilterActivation = ENABLE; //激活过滤器
	CAN_FilterInitTypeStruct.CAN_FilterFIFOAssignment = CAN_FilterFIFO0; //关联到 FIFO 0
	CAN_FilterInitTypeStruct.CAN_FilterMode = CAN_FilterMode_IdMask; //过滤器模式  掩码模式
	CAN_FilterInitTypeStruct.CAN_FilterNumber = 0; //第零个过滤器组
	CAN_FilterInitTypeStruct.CAN_FilterScale = CAN_FilterScale_32bit; //三十二位模式
	
	CAN_FilterInitTypeStruct.CAN_FilterIdHigh = ( ((0x00001314<<3)| CAN_ID_EXT| CAN_RTR_DATA ) &(0xFFFF0000) )>>16;
	CAN_FilterInitTypeStruct.CAN_FilterIdLow = ( ((0x00001314<<3)| CAN_ID_EXT| CAN_RTR_DATA ) & 0x0000FFFF );
	CAN_FilterInitTypeStruct.CAN_FilterMaskIdHigh = 0xFFFF;
	CAN_FilterInitTypeStruct.CAN_FilterMaskIdLow =	0xFFFF;
	
	CAN_FilterInit(&CAN_FilterInitTypeStruct);
}


void Can_Init()
{
	Can_Gpio_Config();
	Can_Mode_Config();
	Can_Filter_Config();
}





void Can_SendMessages(u8 * p, u8 len)
{
	u8 i,numb;
	CanTxMsg CanTxMsgStruct;
	
	//CanTxMsgStruct.StdId=
	CanTxMsgStruct.ExtId = 0x1314;
	CanTxMsgStruct.IDE = CAN_ID_EXT; //扩展ID
	CanTxMsgStruct.RTR = CAN_RTR_DATA;
	CanTxMsgStruct.DLC = len;
	for(i=0; i<len; i++)
	{
		CanTxMsgStruct.Data[i] = p[i];
	}
	numb = CAN_Transmit(CAN1,&CanTxMsgStruct); //返回发送的邮箱号
	while( CAN_TransmitStatus(CAN1, numb) == CAN_TxStatus_Failed);
}




u8 Can_ReceiveMessages(u8 * p)
{
	u8 i;
	CanRxMsg CanRxMsgStruct;
	if( CAN_MessagePending(CAN1, CAN_FIFO0) == 0 ) return 0;
	
	CAN_Receive(CAN1, CAN_FIFO0, &CanRxMsgStruct);
	for(i=0; i<CanRxMsgStruct.DLC; i++)
	{
		p[i] = CanRxMsgStruct.Data[i];
	}
	return CanRxMsgStruct.DLC;
}


#if CAN_Rx_INT_ENABLE

void USB_LP_CAN1_RX0_IRQHandler(void)
{
	u8 i;
	CanRxMsg CanRxMsgStruct;
	CAN_Receive(CAN1, CAN_FIFO0, &CanRxMsgStruct);
	for(i=0; i<CanRxMsgStruct.DLC; i++)
	{
		Rdata[i] = CanRxMsgStruct.Data[i];
		printf("%d ",Rdata[i]);
	}
	printf("\r\n");
}

#endif



