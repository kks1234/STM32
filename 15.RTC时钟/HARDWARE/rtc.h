#ifndef __RTC_H__
#define __RTC_H__
#include "stm32f10x.h"


//时间结构体
typedef struct {
	vu16 year;
	vu8 month;
	vu8 day;
	vu8 week;
	vu8 hour;
	vu8 minute;
	vu8 second;
	
}timer;


void rtc_init(void);
void rtc_nvic_config(void);
void rtc_updata_time(void);
void rtc_set_time(u16 year,u8 month,u8 day,u8 hour,u8 minute,u8 second);
void rtc_alarm_time(u16 year,u8 month,u8 day,u8 hour,u8 minute,u8 second);
u8 rtc_get_week(u16 year,u8 month,u8 day);
u8 rtc_judge_year(u16 year);



#endif







