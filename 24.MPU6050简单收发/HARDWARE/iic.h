#ifndef __IIC_H__
#define __IIC_H__


#include "stm32f10x.h"


/* IIC 1 */
#define    SDA1_0         ( (GPIOC->BRR) = GPIO_Pin_0 )
#define    SDA1_1         ( (GPIOC->BSRR) = GPIO_Pin_0 )
#define    SCL1_0         ( (GPIOC->BRR) = GPIO_Pin_1 )
#define    SCL1_1         ( (GPIOC->BSRR) = GPIO_Pin_1 )
#define    R_SDA1         ( (GPIOC->IDR) & GPIO_Pin_0 )

/* IIC 2 */
#define    SDA2_0         ( (GPIOC->BRR) = GPIO_Pin_2 )
#define    SDA2_1         ( (GPIOC->BSRR) = GPIO_Pin_2 )
#define    SCL2_0         ( (GPIOC->BRR) = GPIO_Pin_3 )
#define    SCL2_1         ( (GPIOC->BSRR) = GPIO_Pin_3 ) 
#define    R_SDA2         ( (GPIOC->IDR) & GPIO_Pin_2 )

/* IIC 3 */
#define    SDA3_0         ( (GPIOC->BRR) = GPIO_Pin_4 )
#define    SDA3_1         ( (GPIOC->BSRR) = GPIO_Pin_4 )
#define    SCL3_0         ( (GPIOC->BRR) = GPIO_Pin_5 )
#define    SCL3_1         ( (GPIOC->BSRR) = GPIO_Pin_5 )
#define    R_SDA3         ( (GPIOC->IDR) & GPIO_Pin_4 )

/* IIC 4 */
#define    SDA4_0         ( (GPIOC->BRR) = GPIO_Pin_6 )
#define    SDA4_1         ( (GPIOC->BSRR) = GPIO_Pin_6 )
#define    SCL4_0         ( (GPIOC->BRR) = GPIO_Pin_7 )
#define    SCL4_1         ( (GPIOC->BSRR) = GPIO_Pin_7 )
#define    R_SDA4         ( (GPIOC->IDR) & GPIO_Pin_6 )






void IIC_Gpio_Config_Init(void);

void IIC_Delay(void);

/* IIC 1 */
void iic1_start(void);
void iic1_stop(void);
void iic1_ack(void);
void iic1_nack(void);
u8 iic1_wait_ack(void);

void iic1_write_byte(u8 byte);
u8 iic1_read_byte(u8 ack);


/* IIC 2 */
void iic2_start(void);
void iic2_stop(void);
void iic2_ack(void);
void iic2_nack(void);
u8 iic2_wait_ack(void);

void iic2_write_byte(u8 byte);
u8 iic2_read_byte(u8 ack);


/* IIC 3 */
void iic3_start(void);
void iic3_stop(void);
void iic3_ack(void);
void iic3_nack(void);
u8 iic3_wait_ack(void);

void iic3_write_byte(u8 byte);
u8 iic3_read_byte(u8 ack);


/* IIC 4 */
void iic4_start(void);
void iic4_stop(void);
void iic4_ack(void);
void iic4_nack(void);
u8 iic4_wait_ack(void);

void iic4_write_byte(u8 byte);
u8 iic4_read_byte(u8 ack);







#endif  /* __IIC_H__ */

















