#include "rtc.h"
#include "stdio.h"
#include "delay.h"
timer  time_struct;
u8 const month_days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
u8 *week_set[7]={ "Sunday" , "Monday" , "Tuesday", "Wednesday" , "Thursday" , "Friday" , "Saturday" };
//初始化RTC
void rtc_init()
{
	u8 t;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE); //使能PWR电源和BKP后备区
	//使能后备寄存器访问
	PWR_BackupAccessCmd(ENABLE);

	if(BKP_ReadBackupRegister(BKP_DR1) != 0x0002)
	{
		BKP_DeInit();
		
		/********少代码**********/ /*已加*/
		RCC_LSEConfig(RCC_LSE_ON);	//设置外部低速晶振(LSE),使用外设低速晶振
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET&&t<250)	//检查指定的RCC标志位设置与否,等待低速晶振就绪
			{
			t++;
			delay_ms(10);
			}
		if(t>=250)return;
		
		//配置RTC时钟源
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForLastTask();
		RTC_WaitForSynchro(); //等待RTC寄存器同步完成
		
		RTC_EnterConfigMode(); //允许配置
		
		RTC_ITConfig(RTC_IT_SEC|RTC_IT_ALR,ENABLE);  //开启闹钟和秒中断
		RTC_WaitForLastTask();
		RTC_SetPrescaler(32767);
		RTC_WaitForLastTask();		
		rtc_set_time(2018,12,1,19,2,30);
		
		RTC_ExitConfigMode(); //关闭配置
		
	}
	else 
	{
		/*******????************/
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_SEC|RTC_IT_ALR,ENABLE);
		RTC_WaitForLastTask();
	}
	
	rtc_nvic_config();
	
	/********少代码*更新时间*******/  /*已加*/
	rtc_updata_time();//更新时间
	BKP_WriteBackupRegister(BKP_DR1,0x0002);
}


//设置中断
void rtc_nvic_config()
{
	
	NVIC_InitTypeDef NVIC_InitTypeStruvt;

	NVIC_InitTypeStruvt.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitTypeStruvt.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeStruvt.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitTypeStruvt.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&NVIC_InitTypeStruvt);
		
}


//设置时间
void rtc_set_time(u16 year,u8 month,u8 day,u8 hour,u8 minute,u8 second)
{
	u32 value = 0;
	u16 i;
	
	if(year<1970 || year>2099)	return ;
	
	for(i=1970 ; i<year ; i++)
	{
		if( rtc_judge_year(i) )
			value += 31622400; //闰年时间（s）
		else
			value += 31536000; //平年时间
	}
	for(i=0 ; i<(month-1) ; i++)
	{
		value += (u32)month_days[i] * 86400;  //每个月对应的时间
		if( rtc_judge_year(year) && i==1)
			value += 86400;
	}
	value += (u32)(day-1)*86400;
	value += (u32)hour*3600;
	value += (u32)minute*60;
	value += second;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE); //使能时钟
	PWR_BackupAccessCmd(ENABLE); //使能后备寄存器访问
	
	RTC_SetCounter(value);
	
	RTC_WaitForLastTask();
	
}

//判断是否为闰年
u8 rtc_judge_year(u16 year)
{
	if(year%4 == 0)
	{
		if(year%100 != 0)
			return 1;
		else if(year%400 == 0)
			return 1;
		else 
			return 0;
	}
	else
		return 0; 
}

//设置闹钟时间
void rtc_alarm_time(u16 year,u8 month,u8 day,u8 hour,u8 minute,u8 second)
{
	u32 value = 0;
	u16 i;
	
	if(year<1970 || year>2099)	return ;
	
	for(i=1970 ; i<year ; i++)
	{
		if( rtc_judge_year(i) )
			value += 31622400; //闰年时间（s）
		else
			value += 31536000; //平年时间
	}
	for(i=0 ; i<(month-1) ; i++)
	{
		value += (u32)month_days[i] * 86400;  //每个月对应的时间
		if( rtc_judge_year(year) && i==1)
			value += 86400;
	}
	value += (u32)(day-1)*86400;
	value += (u32)hour*3600;
	value += (u32)minute*60;
	value += second;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	
	RTC_SetAlarm(value);
	
	RTC_WaitForLastTask();

}
//计算星期
u8 rtc_get_week(u16 year,u8 month,u8 day)
{ 
	 if(month <3)  
	 { 
		month+=   12; 
        --year; 
     } 
	return   (day+1+2*month+3*(month+1)/5+year+(year/4)-year/100+year/400)   %   7; 
}

//时间计算更新
void rtc_updata_time()
{
	static u16 daycnt;
	u32 time_count;
	u32 temp,temp1;
	
	time_count = RTC_GetCounter();
	
	temp = time_count / 86400; //天数
	
	if(temp != daycnt)
	{
		daycnt  = temp ;
		temp1 = 1970;   //从1970年开始
		while(temp >= 365)
		{
			if( rtc_judge_year(temp1) )
			{
				if(temp >= 366) temp -= 366; //闰年的天数
					else
					{
						temp1++; break;
					}
			}
			else
			{
				temp -= 365;
			}
			temp1++;
		}
		time_struct.year = temp1;  //得到年份
		temp1 = 0;
		
		while(temp >= 28)
		{
			if( rtc_judge_year(time_struct.year) && temp1 == 1) 
			{
				if(temp >= 29) temp -= 29;
				else break;
			}
			else
			{
				if( temp >= month_days[temp1]) temp -= month_days[temp1];
				else break;
				
			}
			temp1++;
		}
		time_struct.month = temp1+1;  //得到月份
		time_struct.day = temp+1;    //得到日期
	}
	temp = time_count % 86400 ;  //计算最后一天的时间
	
	time_struct.hour = temp/3600; //时
	time_struct.minute = (temp/60) %60; //分
	time_struct.second = temp % 60; //秒
	time_struct.week = rtc_get_week(time_struct.year,time_struct.month,time_struct.day); //星期
	
}



//中断服务函数
void RTC_IRQHandler (void)
{
	if( RTC_GetITStatus(RTC_IT_SEC) == SET)
	{
		rtc_updata_time(); //更新时间
	}
	if( RTC_GetITStatus(RTC_IT_ALR) == SET)
	{
		printf("Alarm_Set \r\n");
		rtc_updata_time();  //更新时间
	}
	
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_ALR); //Clear bit
	
	RTC_WaitForLastTask();

}





