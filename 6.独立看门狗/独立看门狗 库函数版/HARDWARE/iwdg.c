#include "iwdg.h"
#include "stm32f10x.h"

void iwdg_init()
{
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_64);
	IWDG_SetReload(625);//1s
	IWDG_ReloadCounter();  //Î¹¹·
	IWDG_Enable();
	
}

