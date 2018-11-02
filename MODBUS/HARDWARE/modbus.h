#ifndef __MODBUS_H__
#define __MODBUS_H__
#include "stm32f10x.h"
#define T_R_Mode  PDout(7)


typedef struct mod{
	u8 address; //设备地址
	u8 sendbuf[64];//发送缓冲区
	u8 recbuf[64]; //接受缓冲区
	u8 timflag;  //数据接收时间
	u8 timrun;   //定时器启动标志
	u8 reflag;   //接收到一帧数据的标志
	u8 recount;  //接受的数据个数
	u8 secount;  //发送的数据个数
	
}Modbus;

void modbus_init(void);
void modbus_fun3(u8 add,u16 readd,u16 renum);
void modbus_display(void);
void modbus_event(void);


#endif


