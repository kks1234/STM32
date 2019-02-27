#ifndef __CAN_H__
#define __CAN_H__

#include "stm32f10x.h"


#define DATA_MAX     8
#define CAN_Rx_INT_ENABLE      0


void Can_Init(void);
void Can_SendMessages(u8 * p, u8 len);
u8 Can_ReceiveMessages(u8 * p);







#endif   /* __CAN_H__ */



