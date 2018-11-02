#ifndef _modbus_
#define _modbus_
typedef struct
{
  unsigned char myadd;//本设备的地址
  unsigned char rcbuf[128];//Modbus接收缓冲区
  unsigned short int timout;//Modbus的数据断续时间
  unsigned char recount;//Modbus端口已经收到的数据个数
  unsigned char TXcount;//Modbus端口已经发送的数据个数
  unsigned char timrun;//Modbus定时器是否计时的标志
  unsigned char reflag;//收到一帧数据的标志
  unsigned char sendbuf[128];//Modbus发送缓冲区
}MODBUS;

extern MODBUS modbus;
void Modbus_Init(void);
void Modbus_Event(void);
void ModBus_Display(void);
void Modbus_fun3(unsigned char Addr,unsigned short int ReadAdd,unsigned short int ReadNum);//3号功能码处理(主机要读取本从机的寄存器)
void Modbus_fun6(unsigned char Addr,unsigned short int WriteAdd,unsigned short int val);//6号功能码处理


#endif

