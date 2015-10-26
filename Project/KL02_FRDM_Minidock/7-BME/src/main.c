/************************************************************************
*例程功能：
*   比较实用普通C以及BME方式运行异或语句的执行时间大小。
*   并通过串口9600波特率，打印普通C和BME方式异或语句的systick执行时间
*  串口以9600波特率打印：7-BME demo!。
*************************************************************************/
#include <stdio.h>
#include <string.h>

#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "SysTick.h"

int main(void)
{
   
    /* 开机延时 */
    DelayInit();
    /* UART 初始化 */
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600);
    printf("7-BME demo!\r\n");
 
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
    while(1)
    {
  
    }
}

