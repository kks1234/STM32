#include "ov7725.h"
#include "ov7725config.h"
#include "delay.h"
#include "stdio.h"
#include "lcd.h"




volatile uint8_t Ov7725_vsync ;	 /* 帧同步信号标志，在中断函数和main函数里面使用 */

 /*****************************************************************************************
 * 函数名：SCCB_WriteByte
 * 描述  ：写一字节数据
 * 输入  ：- WriteAddress: 待写入地址 	- SendByte: 待写入数据	- DeviceAddress: 器件类型
 * 注意  ：无        
 *****************************************************************************************/ 
void SCCB_WriteByte(u16 WriteAddress, u8 Sendbyte)
{
	sccb_start(); 					//启动SCCB传输
	sccb_write(OV_ID);
	wait_ack();	//写器件ID	  
	delay_us(100);
  	sccb_write(WriteAddress);
	wait_ack();		//写寄存器地址	  
	delay_us(100);
  	sccb_write(Sendbyte);
	wait_ack(); 	//写数据	 
  	sccb_stop();	  
}
/******************************************************************************************************************
 * 函数名：SCCB_ReadByte
 * 描述  ：读取一个数据
 * 输入  ：- ReadAddress: 待读出地址
 * 注意  ：无        
 **********************************************************************************************************************/ 
u8 SCCB_ReadByte(u8 ReadAddress)
{
	u8 val=0;
	sccb_start(); //wait_ack();				//启动SCCB传输
	sccb_write(OV_ID);
	wait_ack();	//写器件ID	  
	delay_us(100);	 
  	sccb_write(ReadAddress);
	wait_ack();			//写寄存器地址	  
	delay_us(100);	  
	sccb_stop();   
	delay_us(100);	   
	//设置寄存器地址后，才是读
	sccb_start();//wait_ack();
	sccb_write(OV_ID|0X01);
	wait_ack();//发送读命令	  
	delay_us(100);
  	val=sccb_read();		 	//读取数据
  	sccb_nack();
  	sccb_stop();
  	return val;
}


/******************************************************************************************************************
 * 函数名：SCCB_ReadBuf
 * 描述  ：读取一串数据
 * 输入  ：- pBuffer: 存放读出数据 	- length: 待读出长度	- ReadAddress: 待读出地址		 - DeviceAddress: 器件类型
 * 注意  ：无        
 **********************************************************************************************************************/ 
void SCCB_ReadBuf(u8*pBuff, u16 length, u8 ReadAddress)
{
	sccb_start();
	sccb_write(OV_ID); //器件地址
	if(!wait_ack())
	{
		sccb_stop();
		return ;
	}
	sccb_write((u8)(ReadAddress&0x00FF)); //寄存器地址
	wait_ack();
	sccb_stop();
		
	sccb_start();
	sccb_write(OV_ID + 1);
	if(!wait_ack())
	{
		sccb_stop();
		return ;
	}
	while(length)
	{
		*pBuff = sccb_read();
		if(length == 1)
			sccb_nack();
		else
			sccb_ack();
		pBuff++;
		length--;	
	}
	sccb_stop();
}




/* 初始化 */

