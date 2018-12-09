#ifndef __WKUP_H__

#define __WKUP_H__

#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"

#define WKUP  PAin(0)    //#define WKUP   (GPIOA->IDR)&0x0001  


void  Wkup_Init(void);

u8 Wkup_Keydelay(void);

void Wkup_Standby(void);



#endif




