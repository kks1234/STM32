#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"

#define KEY0 ((GPIOE->IDR)&(1<<4)?(1):(0))    //PE4

void key_init(void);

u8 key_scan(u8);

#endif 

