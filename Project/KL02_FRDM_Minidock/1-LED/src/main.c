/*************************************************
*例程功能：
*   实现扩展板上LD1-LD4 4个小灯的同时闪烁，并通过串口以9600波特率打印：1-LED demo hello world!。
**************************************************/
#include <stdio.h>
#include <string.h>

#include "gpio.h"
#include "common.h"
#include "uart.h"

/* LED pin */
#define LED0_PORT   HW_GPIOB
#define LED0_PIN    11
#define LED1_PORT   HW_GPIOB
#define LED1_PIN    10
#define LED2_PORT   HW_GPIOB
#define LED2_PIN    7
#define LED3_PORT   HW_GPIOB
#define LED3_PIN    6

int main(void)
{

    /* 开机延时 */
    DelayInit();
    /* LED */
    GPIO_QuickInit(LED0_PORT, LED0_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED1_PORT, LED1_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED2_PORT, LED2_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED3_PORT, LED3_PIN, kGPIO_Mode_OPP);    
    /* UART 初始化 */
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600);
    printf("1-LED demo hello world!\r\n");

    while(1)
    {
        GPIO_ToggleBit(LED0_PORT, LED0_PIN);
        GPIO_ToggleBit(LED1_PORT, LED1_PIN);
        GPIO_ToggleBit(LED2_PORT, LED2_PIN);
        GPIO_ToggleBit(LED3_PORT, LED3_PIN);
        DelayMs(500);    
    }
}

