/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-24     Tanek        the first version
 */
#include <rthw.h>
#include <rtthread.h>

#include "Device.h"                     // Keil::Board Support:V2M-MPS2:Common
#include "RTE_Components.h"             // Component selection

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
void *rt_heap_begin_get(void)
{
    extern int Image$$RTT_HEAP$$Base;
    return &Image$$RTT_HEAP$$Base;
}

void *rt_heap_end_get(void)
{
    extern int Image$$RTT_HEAP$$ZI$$Limit;
    return &Image$$RTT_HEAP$$ZI$$Limit;
}
#endif

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init()
{
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / RT_TIMER_TICK_PER_SECOND);    /* Generate interrupt each 10 ms  */

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

void SysTick_Handler (void)
{
	rt_interrupt_enter();

	rt_tick_increase();

	rt_interrupt_leave();
}
