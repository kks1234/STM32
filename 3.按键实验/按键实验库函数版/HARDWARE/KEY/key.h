#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"
#define key0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define key1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define key2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define key_up   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

#define k1 1
#define k2 2
#define k3 3
#define k4 4
void key_init(void);
u8 key_scan(u8 mode);

#endif




