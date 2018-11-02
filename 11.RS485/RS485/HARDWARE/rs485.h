#ifndef __RS485_H__
#define __RS485_H__
#include "sys.h"

#define RS485_T_R PDout(7)


void rs485_init(void);
void rs485_send_data(u8*buf,u8 len);
void rs485_receive_data(u8*buf,u8 *len);


#endif 

