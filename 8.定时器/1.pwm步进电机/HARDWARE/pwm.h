#ifndef __PWM_H__
#define __PWM_H__
#include "stm32f10x.h"

void tim2_init(u16 arr,u16 psc);
void pwm_tim3_init(u16 arr,u16 psc);


#endif

