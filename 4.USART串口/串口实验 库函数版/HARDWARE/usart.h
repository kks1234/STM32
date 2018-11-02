#ifndef __USART_H__
#define __USART_H__
#include "stm32f10x.h"
extern u8  USART_RX_BUF[200];
extern u16 USART_RX_STA; //½ÓÊÕ×´Ì¬


void usart_init(void);

#endif

