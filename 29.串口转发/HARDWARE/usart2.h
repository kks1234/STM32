#ifndef __USART2_H__
#define __USART2_H__


#include "stm32f10x.h"

struct buf {
	u8 num_buf;
	u8 recv_buf[100];
};
typedef struct buf RECV_BUF;

void usrt2_init(void);

u8 rt_hw_interrupt_disable(void);
void rt_hw_interrupt_enable(u8 level);



#endif




