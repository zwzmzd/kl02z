/***************************************************************************************************
*���̹��ܣ�
*�ȶ�24C02����64�ֽڵ�����д������Ȼ����ͨ��������������ȡд���64�ֽڣ��Ƚ�ǰ�������Ƿ�һ��
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
    /* ������ʱ */
    DelayInit();
    /* UART ��ʼ�� */
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



