#ifndef __TPAD_H__
#define __TPAD_H__
#include "sys.h"

#define TIM_ARR_MAX 0XFFFF
#define TPAD_FLAG 100


void tpad_init(void);
void tpad_tim5ch2_init(u16,u16);
u16 tpad_get_val(void);
u16 tpad_get_maxval(u8);
void tpad_reset(void);
u8 tpad_scan(u8);




#endif


