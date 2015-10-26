/************************************************************************
*例程功能：
*   实现扩展板上外部flashW25P80第一个页256字节的擦写功能，并通过打印这256字节擦前擦后写后的数据
*  外部flash读写完成后，扩展板上LD4闪烁
* 串口以9600波特率打印：5-SPI_FLASH demo!。
*************************************************************************/
#include <stdio.h>
#include <string.h>

#include "gpio.h"
#include "spi.h"
#include "common.h"
#include "uart.h"


#define LED0_PORT   HW_GPIOB
#define LED0_PIN    11
int cmd_spi(int argc, char * const argv[]);

int main(void)
{

    /* 开机延时 */
    DelayInit();
    /* UART 初始化 */
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600); 
    printf("5-SPI_FLASH demo!\r\n");

    /* LED */
    GPIO_QuickInit(LED0_PORT, LED0_PIN, kGPIO_Mode_OPP);
     /* do test */
    cmd_spi(0, NULL);
    while(1)
    {
        GPIO_ToggleBit(LED0_PORT, LED0_PIN);
        DelayMs(500);       
    }
}