u8 ov7725_init(void)
{
	u8 raw,temp;
	u16 sx=0,sy=0;
	u16 i=0;
	u16 reg=0;
	GPIO_InitTypeDef GPIO_InitTypeStruct;
	EXTI_InitTypeDef EXTI_InitTypeStruct;
	NVIC_InitTypeDef NVIC_InitTypeStruct;
	
	/* ov7725 gpio config */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|OV7725_OE_GPIO_CLK|
							OV7725_WRST_GPIO_CLK|OV7725_RRST_GPIO_CLK|
							OV7725_RCLK_GPIO_CLK|OV7725_WE_GPIO_CLK|
							OV7725_DATA_GPIO_CLK|OV7725_VSYNC_GPIO_CLK, ENABLE);
	
	/*(FIFO_OE--FIFO输出使能)*/
	GPIO_InitTypeStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitTypeStruct.GPIO_Pin = OV7725_OE_GPIO_PIN;
	GPIO_Init(OV7725_OE_GPIO_PORT, &GPIO_InitTypeStruct);
	
	/*(FIFO_WRST--FIFO写复位)*/
	GPIO_InitTypeStruct.GPIO_Pin = OV7725_WRST_GPIO_PIN;
	GPIO_Init(OV7725_WRST_GPIO_PORT, &GPIO_InitTypeStruct);
	
	/*(FIFO_RRST--FIFO读复位) */
	GPIO_InitTypeStruct.GPIO_Pin = OV7725_RRST_GPIO_PIN;
	GPIO_Init(OV7725_RRST_GPIO_PORT, &GPIO_InitTypeStruct);
		
	/*(FIFO_RCLK-FIFO读时钟)*/
	GPIO_InitTypeStruct.GPIO_Pin = OV7725_RCLK_GPIO_PIN;
	GPIO_Init(OV7725_RCLK_GPIO_PORT, &GPIO_InitTypeStruct);

	/*(FIFO_WE--FIFO写使能)*/
	GPIO_InitTypeStruct.GPIO_Pin = OV7725_WE_GPIO_PIN;	
	GPIO_Init(OV7725_WE_GPIO_PORT, &GPIO_InitTypeStruct);
	

    /*(FIFO_DATA--FIFO输出数据)*/
	GPIO_InitTypeStruct.GPIO_Pin = 	OV7725_DATA_0_GPIO_PIN | OV7725_DATA_1_GPIO_PIN |
									OV7725_DATA_2_GPIO_PIN | OV7725_DATA_3_GPIO_PIN |
									OV7725_DATA_4_GPIO_PIN | OV7725_DATA_5_GPIO_PIN |
									OV7725_DATA_6_GPIO_PIN | OV7725_DATA_7_GPIO_PIN;
	GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OV7725_DATA_GPIO_PORT, &GPIO_InitTypeStruct);
	FIFO_OE_L();	  					/*拉低使FIFO输出使能*/
	FIFO_WE_H();   						/*拉高使FIFO写允许*/
	
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	sccb_init();
	
	
	/*初始化时钟，注意中断要开AFIO*/
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_AFIO|OV7725_VSYNC_GPIO_CLK, ENABLE );	 
    
	/*初始化引脚*/
	GPIO_InitTypeStruct.GPIO_Pin =  OV7725_VSYNC_GPIO_PIN;
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OV7725_VSYNC_GPIO_PORT, &GPIO_InitTypeStruct);

	/*配置中断*/
    GPIO_EXTILineConfig(OV7725_VSYNC_EXTI_SOURCE_PORT, OV7725_VSYNC_EXTI_SOURCE_PIN);
    EXTI_InitTypeStruct.EXTI_Line = OV7725_VSYNC_EXTI_LINE;
    EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Falling ; 
    EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitTypeStruct);
    EXTI_GenerateSWInterrupt(OV7725_VSYNC_EXTI_LINE);		
	
	/*配置优先级*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitTypeStruct.NVIC_IRQChannel = OV7725_VSYNC_EXTI_IRQ;
    NVIC_InitTypeStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitTypeStruct.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitTypeStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitTypeStruct);
	
	/* ov7725 init */
	SCCB_WriteByte(0x12,0x80);	//软复位OV7725
	delay_ms(50); 
	reg=SCCB_ReadByte(0X1c);		//读取厂家ID 高八位
	reg<<=8;
	reg|=SCCB_ReadByte(0X1d);		//读取厂家ID 低八位
	if(reg!=OV7725_MID)
	{
		printf("MID:%d\r\n",reg);
		return 1;
	}
	reg=SCCB_ReadByte(0X0a);		//读取厂家ID 高八位
	reg<<=8;
	reg|=SCCB_ReadByte(0X0b);		//读取厂家ID 低八位
	if(reg!=OV7725_PID)
	{
		printf("HID:%d\r\n",reg);
		return 2;
	}   
 	//初始化 OV7725,采用QVGA分辨率(320*240)  
	for(i=0;i<sizeof(ov7725_init_reg_tb1)/sizeof(ov7725_init_reg_tb1[0]);i++)
	{								
	   	SCCB_WriteByte(ov7725_init_reg_tb1[i][0],ov7725_init_reg_tb1[i][1]);
 	} 

	SCCB_WriteByte(COM7,0x46);		//设置为QVGA模式
	SCCB_WriteByte(HSTART,0x3f); 	//水平起始位置
	SCCB_WriteByte(HSIZE, 0x50); 	//水平尺寸
	SCCB_WriteByte(VSTRT, 0x03); 	//垂直起始位置
	SCCB_WriteByte(VSIZE, 0x78); 	//垂直尺寸
	SCCB_WriteByte(HREF,  0x00);
	SCCB_WriteByte(HOutSize,0x50);	//输出尺寸
	SCCB_WriteByte(VOutSize,0x78); //输出尺寸
	
	raw=SCCB_ReadByte(HSTART);
	temp=raw+(sx>>2);//sx高8位存在HSTART,低2位存在HREF[5:4]
	SCCB_WriteByte(HSTART,temp);
	SCCB_WriteByte(HSIZE,320>>2);//width高8位存在HSIZE,低2位存在HREF[1:0]
	
	raw=SCCB_ReadByte(VSTRT);
	temp=raw+(sy>>1);//sy高8位存在VSTRT,低1位存在HREF[6]
	SCCB_WriteByte(VSTRT,temp);
	SCCB_WriteByte(VSIZE,240>>1);//height高8位存在VSIZE,低1位存在HREF[2]
	
	raw=SCCB_ReadByte(HREF);
	temp=((sy&0x01)<<6)|((sx&0x03)<<4)|((240&0x01)<<2)|(240&0x03)|raw;
	SCCB_WriteByte(HREF,temp);
	
	SCCB_WriteByte(HOutSize,320>>2);
	SCCB_WriteByte(VOutSize,240>>1);
	
	SCCB_ReadByte(EXHCH);	
	temp = (raw|(320&0x03)|((240&0x01)<<2));	
	SCCB_WriteByte(EXHCH,temp);
  	return 0; 	//ok
}
















