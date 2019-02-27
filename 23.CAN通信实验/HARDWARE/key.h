#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"


#define  KEY_WKUP    ((GPIOA->IDR) & (0x0001<<0))


void key_init(void);
u8 key_scan(u8 mode);









#endif


