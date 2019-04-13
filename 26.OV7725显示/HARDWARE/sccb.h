#ifndef __SCCB_H__
#define __SCCB_H__

#include "sys.h"
#include "stm32f10x.h"

#define SDA_OUT()   {GPIOG->CRH &= 0xFF0FFFFF;GPIOG->CRH |= 0x00300000;}
#define SDA_IN()    {GPIOG->CRH &= 0xFF0FFFFF;GPIOG->CRH |= 0x00400000;}


#define SCCB_SDAIN   (((GPIOG->IDR)&(1<<13)) != 0)
#define SCCB_SDA_L    GPIOG->BRR  = (1<<13)
#define SCCB_SDA_H    GPIOG->BSRR = (1<<13)


#define SCCB_SCL_L    GPIOD->BRR  = (1<<3)
#define SCCB_SCL_H    GPIOD->BSRR = (1<<3)




#define OV_ID 0x42

void sccb_init(void);
void sccb_start(void);
u8 wait_ack(void);
void sccb_stop(void);
void sccb_ack(void);
void sccb_nack(void);
void sccb_write(u8 data);
u8 sccb_read(void);






#endif






