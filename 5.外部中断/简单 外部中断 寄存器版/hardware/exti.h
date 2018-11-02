#ifndef __EXTI_H__
#define __EXTI_H__
#include "stm32f10x.h"
#define Pin (u8)(1<<4)
#define KEY0 ((GPIOE->IDR&Pin)?(1):(0))


void exti_init(void);
void key_init(void);


#endif

