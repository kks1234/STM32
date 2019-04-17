#include "ccs811.h"


u8 BUF[12];
u8 Information[10];
u8 temp=0x5a;
u8 MeasureMode,Status,Error_ID;

ccs811_measurement_t CCS;


u8 CCS811_WriteReg(u8 reg_add, u8 reg_dat)
{
	if(I2C_Start()==0)  //起始信号
		{I2C_Stop(); return RESET;}           

    I2C_SendByte(CCS811_Add);   //发送设备地址+写信号
 	  if(!I2C_WaitAck()){I2C_Stop(); return RESET;}
   
		I2C_SendByte(reg_add);    //内部寄存器地址，
 	  if(!I2C_WaitAck()){I2C_Stop(); return RESET;}
   
		I2C_SendByte(reg_dat);       //内部寄存器数据，
	  if(!I2C_WaitAck()){I2C_Stop(); return RESET;}
		
		I2C_Stop();   //发送停止信号
		
		return SET;
}

u8 CCS811_Write_SomeReg(u8 reg_add, u8* reg_dat,u16 length)
{
  if(I2C_Start()==0)  //起始信号
		{I2C_Stop(); return RESET;}           

    I2C_SendByte(CCS811_Add);   //发送设备地址+写信号
 	  if(!I2C_WaitAck()){I2C_Stop(); return RESET;}
   
		I2C_SendByte(reg_add);    //内部寄存器地址，
 	  if(!I2C_WaitAck()){I2C_Stop(); return RESET;}
   
	while(length)
	{
		I2C_SendByte(*reg_dat++);       //内部寄存器数据，
	   if(!I2C_WaitAck()){I2C_Stop(); return RESET;}           //应答
		length--;
	}
	//	I2C_SendByte(*data);       //内部寄存器数据，
 	//	if(!I2C_WaitAck()){I2C_Stop(); return RESET;}
		I2C_Stop();   //发送停止信号		
		return SET;
}

u8 CCS811_ReadReg(u8 reg_add, u8 * read, u8 num)
{
 if(I2C_Start()==0)  //起始信号
		{I2C_Stop(); return RESET;}          
	 
	I2C_SendByte(CCS811_Add);    //发送设备地址+写信号
 	if(!I2C_WaitAck()){I2C_Stop(); return RESET;} 
	
	I2C_SendByte(reg_add);     //发送存储单元地址
 	if(!I2C_WaitAck()){I2C_Stop(); return RESET;} 
	
	if(I2C_Start()==0)  //起始信号
			{I2C_Stop(); return RESET;}            

	I2C_SendByte(CCS811_Add+1);  //发送设备地址+读信号
 	if(!I2C_WaitAck()){I2C_Stop(); return RESET;}
	
	while(num-1)
	{
		*read++=I2C_RecvByte();       //读出寄存器数据
		I2C_SendACK(0);               //应答
		num--;
	}
	*read=I2C_RecvByte();  
	I2C_SendACK(1);     //发送停止传输信号
	I2C_Stop();                    //停止信号
	return SET;
}






void CCS811_Init(void)
{
	
	delay_ms(10);
	CCS811_ReadReg(0x20,Information,1);  //Read CCS's information  ,ID
    CCS811_ReadReg(0x23,&Information[1],2);	//FW_Boot_Version  
	CCS811_ReadReg(0x24,&Information[3],2); 	//FW_App_Version
  	CCS811_ReadReg(0x00,&Status,1);	   //Firstly the status register is read and the APP_VALID flag is checked.
	if(Status&0x10)	 CCS811_Write_SomeReg(0xF4,&temp,0);	//Used to transition the CCS811 state from boot to application mode, a write with no data is required.
	CCS811_ReadReg(0x00,&Status,1);
	CCS811_ReadReg(0x01,&MeasureMode,1);
    CCS811_WriteReg(0x01,0x10); //Write Measure Mode Register,sensor measurement every second,no interrupt
	delay_ms(10);
		
}


void CCS811_Getval()
{
	CCS811_ReadReg(0x00,&Status,1);
	CCS811_ReadReg(0xE0,&Error_ID,1);
	CCS811_ReadReg(0x02,BUF,8);
	CCS811_ReadReg(0x20,Information,1);  //Read CCS's information  ,ID

	CCS.eco2= (u16)BUF[0]*256+BUF[1];
	CCS.tvoc= (u16)BUF[2]*256+BUF[3];
	
}










