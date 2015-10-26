/************************************************************************
*���̹��ܣ�
*   ʵ����չ���ϰ�������LD�Ĺ��ܡ�
* K4����LD4��K3����LD3��K2����LD2���������£���ӦС�Ƶ������ɿ���������ӦС��Ϩ��K1��reset����������δ�����ơ�
* ������9600�����ʴ�ӡ��2-KEY demo!
*ע��K3��FRDM����MMA8451Q INT2����,������չ��K3��������Ҫȥ��FRDM����R26����
*************************************************************************/
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

/* KEY pin */
#define KEY3_PORT   HW_GPIOA
#define KEY3_PIN    12
#define KEY2_PORT   HW_GPIOA // ע��˽ź�FRDM����MMA8451Q INT2����,������չ�尴������Ҫȥ��FRDM����R26����
#define KEY2_PIN    10
#define KEY1_PORT   HW_GPIOB  //NMI
#define KEY1_PIN    5
#define KEY0_PORT   HW_GPIOA//RESET
#define KEY0_PIN    11

int main(void)
{

    /* ������ʱ */
    DelayInit();
    /* LED */
    GPIO_QuickInit(LED0_PORT, LED0_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED1_PORT, LED1_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED2_PORT, LED2_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED3_PORT, LED3_PIN, kGPIO_Mode_OPP);
    /* KEY */
  // GPIO_QuickInit(KEY0_PORT, KEY0_PIN, kGPIO_Mode_IPU);// reset
    GPIO_QuickInit(KEY1_PORT, KEY1_PIN, kGPIO_Mode_IPU);  //NMI
    GPIO_QuickInit(KEY2_PORT, KEY2_PIN, kGPIO_Mode_IPU); //kGPIO_Mode_IFT
    GPIO_QuickInit(KEY3_PORT, KEY3_PIN, kGPIO_Mode_IPU);
    /* UART ��ʼ�� */
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600); 
    printf("2-KEY demo!\r\n");
  
    while(1)
    {
        if(GPIO_ReadBit(HW_GPIOA, 12)==0)
              GPIO_WriteBit(LED0_PORT, LED0_PIN, 0);
        else
              GPIO_WriteBit(LED0_PORT, LED0_PIN, 1);
        
        if(GPIO_ReadBit(HW_GPIOA, 10)==0)  // ע��˽ź�FRDM����MMA8451Q INT2����,������չ�尴������Ҫȥ��FRDM����R26����
              GPIO_WriteBit(LED1_PORT, LED1_PIN, 0);
        else
              GPIO_WriteBit(LED1_PORT, LED1_PIN, 1);
        
        if(GPIO_ReadBit(HW_GPIOB, 5)==0)
              GPIO_WriteBit(LED2_PORT, LED2_PIN, 0);
        else
              GPIO_WriteBit(LED2_PORT, LED2_PIN, 1);
        
    }
}



