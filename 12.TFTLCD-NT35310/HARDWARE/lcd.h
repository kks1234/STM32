#ifndef __LCD_H__
#define __LCD_H__
#include "stm32f10x.h"


typedef struct {
	u16 width;   //屏幕宽度
	u16 height;  //屏幕高度
	u16 id;  	 //驱动ic ID
	u8 dir;      //设置扫描方向
	u16 wramcmd; //开始写GRAM指令
	u16 setxcmd; //设置x坐标命令
	u16 setycmd; //设置y坐标指令
	
}LCD_DEV;

//扫描方向定义
#define L2R_U2D   0 //从左到右，从上到下
#define L2R_D2U   1 //从左到右，从下到上
#define R2L_U2D   2 //从右到左，从上到下  
#define R2L_D2U   3 //从右到左，从下到上

#define U2D_L2R   4 //从上到下，从左到右
#define U2D_R2L   5 //从上到下，从右到左
#define D2U_L2R   6 //从下到上，从左到右
#define D2U_R2L   7 //从下到上，从右到左

//默认画笔颜色和背景颜色
#define PRINT_COLOR  RED
#define BACK_COLOR   GREEN

//默认扫描方向
#define TFT_SCAN   L2R_U2D
//部分颜色定义
#define WHILE  0xFFFF
#define BLACK  0x0000
#define BLUE   0x001F
#define RED    0xF800
#define GREEN  0x07E0


typedef struct lcd{   //RS选择  地址A10
	vu16 LCD_REG;   //写命令
	vu16 LCD_RAM;   //写数据
}TftlcdTypedef;
//LCD 结构体
#define LCD_BASE   ((u32)(0X6C000000|0X7FE))
#define LCD        ((TftlcdTypedef*)LCD_BASE)


void TFTLCD_Init(void);                                                     //LCD初始化
void LCD_Display_on(void);                                                  //显示开
void LCD_Display_off(void);                                                 //显示关
void LCD_WR_REG(u16 regval);												//写命令 寄存器
void LCD_WR_DATA(u16 data);													//写数据
u16  LCD_RD_DATA(void);														//读数据
void LCD_WriteReg(u16 LCD_Reg,u16 RegVal);									//写命令+数据
u16  LCD_ReadReg(u16 LCD_Reg);												//读寄存器值
void LCD_WriteRam_Start(void);												//开始写RGB函数
void LCD_WriteRam(u16 RGBcode);												//写RGB函数
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//设置坐标函数
void LCD_Clear(u16 Color);	 												//清屏函数
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);					//设置窗口函数
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);						//填充函数
void LCD_Scan_Dir(u8 dir);													//X Y扫描方向函数
void LCD_Display_Dir(u8 dir);												//LCD显示方向函数

u32 LCD_Pow(u16 m,u16 n);													//计算m的n次方函数
void LCD_DrawPoint(u16 x,u16 y);											//画点函数
u16  LCD_ReadPoint(u16 x,u16 y); 											//读点函数
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);								//快速画点函数
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);						 			//画圆函数
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//画线函数
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);	   					//画矩形函数
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//显示一个字符函数
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);  				//显示一个数字函数
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//显示一个字符串函数


#endif


