/*************************************************
*���̹��ܣ�
*   ͨ��ADC�ɼ���չ����RV1��λ����ֵ����ͨ��ֵ�������ư���LD1-4�Ƶ�������ת��λ��������ʵ�ֲ�ͬλ��С�Ƶ���
*  ��ͨ��������9600�����ʴ�ӡ��λ��ADCֵ���Լ�������Ϣ6-ADC with LED flashing demo!��
**************************************************/
#include <stdio.h>
#include <string.h>

#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "adc.h"

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
    int value;
    /* ������ʱ */
    DelayInit();
    /* LED */
    GPIO_QuickInit(LED0_PORT, LED0_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED1_PORT, LED1_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED2_PORT, LED2_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED3_PORT, LED3_PIN, kGPIO_Mode_OPP);    
    /* UART ��ʼ�� */
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600);  
    printf("6-ADC with LED flashing demo!\r\n");//
    ADC_QuickInit(ADC0_SE11A_PB08, kADC_SingleDiff12or13); 

   
    while(1)
    {
        value = ADC_QuickReadValue(ADC0_SE11A_PB08);
        printf("ADC0_SE11A_PB08:%d\r\n", value);
        DelayMs(200); 
        if(value<=1000)
          {   
                  GPIO_WriteBit(LED0_PORT, LED0_PIN, 1);   
                  GPIO_WriteBit(LED1_PORT, LED1_PIN, 1);        
                  GPIO_WriteBit(LED2_PORT, LED2_PIN, 1);
                  GPIO_WriteBit(LED3_PORT, LED3_PIN, 0);
          }
        else if(value<=2000){
                  GPIO_WriteBit(LED0_PORT, LED0_PIN, 1);   
                  GPIO_WriteBit(LED1_PORT, LED1_PIN, 1);        
                  GPIO_WriteBit(LED2_PORT, LED2_PIN, 0);
                  GPIO_WriteBit(LED3_PORT, LED3_PIN, 1);
          
          }
         else if(value<=3000){
                  GPIO_WriteBit(LED0_PORT, LED0_PIN, 1);   
                  GPIO_WriteBit(LED1_PORT, LED1_PIN, 0);        
                  GPIO_WriteBit(LED2_PORT, LED2_PIN, 1);
                  GPIO_WriteBit(LED3_PORT, LED3_PIN, 1);
          
          }
         else if(value>3000){
                  GPIO_WriteBit(LED0_PORT, LED0_PIN, 0);   
                  GPIO_WriteBit(LED1_PORT, LED1_PIN, 1);        
                  GPIO_WriteBit(LED2_PORT, LED2_PIN, 1);
                  GPIO_WriteBit(LED3_PORT, LED3_PIN, 1);
          
          }
    }
    
}


