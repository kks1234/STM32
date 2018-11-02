#include"modbus.h"
#include"usart.h"
#include"ModbusCRC.h"
#include"stdio.h"
MODBUS modbus;

/*
因为波特率为9600
1位数据的时间为 1000000us/9600bit/s=104us
一个字节为 104us*10位
所以 Modbus一个数据帧完成各时间为13.5*104=3.6ms
*/


void Modbus_Init()
{
  modbus.timrun=0;//Modbus定时器停止计时
  RS485_Init();

}

void Modbus_fun3(unsigned char Addr,unsigned short int ReadAdd,unsigned short int ReadNum)//3号功能码处理(主机要读取本从机的寄存器)
{
	//Addr    主机要读的从机地址
	//ReadAdd 主机要读取的寄存器首地址
	//ReadNum 要读取的寄存器个数
	unsigned short int j;
	unsigned short int crc;
	modbus.TXcount=0;
	modbus.sendbuf[modbus.TXcount++]=Addr;//首先填入要读取的从机地址
	modbus.sendbuf[modbus.TXcount++]=0X03;//填入功能码
	modbus.sendbuf[modbus.TXcount++]=ReadAdd/256;//填入要读取的第一个寄存器的高位地址
	modbus.sendbuf[modbus.TXcount++]=ReadAdd%256;//填入要读取的第一个寄存器的低位地址
	modbus.sendbuf[modbus.TXcount++]=ReadNum/256;//填入要读取寄存器数量的高位地址
	modbus.sendbuf[modbus.TXcount++]=ReadNum%256;//填入要读取寄存器数量的低位地址
	crc=crc16(modbus.sendbuf,modbus.TXcount);//计算校验码
	modbus.sendbuf[modbus.TXcount++]=crc/256;//填入校验码
	modbus.sendbuf[modbus.TXcount++]=crc%256;
	
	RS485_1;//将485转为发送模式
	for(j=0;j<modbus.TXcount;j++)
	{
		RS485_Send_Data(modbus.sendbuf[j]);
	}
	RS485_0;//将485转为接收模式
}

void Modbus_fun6(unsigned char Addr,unsigned short int WriteAdd,unsigned short int val)//6号功能码处理
{
	//Addr    主机要写的从机地址
	//WriteAdd 要改写的寄存器地址
	//val      修改后该寄存器的值
	unsigned short int j;
	unsigned short int crc;
	
	modbus.TXcount=0;
	modbus.sendbuf[modbus.TXcount++]=Addr;//填入要改写的从机地址
	modbus.sendbuf[modbus.TXcount++]=0x06;//填入功能码 
	modbus.sendbuf[modbus.TXcount++]=WriteAdd/256;//写入的寄存器的地址
	modbus.sendbuf[modbus.TXcount++]=WriteAdd%256;
	modbus.sendbuf[modbus.TXcount++]=val/256;//写入的值
	modbus.sendbuf[modbus.TXcount++]=val%256;
	crc=crc16(modbus.sendbuf,modbus.TXcount);//计算校验码
	modbus.sendbuf[modbus.TXcount++]=crc/256;//填入校验码
	modbus.sendbuf[modbus.TXcount++]=crc%256;

	RS485_1;//将485转为发送模式
	for(j=0;j<modbus.TXcount;j++)
	{
		RS485_Send_Data(modbus.sendbuf[j]);
	}
	RS485_0;//将485转为接收模式
}
void Modbus_Event()
{
   /* unsigned short int	crc;
	unsigned short int  rccrc;
    if(modbus.reflag==0)//没有收到Modbus的数据包
    {
		return;
	}
	
	crc=crc16(&modbus.rcbuf[0],modbus.recount-2);//从接收缓冲区的第0个地址开始 到接收到的数据个数结束，接受CRC校验
	rccrc=modbus.rcbuf[modbus.recount-2]*256+modbus.rcbuf[modbus.recount-1];//收到的校验码
	if(crc==rccrc)//数据包符号CRC校验规则*/
	{
		ModBus_Display();
	}
	modbus.recount=0;
	modbus.reflag=0;
}
void ModBus_Display(void)
{
	char i =0;
	
	printf("**************************************************\r\n");
	printf("主机已发送的命令为:0x:");	
	for(i=0;i<modbus.TXcount;i++)
	{
		printf(" %02X",modbus.sendbuf[i]);
	}
	printf("\r\n");
	modbus.TXcount=0;
	printf("\r\n");
	printf("主机接收到的回应为:0x:");	
	for(i=0;i<modbus.recount;i++)
	{
		printf(" %02X",modbus.rcbuf[i]);
	}
	printf("\r\n");
	printf("**************************************************\r\n");
	printf("\r\n");	
}


