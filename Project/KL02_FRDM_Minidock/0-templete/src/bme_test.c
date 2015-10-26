#include <stdio.h>

#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "SysTick.h"

int cmd_bme(int argc, char * const argv[])
{
    uint32_t tick;

    systick_disable();
    systick_cnt_init();
    tick = SysTick->VAL;
    GPIOA->PDOR ^= 0x04;
    tick = tick - SysTick->VAL;
    printf("C XOR take:%d ticks\r\n", tick);
    systick_disable();

    systick_cnt_init();
    tick = SysTick->VAL;
    BME_XOR32(&GPIOA->PDOR, 0x04);
    tick = tick - SysTick->VAL;
    printf("BME XOR take:%d ticks\r\n", tick);
    systick_disable();
    
    return 0;
}

