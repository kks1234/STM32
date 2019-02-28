#include "mpu6050.h"
#include <stdio.h>

/*****************   MPU6050  1 ************************/

void MPU1_WriteReg(u8 reg_add, u8 reg_dat)
{
	iic1_start();
	iic1_write_byte(MPU6050_SLAVE_ADDRESS);
	iic1_wait_ack();
	iic1_write_byte(reg_add);
	iic1_wait_ack();
	iic1_write_byte(reg_dat);
	iic1_wait_ack();
	iic1_stop();
}



void MPU1_ReadReg(u8 reg_add, u8 * read, u8 num)
{
	u8 i;
	iic1_start();
	iic1_write_byte(MPU6050_SLAVE_ADDRESS);
	iic1_wait_ack();
	iic1_write_byte(reg_add);
	iic1_wait_ack();
	iic1_start();
	iic1_write_byte(MPU6050_SLAVE_ADDRESS+1);
	iic1_wait_ack();
	
	for(i=0; i<(num-1); i++)
	{
		read[i] = iic1_read_byte(1);
	}
	read[i] = iic1_read_byte(0);
	
	iic1_stop();
}



void MPU1_Init()
{
	MPU1_WriteReg(MPU6050_RA_PWR_MGMT_1,0x80); //复位MPU6050
	delay_ms(100);
	MPU1_WriteReg(MPU6050_RA_PWR_MGMT_1,0x00); //唤醒MPU6050
	MPU1_WriteReg(MPU6050_RA_SMPLRT_DIV,0x13);  //采样频率 50hz   1000/50 -1  = 19  =0x13
	MPU1_WriteReg(MPU6050_RA_CONFIG,0x04);  //设置陀螺仪的输出频率 1 k
	MPU1_WriteReg(MPU6050_RA_GYRO_CONFIG,0x18);  //陀螺仪传感器,±2000dps
	MPU1_WriteReg(MPU6050_RA_ACCEL_CONFIG,0x00);  //配置加速度传感器工作在2G模式，不自检

}


void MPU1_Read_Acc(short * Accdata)
{
	u8 data[6];
	
	MPU1_ReadReg(MPU6050_ACC_OUT,data,6);
	
	Accdata[0] = (u16)(data[0] << 8)|(u16)data[1];
	Accdata[1] = (u16)(data[2] << 8)|(u16)data[3];
	Accdata[2] = (u16)(data[4] << 8)|(u16)data[5];

}

/*
u8 MPU6050ReadID(void)
{
	unsigned char Re = 0;
    MPU1_ReadReg(MPU6050_RA_WHO_AM_I,&Re,1);    //读器件地址
	if(Re != 0x68)
	{
		printf("MPU6050 dectected error!\r\n检测不到MPU6050模块，请检查模块与开发板的接线");
		return 0;
	}
	else
	{
		printf("MPU6050 ID = %d\r\n",Re);
		return 1;
	}
		
}*/



/*****************   MPU6050  2 ************************/



void MPU2_WriteReg(u8 reg_add, u8 reg_dat)
{
	iic2_start();
	iic2_write_byte(MPU6050_SLAVE_ADDRESS);
	iic2_wait_ack();
	iic2_write_byte(reg_add);
	iic2_wait_ack();
	iic2_write_byte(reg_dat);
	iic2_wait_ack();
	iic2_stop();
}



void MPU2_ReadReg(u8 reg_add, u8 * read, u8 num)
{
	u8 i;
	iic2_start();
	iic2_write_byte(MPU6050_SLAVE_ADDRESS);
	iic2_wait_ack();
	iic2_write_byte(reg_add);
	iic2_wait_ack();
	iic2_start();
	iic2_write_byte(MPU6050_SLAVE_ADDRESS+1);
	iic2_wait_ack();
	
	for(i=0; i<(num-1); i++)
	{
		read[i] = iic2_read_byte(1);
	}
	read[i] = iic2_read_byte(0);
	
	iic2_stop();
}



void MPU2_Init()
{
	MPU2_WriteReg(MPU6050_RA_PWR_MGMT_1,0x80); //复位MPU6050
	delay_ms(100);
	MPU2_WriteReg(MPU6050_RA_PWR_MGMT_1,0x00); //唤醒MPU6050
	MPU2_WriteReg(MPU6050_RA_SMPLRT_DIV,0x13);  //采样频率 50hz   1000/50 -1  = 19  =0x13
	MPU2_WriteReg(MPU6050_RA_CONFIG,0x04);  //设置陀螺仪的输出频率 1 k
	MPU2_WriteReg(MPU6050_RA_GYRO_CONFIG,0x18);  //陀螺仪传感器,±2000dps
	MPU2_WriteReg(MPU6050_RA_ACCEL_CONFIG,0x00);  //配置加速度传感器工作在2G模式，不自检

}