////////////////////////////////////////////////////////////////////////////
//OV7725功能设置
//白平衡设置
//0:自动模式
//1:晴天
//2,多云
//3,办公室
//4,家里
//5,夜晚
void OV7725_Light_Mode(u8 mode)
{
	switch(mode)
	{
		case 0:	//Auto，自动模式
			SCCB_WriteByte(0x13, 0xff); //AWB on 
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;
		case 1://sunny，晴天
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x5a);
			SCCB_WriteByte(0x02, 0x5c);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 2://cloudy，多云
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x58);
			SCCB_WriteByte(0x02, 0x60);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 3://office，办公室
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x84);
			SCCB_WriteByte(0x02, 0x4c);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	
		case 4://home，家里
			SCCB_WriteByte(0x13, 0xfd); //AWB off
			SCCB_WriteByte(0x01, 0x96);
			SCCB_WriteByte(0x02, 0x40);
			SCCB_WriteByte(0x0e, 0x65);
			SCCB_WriteByte(0x2d, 0x00);
			SCCB_WriteByte(0x2e, 0x00);
			break;	

		case 5://night，夜晚
			SCCB_WriteByte(0x13, 0xff); //AWB on
			SCCB_WriteByte(0x0e, 0xe5);
			break;
	}
}		  
//色度设置
//sat:-4~+4
void OV7725_Color_Saturation(s8 sat)
{
 	if(sat>=-4 && sat<=4)
	{	
		SCCB_WriteByte(USAT,(sat+4)<<4); 
		SCCB_WriteByte(VSAT,(sat+4)<<4);
	}
}
//亮度设置
//bright：-4~+4
void OV7725_Brightness(s8 bright)
{
	u8 bright_value,sign;
  	switch(bright)
	{
		case 4:
			bright_value = 0x48;
			sign = 0x06;
			break;
		case 3:
			bright_value = 0x38;
			sign = 0x06;		
			break;	
		case 2:
			bright_value = 0x28;
			sign = 0x06;			
			break;	
		case 1:
			bright_value = 0x18;
			sign = 0x06;			
			break;
		case 0:
			bright_value = 0x08;
			sign = 0x06;			
			break;	
		case -1:
			bright_value = 0x08;
			sign = 0x0e;		
			break;		
		case -2:
			bright_value = 0x18;
			sign = 0x0e;		
			break;	
		case -3:
			bright_value = 0x28;
			sign = 0x0e;		
			break;	
		case -4:
			bright_value = 0x38;
			sign = 0x0e;		
			break;	
	}
	SCCB_WriteByte(BRIGHT, bright_value);
	SCCB_WriteByte(SIGN, sign);
}
//对比度设置
//contrast：-4~+4
void OV7725_Contrast(s8 contrast)
{
	if(contrast >= -4 && contrast <=4)
	{
		SCCB_WriteByte(CNST,(0x30-(4-contrast)*4));
	}
}
//特效设置
//0:普通模式    
//1,负片
//2,黑白   
//3,偏红色
//4,偏绿色
//5,偏蓝色
//6,复古	    
void OV7725_Special_Effects(u8 eft)
{
	switch(eft)
	{
		case 0://正常
			SCCB_WriteByte(0xa6, 0x06);//TSLB设置
			SCCB_WriteByte(0x60, 0x80);//MANV,手动V值
			SCCB_WriteByte(0x61, 0x80);//MANU,手动U值
			break;
		case 1://负片
			SCCB_WriteByte(0xa6, 0x46);
			break;
		case 2://黑白
			SCCB_WriteByte(0xa6, 0x26);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0x80);
			break;		
		case 3://偏红
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x80);
			SCCB_WriteByte(0x61, 0xc0);		
			break;
		case 4://偏绿
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x60);
			SCCB_WriteByte(0x61, 0x60);		
			break;
		case 5://偏蓝
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0xa0);
			SCCB_WriteByte(0x61, 0x40);	
			break;
		case 6://复古
			SCCB_WriteByte(0xa6, 0x1e);
			SCCB_WriteByte(0x60, 0x40);
			SCCB_WriteByte(0x61, 0xa0);
			break;	

	}
}	
//设置图像输出窗口
//width:输出图像宽度,<=320
//height:输出图像高度,<=240
//mode:0，QVGA输出模式；1，VGA输出模式
//QVGA模式可视范围广但近物不是很清晰，VGA模式可视范围小近物清晰
void OV7725_Window_Set(u16 width,u16 height,u8 mode)
{
	u8 raw,temp;
	u16 sx,sy;	
	if(mode)
	{
		sx=(640-width)/2;
		sy=(480-height)/2;
		SCCB_WriteByte(COM7,0x06);		//设置为VGA模式
		SCCB_WriteByte(HSTART,0x23); 	//水平起始位置
		SCCB_WriteByte(HSIZE,0xA0); 	//水平尺寸
		SCCB_WriteByte(VSTRT,0x07); 	//垂直起始位置
		SCCB_WriteByte(VSIZE,0xF0); 	//垂直尺寸
		SCCB_WriteByte(HREF,0x00);
		SCCB_WriteByte(HOutSize,0xA0); //输出尺寸
		SCCB_WriteByte(VOutSize,0xF0); //输出尺寸
	}
	else
	{
		sx=(320-width)/2;
		sy=(240-height)/2;
		SCCB_WriteByte(COM7,0x46);		//设置为QVGA模式
		SCCB_WriteByte(HSTART,0x3f); 	//水平起始位置
		SCCB_WriteByte(HSIZE, 0x50); 	//水平尺寸
		SCCB_WriteByte(VSTRT, 0x03); 	//垂直起始位置
		SCCB_WriteByte(VSIZE, 0x78); 	//垂直尺寸
		SCCB_WriteByte(HREF,  0x00);
		SCCB_WriteByte(HOutSize,0x50);	//输出尺寸
		SCCB_WriteByte(VOutSize,0x78); //输出尺寸
	}
	raw=SCCB_ReadByte(HSTART);
	temp=raw+(sx>>2);//sx高8位存在HSTART,低2位存在HREF[5:4]
	SCCB_WriteByte(HSTART,temp);
	SCCB_WriteByte(HSIZE,width>>2);//width高8位存在HSIZE,低2位存在HREF[1:0]
	
	raw=SCCB_ReadByte(VSTRT);
	temp=raw+(sy>>1);//sy高8位存在VSTRT,低1位存在HREF[6]
	SCCB_WriteByte(VSTRT,temp);
	SCCB_WriteByte(VSIZE,height>>1);//height高8位存在VSIZE,低1位存在HREF[2]
	
	raw=SCCB_ReadByte(HREF);
	temp=((sy&0x01)<<6)|((sx&0x03)<<4)|((height&0x01)<<2)|(width&0x03)|raw;
	SCCB_WriteByte(HREF,temp);
	
	SCCB_WriteByte(HOutSize,width>>2);
	SCCB_WriteByte(VOutSize,height>>1);
	
	SCCB_ReadByte(EXHCH);	
	temp = (raw|(width&0x03)|((height&0x01)<<2));	
	SCCB_WriteByte(EXHCH,temp);	
}





/**
  * @brief  设置显示位置
	* @param  sx:x起始显示位置
	* @param  sy:y起始显示位置
	* @param  width:显示窗口宽度,要求跟OV7725_Window_Set函数中的width一致
	* @param  height:显示窗口高度，要求跟OV7725_Window_Set函数中的height一致
  * @retval 无
  */
void OV_Lcd_Display(u16 sx,u16 sy,u16 width,u16 height)
{
	u32 i;
	u16 Camera_Data;
	LCD_Scan_Dir(U2D_L2R);//从上到下,从左到右
	
	LCD_Set_Window(sx,sy,width,height);
	LCD_WriteRam_Start();
	
	FIFO_PREPARE;  			/*FIFO准备*/
	for(i=0;i<width*height;i++)
	{	
		READ_FIFO_PIXEL(Camera_Data);
	//	printf("0x%x\t",Camera_Data);
		LCD_WriteRam(Camera_Data);
	}
	LCD_Scan_Dir(TFT_SCAN);	
}
























