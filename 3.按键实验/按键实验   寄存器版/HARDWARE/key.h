#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"

#define k0 (1<<4) //GPIO E
#define k1 (1<<3)
#define k2 (1<<2)
#define wp (1<<0) //GPIO  A

#define LED0 ((GPIOE->IDR&k0)?(1):(0))
#define LED1 ((GPIOE->IDR&k1)?(1):(0))
#define LED2 ((GPIOE->IDR&k2)?(1):(0))
#define WEP ((GPIOA->IDR&wp)?(1):(0))


u8 keyscan(u8);

void key_init(void);



#endif

