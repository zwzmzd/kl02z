/*************************************************
*例程功能：
*   全功能例程，可以实现Low power, LED, ADC,SPI,I2C以及BME模块的功能，模块代码实现顺序如下：
*1，low power, 进入VLPS模式，可以通过板上K2按键唤醒，唤醒后进入下一个功能
*2，LED，实现扩展板上四个LED的闪烁
*3，ADC，实现板上RV1电位器电压的采集，并通过串口打印
*4，SPI，实现扩展板上外部SPIflash W25P80芯片的读擦写，并将数据打印出来。
*5，I2C，实现扩展板上外部I2C EEPROM的读写
*6，BME，实现普通C代码以及BME 异或功能的执行时间比较
最后程序停止。
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
    /* 开机延时 */
    DelayInit();
    /* UART 初始化 */
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

