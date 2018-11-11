#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "stm32f10x.h"

#define  TIMEOUT  1000

void eeprom_write_byte(u16 addr, u8 byte);
void eeprom_read_str(u16 addr, u8 *byte, u16 number);
void eeprom_write_page(u16 addr, u8 len, u8 * bufer);
void eeprom_wait(void);

#endif



