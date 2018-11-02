#ifndef __OLED_H__
#define __OLED_H__
#include "sys.h"


//写数据 ：1  写命令 ：0
#define OLED_CMD 0
#define OLED_DATA 1   




//端口定义
#define CLK PDout(4)   //spi时钟线
#define SDA PDout(5)   //spi数据线
#define RST PDout(6)   //复位键
#define DC  PDout(7)   //数据命令选择线
#define CS  PDout(8)   //片选线  /* 模块无片选接口默认为零*/


//OLED传输方式 1:8080并口  0:SPI
#define OLED_MODE  0


void OLED_init(void);  //OLED初始化
void OLED_WR_Byte(u8 dat,u8 cmd);  //写一个字节数据或命令
u32 mypow(u8 m,u8 n);  //计算m^n
void OLED_Refresh_Gram(void);   //更新显示内存
void OLED_Clear(void); //清屏
void OLED_DrawPoint(u8 x,u8 y,u8 t);  //画点
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);  //显示一个字符
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);    //显示一个数字
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);     //显示一个字符串


#endif


