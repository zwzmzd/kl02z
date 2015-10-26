/************************************************************************
*���̹��ܣ�
*   �Ƚ�ʵ����ͨC�Լ�BME��ʽ�����������ִ��ʱ���С��
*   ��ͨ������9600�����ʣ���ӡ��ͨC��BME��ʽ�������systickִ��ʱ��
*  ������9600�����ʴ�ӡ��7-BME demo!��
*************************************************************************/
#include <stdio.h>
#include <string.h>

#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "SysTick.h"

int main(void)
{
   
    /* ������ʱ */
    DelayInit();
    /* UART ��ʼ�� */
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

