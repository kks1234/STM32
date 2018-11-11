#ifndef __IIC_H__
#define __IIC_H__
#include "stm32f10x.h"

#define  SDA_READ   ((GPIOB->IDR&(1<<7))!=0)
#define  SDA_0      GPIOB->BRR = 1<<7;
#define  SDA_1      GPIOB->BSRR = 1<<7;
#define  SCL_0      GPIOB->BRR = 1<<6;
#define  SCL_1      GPIOB->BSRR = 1<<6;



void eeprom_write_onebyte(u16 addr, u8 byte);
u8 eeprom_read_onebyte(u16 addr);
void eeprom_wait(void);
void eeprom_write_string(u16 addr, u8* byte, u8 len);
void eeprom_read_string(u16 addr, u8* buf, u8 len);
void eeprom_write_stringpage(u16 addr, u8* byte, u8 len);
	

void iic_delay(void);
void iic_init(void);
void iic_start(void);
void iic_stop(void);
void iic_ack(void);
void iic_nack(void);
void iic_send_byte(u8 byte);
u8   iic_receive_byte(void);
u8   iic_waitack(void);

#endif

