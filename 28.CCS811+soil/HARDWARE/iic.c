#include "iic.h"
#include "delay.h"
#include "usart.h"
 void I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
		/* ʹ���� I2C�йص�ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_IIC_CLK, ENABLE );  

	 /* PC3-I2C_SCL��PC5-I2C_SDA*/
	GPIO_InitStructure.GPIO_Pin = IIC_GPIO_PIN_SDA| IIC_GPIO_PIN_SCL; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
	GPIO_Init(IIC_GPIO, &GPIO_InitStructure); 
	SCL_H;
	SDA_H;
}
void delay_1us(u8 x)//������ʱ,iic_40K
{
	u8 i=20;
	x=i*x;
	while(x--);
}
////////IIC��ʼ����//////////
/*
IIC��ʼ:��SCL���ڸߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��ɵ͵�ƽ����һ���½��أ�Ȼ��SCL����
*/
u8 I2C_Start(void)
{
		SDA_H; 
		delay_1us(5);	//��ʱ��֤ʱ��Ƶ�ʵ���40K���Ա�ӻ�ʶ��
		SCL_H;
		delay_1us(5);//��ʱ��֤ʱ��Ƶ�ʵ���40K���Ա�ӻ�ʶ��
		if(!SDA_read) return 0;//SDA��Ϊ�͵�ƽ������æ,�˳�
		SDA_L;   //SCL���ڸߵ�ƽ��ʱ��SDA����
		delay_1us(5);
	  if(SDA_read) return 0;//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
		SCL_L;
	  delay_1us(5);
	  return 1;
}
//**************************************
//IICֹͣ�ź�
/*
IICֹͣ:��SCL���ڸߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ɸߵ�ƽ����һ��������
*/
//**************************************
void I2C_Stop(void)
{
    SDA_L;
		SCL_L;
		delay_1us(5);
		SCL_H;
		delay_1us(5);
		SDA_H;//��SCL���ڸߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ɸߵ�ƽ             //��ʱ
}
//**************************************
//IIC����Ӧ���ź�
//��ڲ���:ack (0:ACK 1:NAK)
/*
Ӧ�𣺵��ӻ����յ����ݺ�����������һ���͵�ƽ�ź�
��׼����SDA��ƽ״̬����SCL�ߵ�ƽʱ����������SDA
*/
//**************************************
void I2C_SendACK(u8 i)
{
    if(1==i)
			SDA_H;	             //׼����SDA��ƽ״̬����Ӧ��
    else 
			SDA_L;  						//׼����SDA��ƽ״̬��Ӧ�� 	
	  SCL_H;                    //����ʱ����
    delay_1us(5);                 //��ʱ
    SCL_L ;                  //����ʱ����
    delay_1us(5);    
} 
///////�ȴ��ӻ�Ӧ��////////
/*
������(����)������һ�����ݺ󣬵ȴ��ӻ�Ӧ��
���ͷ�SDA���ôӻ�ʹ�ã�Ȼ��ɼ�SDA״̬
*/
/////////////////
u8 I2C_WaitAck(void) 	 //����Ϊ:=1��ACK,=0��ACK
{
	uint16_t i=0;
	SDA_H;	        //�ͷ�SDA
	SCL_H;         //SCL���߽��в���
	while(SDA_read)//�ȴ�SDA����
	{
		i++;      //�ȴ�����
		if(i==500)//��ʱ����ѭ��
		break;
	}
	if(SDA_read)//�ٴ��ж�SDA�Ƿ�����
	{
		SCL_L; 
		return RESET;//�ӻ�Ӧ��ʧ�ܣ�����0
	}
  delay_1us(5);//��ʱ��֤ʱ��Ƶ�ʵ���40K��
	SCL_L;
	delay_1us(5); //��ʱ��֤ʱ��Ƶ�ʵ���40K��
	return SET;//�ӻ�Ӧ��ɹ�������1
}
//**************************************
//��IIC���߷���һ���ֽ�����
/*
һ���ֽ�8bit,��SCL�͵�ƽʱ��׼����SDA��SCL�ߵ�ƽʱ���ӻ�����SDA
*/
//**************************************
void I2C_SendByte(u8 dat)
{
  u8 i;
	SCL_L;//SCL���ͣ���SDA׼��
  for (i=0; i<8; i++)         //8λ������
  {
		if(dat&0x80)//SDA׼��
		SDA_H;  
		else 
		SDA_L;
    SCL_H;                //����ʱ�ӣ����ӻ�����
    delay_1us(5);        //��ʱ����IICʱ��Ƶ�ʣ�Ҳ�Ǹ��ӻ������г���ʱ��
    SCL_L;                //����ʱ�ӣ���SDA׼��
    delay_1us(5); 		  //��ʱ����IICʱ��Ƶ��
		dat <<= 1;          //�Ƴ����ݵ����λ  
  }					 
}
//**************************************
//��IIC���߽���һ���ֽ�����
//**************************************
u8 I2C_RecvByte()
{
    u8 i;
    u8 dat = 0;
    SDA_H;//�ͷ�SDA�����ӻ�ʹ��
    delay_1us(1);         //��ʱ���ӻ�׼��SDAʱ��            
    for (i=0; i<8; i++)         //8λ������
    { 
		  dat <<= 1;
			
      SCL_H;                //����ʱ���ߣ������ӻ�SDA
     
		  if(SDA_read) //������    
		   dat |=0x01;      
       delay_1us(5);     //��ʱ����IICʱ��Ƶ��		
       SCL_L;           //����ʱ���ߣ��������յ�������
       delay_1us(5);   //��ʱ���ӻ�׼��SDAʱ��
    } 
    return dat;
}
