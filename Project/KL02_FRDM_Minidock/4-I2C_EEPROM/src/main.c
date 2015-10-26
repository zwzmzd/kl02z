/***************************************************************************************************
*例程功能：
*先对24C02进行64字节的连续写操作，然后再通过连续读操作读取写入的64字节，比较前后数据是否一致
***************************************************************************************************/


#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "common.h"
#include "i2c.h"
#include "uart.h"
#include "at24cxx.h"




int cmd_i2c(int argc, char * const argv[])
{
    int ret;
    
    I2C_QuickInit(I2C0_SCL_PB03_SDA_PB04, 576000);

    at24cxx_init(HW_I2C0);
    ret = at24cxx_self_test();
    return ret;
}



int main(void)
{
    int ret;
    /* 开机延时 */
    DelayInit();
    /* UART 初始化 */
    GPIO_QuickInit(HW_GPIOB, 6, kGPIO_Mode_OPP);
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600);
    UART_ITConfig(HW_UART0, kUART_IT_Rx, true);
    
    /* do test */
    printf("4-I2C_EEPORM demo\r\n");
    ret = cmd_i2c(0, NULL);
    
    if(ret)
    {
        printf("EEPOEM test failed\r\n");
    }
    else
    {
        printf("EEPORM test ok!\r\n");
    }
    
    while(1)
    {
        GPIO_ToggleBit(HW_GPIOB, 6);
        DelayMs(500);
    }    
    
}



