/************************************************************************
*���̹��ܣ�
*   ʵ����չ�����ⲿflashW25P80��һ��ҳ256�ֽڵĲ�д���ܣ���ͨ����ӡ��256�ֽڲ�ǰ����д�������
*  �ⲿflash��д��ɺ���չ����LD4��˸
* ������9600�����ʴ�ӡ��5-SPI_FLASH demo!��
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

    /* ������ʱ */
    DelayInit();
    /* UART ��ʼ�� */
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


