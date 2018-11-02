#include "oled.h"
#include "oledfont.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "delay.h"
u8 GRAM_NUM[128][8];

u32 mypow(u8 m,u8 n)  //计算m^n
{
	u32 num=1;
	while(n--)
		num *= m;
	return num;
}

#if OLED_MODE

void OLED_WR_Byte(u8 dat,u8 cmd)  //写一个字节数据或命令
{
	/***********************/
	/***********************/
	/***********************/
}

#else
// dat 要写入的值   cmd写入数据或者命令选择
void OLED_WR_Byte(u8 dat,u8 cmd)  //写一个字节数据或命令
{
	u8 i;
	u8 temp=dat;
	CS=0;
	DC=cmd;
	for(i=0;i<8;i++)
	{
		CLK=0;
		if(temp&0x80)
			SDA=1;
		else
			SDA=0;
		CLK=1;
		temp<<=1;
		
	}
	
	CS=1;
	DC=1;
}
#endif


void OLED_Refresh_Gram(void)   //更新显示内存
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
		OLED_WR_Byte(0xB0+i,OLED_CMD);
		OLED_WR_Byte(0x00,OLED_CMD);
		OLED_WR_Byte(0x10,OLED_CMD);
		for(j=0;j<128;j++)
		{
			OLED_WR_Byte(GRAM_NUM[j][i],OLED_DATA);                     /***********疑问：写入时的顺序***********/
		}
	}
	
}


void OLED_Clear(void) //清屏
{
	u8 i,j;
	for(i=0;i<8;i++)
		for(j=0;j<128;j++)
			GRAM_NUM[j][i]=0x00;
	OLED_Refresh_Gram();
	
}

//  x:0-127
//  y:0-63
//  t: 0 清除  1 画点
void OLED_DrawPoint(u8 x,u8 y,u8 t)  //画点             
{
	u8 y0,y1,tep;
	if((x>127)||(y>63)) return;
	y0=7-y/8;                                         /**********疑问：画点时的坐标设置**************/
	y1=7-(y%8);
	
	tep=1<<y1;
	if(t)
		GRAM_NUM[x][y0]|=tep;
	else
		GRAM_NUM[x][y0]&=~tep;   /*出错*/
		
}
		/********************x：0-127,y：0-63*****************************************/
		/********************chr：要显示的字符 num：要显示的数字  *p：要显示的字符串**/
		/********************size：显示模型的大小 len：数字的位数*********************/
		/********************mode：0：不显示 1：显示**********************************/

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)  //显示一个字符
{
	u8 num_size,temp,y0;
	u8 i,j;
	y0=y;
	num_size=((size/8)+((size%8)?(1):(0)))*(size/2);
	chr=chr-' ';
	for(i=0;i<num_size;i++)
	{
		if(size==12) temp=asc2_1206[chr][i];
		else if(size==16) temp=asc2_1608[chr][i];
		else if(size==24) temp=asc2_2412[chr][i];
		else return ;
		for(j=0;j<8;j++)
		{
			if(temp&0x80)  OLED_DrawPoint(x,y,mode);
				else       OLED_DrawPoint(x,y,!mode);
			
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}		
	}
}


void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)    //显示一个数字
{
	u8 temp;
	u8 i=0;

	while(i<len)
	{
		temp=(num/(mypow(10,len-i-1)))%10;
		if(temp==0)
		{
			//if(i==len-1)           /***判断是否是最后一位为0***/
				OLED_ShowChar(x+(size/2)*i,y,'0',size,1);
			//else
				//OLED_ShowChar(x+(size/2)*i,y,' ',size,1);
		}
		else
			OLED_ShowChar(x+(size/2)*i,y,'0'+temp,size,1);
		i++;
	}
}


void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size)    //显示一个字符串
{
	while(*p<='~'&&*p>=' ')  //判断是否
	{
		if(x>128-(size/2))
		{ x=0; y+=size;}
		if(y>64-(size))
		{ y=0; OLED_Clear(); }
		OLED_ShowChar(x,y,*p,size,1);
		p++;
		x+=size/2;	
	}
}

void OLED_init()
{
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
	GPIO_InitTypeStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitTypeStruct.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitTypeStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOD,&GPIO_InitTypeStruct);
	GPIO_SetBits(GPIOD,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	
	DC=1;
	CS=1;
	RST=0;
	delay_ms(100);
	RST=1;
	
	OLED_WR_Byte(0xAE,OLED_CMD); //关闭显示
	OLED_WR_Byte(0xD5,OLED_CMD); //设置时钟分频因子,震荡频率
	OLED_WR_Byte(0x80,OLED_CMD);   //[3:0],分频因子;[7:4],震荡频率
	OLED_WR_Byte(0xA8,OLED_CMD); //设置驱动路数
	OLED_WR_Byte(0X3F,OLED_CMD); //默认0X3F(1/64) 
	OLED_WR_Byte(0xD3,OLED_CMD); //设置显示偏移
	OLED_WR_Byte(0X00,OLED_CMD); //默认为0

	OLED_WR_Byte(0x40,OLED_CMD); //设置显示开始行 [5:0],64行数.
													    
	OLED_WR_Byte(0x8D,OLED_CMD); //电荷泵设置
	OLED_WR_Byte(0x14,OLED_CMD); //bit2，开启/关闭
	OLED_WR_Byte(0x20,OLED_CMD); //设置内存地址模式
	OLED_WR_Byte(0x02,OLED_CMD); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
	OLED_WR_Byte(0xA1,OLED_CMD); //段重定义设置,bit0:0,0->0;1,0->127;
	OLED_WR_Byte(0xC0,OLED_CMD); //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
	OLED_WR_Byte(0xDA,OLED_CMD); //设置COM硬件引脚配置
	OLED_WR_Byte(0x12,OLED_CMD); //[5:4]配置
		 
	OLED_WR_Byte(0x81,OLED_CMD); //对比度设置
	OLED_WR_Byte(0xEF,OLED_CMD); //1~255;默认0X7F (亮度设置,越大越亮)
	OLED_WR_Byte(0xD9,OLED_CMD); //设置预充电周期
	OLED_WR_Byte(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB,OLED_CMD); //设置VCOMH 电压倍率
	OLED_WR_Byte(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WR_Byte(0xA4,OLED_CMD); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	OLED_WR_Byte(0xA6,OLED_CMD); //设置显示方式;bit0:1,反相显示;0,正常显示	    						   
	OLED_WR_Byte(0xAF,OLED_CMD); //开启显示	 
	OLED_Clear();	
	
	
	
}



