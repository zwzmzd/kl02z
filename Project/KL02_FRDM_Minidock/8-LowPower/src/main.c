/************************************************************************
*���̹��ܣ�
*  ����͹���VLPS֮��ͨ��NMI������K2���������ѡ�
* ������9600�����ʴ�ӡ��8-LowPower demo!��
*************************************************************************/
#include <stdio.h>
#include <string.h>

#include "gpio.h"
#include "common.h"
#include "uart.h"


int main(void)
{
    /* ������ʱ */
    DelayInit();
    /* UART ��ʼ�� */
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600);   
    printf("8-LowPower demo!\r\n");

    printf("entering VLPS mode...\r\n");
    printf("press NMI switch (k2) to wake up\r\n");
    
    /* allow VLPS mode */
    SMC->PMPROT |= SMC_PMPROT_AVLP(1);
    
    /* set VLPS mode */
    SMC->PMCTRL &= ~SMC_PMCTRL_STOPM_MASK;
    SMC->PMCTRL |= SMC_PMCTRL_STOPM(2);
    
    DelayMs(10);
    
    /* enter STOP */
    EnterSTOPMode(false);
    printf("wake up from VLPS mode\r\n");
    
    while(1)
    {
  
    }
}

