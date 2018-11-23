#ifndef  __SPI_FLASH_H__
#define  __SPI_FLASH_H__
#include "stm32f10x.h"
#include "stdio.h"




#define Flash_Write_COM               0X02
#define Flash_Read_COM                0X03
#define Flash_Status                  0X05
#define Flash_Write_Enable            0X06
#define Sector_Erase                  0X20
#define ID_COM                        0X9F
#define DUMMY                         0X00
#define time_out                      0XFFFE



#define FLASH_ERROR(fmt,arg...)       printf("<<FLASHERROR>>"fmt"\n",##arg)
#define NSS_High                      GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define NSS_Low                       GPIO_ResetBits(GPIOB,GPIO_Pin_12)


void spi_init(void);  //spi2 init

u8 flash_write_byte(u8 data);
u8 flash_read_byte(void);
u8 spi_check_timeout(void);
u32 flash_read_id(void);
void flash_sector_erase(u32 addr);
void flash_wait_writewait(void);
void flash_read_buf(u32 addr , u8* buf , u32 num_read);
void flash_write_buf(u32 addr , u8* buf ,u32 num_write);
void flash_write_anybuf(u32 addr , u8* buf ,u32 num_write);
void flash_write_enable(void);



#endif






