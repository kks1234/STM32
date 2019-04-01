/*
 * File      : pipe.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-22     Tanek        first version.
 */

#include <stdio.h>
#include <rtthread.h>

int main(void)
{
	rt_kprintf("hello word!\r\n");
    while(1)
    {
        rt_thread_delay(10 * RT_TICK_PER_SECOND);
    }
}

void aaa(void)
{
    rt_kprintf("bbb\n");
}
MSH_CMD_EXPORT(aaa, print);

