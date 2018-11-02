#include "rs485.h"
#include "stm32f10x.h"
#include "misc.h"
#include "sys.h"
#include "delay.h"
#define k0 PEin(4)
#define led  PBout(5)
u8 key;
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

}
u8 key_scan(u8 mode)
{
	static u8 flag;
	if(mode)
		flag=1;                                                /***************键盘设置**************************************/
	if(flag&&k0==0)
	{
		delay_ms(5);
		flag=0;
		if(k0==0)
			return 1;
	}else if(k0==1)
		flag=1;	
	return 0;
}
u8 a[5];
u8 i;
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	a[0]=89;
	a[1]=72;
	a[2]=12;
	a[3]=12;
	a[4]=11;
	KEY_Init();
	rs485_init();
	
	delay_init();
	
	while(1)
	{
		key=key_scan(0);
		if(key==1)
		{
			rs485_send_data(a,5);
			for(i=0;i<5;i++)
			{
				a[i]++;
			}
		}
		PBout(5)=~PBout(5);
		delay_ms(200);
		
	}
}

