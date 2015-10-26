/*************************************************
*���̹��ܣ�
*   ȫ�������̣�����ʵ��Low power, LED, ADC,SPI,I2C�Լ�BMEģ��Ĺ��ܣ�ģ�����ʵ��˳�����£�
*1��low power, ����VLPSģʽ������ͨ������K2�������ѣ����Ѻ������һ������
*2��LED��ʵ����չ�����ĸ�LED����˸
*3��ADC��ʵ�ְ���RV1��λ����ѹ�Ĳɼ�����ͨ�����ڴ�ӡ
*4��SPI��ʵ����չ�����ⲿSPIflash W25P80оƬ�Ķ���д���������ݴ�ӡ������
*5��I2C��ʵ����չ�����ⲿI2C EEPROM�Ķ�д
*6��BME��ʵ����ͨC�����Լ�BME ����ܵ�ִ��ʱ��Ƚ�
������ֹͣ��
**************************************************/
#include <stdio.h>
#include <string.h>

#include "gpio.h"
#include "spi.h"
#include "common.h"
#include "i2c.h"
#include "uart.h"

#include "w25qxx.h"



struct cmd_t
{
    char		*name;
    uint8_t		maxargs;
    int         (*cmd)(int argc, char * const argv[]);
    char		*help;
};
    



int cmd_gpio(int argc, char * const argv[]);
int cmd_spi(int argc, char * const argv[]);
int cmd_adc(int argc, char * const argv[]);
int cmd_i2c(int argc, char * const argv[]);
int cmd_low_power(int argc, char * const argv[]);
int cmd_bme(int argc, char * const argv[]);
static struct cmd_t cmd[]=
{
    "LOW_POWER", 5, cmd_low_power,      "do low power test",    
    "LED",       5, cmd_gpio,           "do led test",
    "ADC",       5, cmd_adc,            "do adc test",
    "SPI",       5, cmd_spi,            "do spi test", 
    "I2C",       5, cmd_i2c,            "do i2c test",
    "BME",       5, cmd_bme,            "do bme test",   
    "LOOP",      5, NULL,               "do loop test",
};

int main(void)
{
    int i, ret;
    /* ������ʱ */
    DelayInit();
    /* UART ��ʼ�� */
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600);
    UART_ITConfig(HW_UART0, kUART_IT_Rx, true);
    
    printf("HelloWorld!\r\n");
    /* do test */
    for(i=0; i<ARRAY_SIZE(cmd); i++)
    {
        printf("processing %s cmd...\r\n", cmd[i].name);
        if(cmd[i].cmd)
        {
            ret = cmd[i].cmd(0, NULL);
            if(ret)
            {
                printf("failed!\r\n");
            }
            else
            {
                printf("ok!\r\n");
            }  
        }
        else
        {
            printf("no entry!\r\n");
        }
    }
    
    while(1)
    {
  
    }
}

void UART0_IRQHandler(void)
{
    uint8_t ch;
    UART_ReadByte(HW_UART0, &ch);
    printf("%c", ch);
}

