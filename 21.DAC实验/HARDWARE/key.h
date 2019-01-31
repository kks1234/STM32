#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"

#define WEKUP ( (GPIOA->IDR) & (0x0001<<0) )

void Key_Init(void);

u8 Key_Scan(u8 mode);


#endif