void MPU2_Read_Acc(short * Accdata)
{
	u8 data[6];
	
	MPU2_ReadReg(MPU6050_ACC_OUT,data,6);
	
	Accdata[0] = (u16)(data[0] << 8)|(u16)data[1];
	Accdata[1] = (u16)(data[2] << 8)|(u16)data[3];
	Accdata[2] = (u16)(data[4] << 8)|(u16)data[5];

}





/*****************   MPU6050  3 ************************/







void MPU3_WriteReg(u8 reg_add, u8 reg_dat)
{
	iic3_start();
	iic3_write_byte(MPU6050_SLAVE_ADDRESS);
	iic3_wait_ack();
	iic3_write_byte(reg_add);
	iic3_wait_ack();
	iic3_write_byte(reg_dat);
	iic3_wait_ack();
	iic3_stop();
}



void MPU3_ReadReg(u8 reg_add, u8 * read, u8 num)
{
	u8 i;
	iic3_start();
	iic3_write_byte(MPU6050_SLAVE_ADDRESS);
	iic3_wait_ack();
	iic3_write_byte(reg_add);
	iic3_wait_ack();
	iic3_start();
	iic3_write_byte(MPU6050_SLAVE_ADDRESS+1);
	iic3_wait_ack();
	
	for(i=0; i<(num-1); i++)
	{
		read[i] = iic3_read_byte(1);
	}
	read[i] = iic3_read_byte(0);
	
	iic3_stop();
}



void MPU3_Init()
{
	MPU3_WriteReg(MPU6050_RA_PWR_MGMT_1,0x80); //复位MPU6050
	delay_ms(100);
	MPU3_WriteReg(MPU6050_RA_PWR_MGMT_1,0x00); //唤醒MPU6050
	MPU3_WriteReg(MPU6050_RA_SMPLRT_DIV,0x13);  //采样频率 50hz   1000/50 -1  = 19  =0x13
	MPU3_WriteReg(MPU6050_RA_CONFIG,0x04);  //设置陀螺仪的输出频率 1 k
	MPU3_WriteReg(MPU6050_RA_GYRO_CONFIG,0x18);  //陀螺仪传感器,±2000dps
	MPU3_WriteReg(MPU6050_RA_ACCEL_CONFIG,0x00);  //配置加速度传感器工作在2G模式，不自检

}


void MPU3_Read_Acc(short * Accdata)
{
	u8 data[6];
	
	MPU3_ReadReg(MPU6050_ACC_OUT,data,6);
	
	Accdata[0] = (u16)(data[0] << 8)|(u16)data[1];
	Accdata[1] = (u16)(data[2] << 8)|(u16)data[3];
	Accdata[2] = (u16)(data[4] << 8)|(u16)data[5];

}










/*****************   MPU6050  4 ************************/



void MPU4_WriteReg(u8 reg_add, u8 reg_dat)
{
	iic4_start();
	iic4_write_byte(MPU6050_SLAVE_ADDRESS);
	iic4_wait_ack();
	iic4_write_byte(reg_add);
	iic4_wait_ack();
	iic4_write_byte(reg_dat);
	iic4_wait_ack();
	iic4_stop();
}



void MPU4_ReadReg(u8 reg_add, u8 * read, u8 num)
{
	u8 i;
	iic4_start();
	iic4_write_byte(MPU6050_SLAVE_ADDRESS);
	iic4_wait_ack();
	iic4_write_byte(reg_add);
	iic4_wait_ack();
	iic4_start();
	iic4_write_byte(MPU6050_SLAVE_ADDRESS+1);
	iic4_wait_ack();
	
	for(i=0; i<(num-1); i++)
	{
		read[i] = iic4_read_byte(1);
	}
	read[i] = iic4_read_byte(0);
	
	iic4_stop();
}



void MPU4_Init()
{
	MPU4_WriteReg(MPU6050_RA_PWR_MGMT_1,0x80); //复位MPU6050
	delay_ms(100);
	MPU4_WriteReg(MPU6050_RA_PWR_MGMT_1,0x00); //唤醒MPU6050
	MPU4_WriteReg(MPU6050_RA_SMPLRT_DIV,0x13);  //采样频率 50hz   1000/50 -1  = 19  =0x13
	MPU4_WriteReg(MPU6050_RA_CONFIG,0x04);  //设置陀螺仪的输出频率 1 k
	MPU4_WriteReg(MPU6050_RA_GYRO_CONFIG,0x18);  //陀螺仪传感器,±2000dps
	MPU4_WriteReg(MPU6050_RA_ACCEL_CONFIG,0x00);  //配置加速度传感器工作在2G模式，不自检

}


void MPU4_Read_Acc(short * Accdata)
{
	u8 data[6];
	
	MPU4_ReadReg(MPU6050_ACC_OUT,data,6);
	
	Accdata[0] = (u16)(data[0] << 8)|(u16)data[1];
	Accdata[1] = (u16)(data[2] << 8)|(u16)data[3];
	Accdata[2] = (u16)(data[4] << 8)|(u16)data[5];

}









