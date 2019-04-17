#ifndef __CCS811_H__
#define __CCS811_H__


#include "iic.h"
#include "delay.h"
#include "stm32f10x.h"


typedef struct {
u16 eco2;
u16 tvoc;
u8 status;
u8 error_id;
u16 raw_data;
} ccs811_measurement_t;


#define CCS811_Add  (0x5A<<1)
#define STATUS_REG 0x00
#define MEAS_MODE_REG 0x01
#define ALG_RESULT_DATA 0x02
#define ENV_DATA 0x05
#define NTC_REG 0x06
#define THRESHOLDS 0x10
#define BASELINE 0x11
#define HW_ID_REG 0x20
#define ERROR_ID_REG 0xE0
#define APP_START_REG 0xF4
#define SW_RESET 0xFF
#define CCS_811_ADDRESS 0x5A
#define GPIO_WAKE 0x5
#define DRIVE_MODE_IDLE 0x0
#define DRIVE_MODE_1SEC 0x10
#define DRIVE_MODE_10SEC 0x20
#define DRIVE_MODE_60SEC 0x30
#define INTERRUPT_DRIVEN 0x8
#define THRESHOLDS_ENABLED 0x4




void CCS811_Init(void);
void CCS811_Getval(void);
u8 CCS811_WriteReg(u8 reg_add, u8 reg_dat);
u8 CCS811_Write_SomeReg(u8 reg_add, u8* reg_dat,u16 length);
u8 CCS811_ReadReg(u8 reg_add, u8 * read, u8 num);









#endif




