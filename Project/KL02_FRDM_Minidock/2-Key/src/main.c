/************************************************************************
*例程功能：
*   实现扩展板上按键控制LD的功能。
* K4控制LD4，K3控制LD3，K2控制LD2，按键按下，相应小灯点亮，松开按键，相应小灯熄灭。K1与reset引脚相连，未做控制。
* 串口以9600波特率打印：2-KEY demo!
*注意K3和FRDM板上MMA8451Q INT2共用,若用扩展板K3按键，需要去掉FRDM板上R26电阻
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
#define KEY2_PORT   HW_GPIOA // 注意此脚和FRDM板上MMA8451Q INT2共用,若用扩展板按键，需要去掉FRDM板上R26电阻
#define KEY2_PIN    10
#define KEY1_PORT   HW_GPIOB  //NMI
#define KEY1_PIN    5
#define KEY0_PORT   HW_GPIOA//RESET
#define KEY0_PIN    11

int main(void)
{

    /* 开机延时 */
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
    /* UART 初始化 */
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600); 
    printf("2-KEY demo!\r\n");
  
    while(1)
    {
        if(GPIO_ReadBit(HW_GPIOA, 12)==0)
              GPIO_WriteBit(LED0_PORT, LED0_PIN, 0);
        else
              GPIO_WriteBit(LED0_PORT, LED0_PIN, 1);
        
        if(GPIO_ReadBit(HW_GPIOA, 10)==0)  // 注意此脚和FRDM板上MMA8451Q INT2共用,若用扩展板按键，需要去掉FRDM板上R26电阻
              GPIO_WriteBit(LED1_PORT, LED1_PIN, 0);
        else
              GPIO_WriteBit(LED1_PORT, LED1_PIN, 1);
        
        if(GPIO_ReadBit(HW_GPIOB, 5)==0)
              GPIO_WriteBit(LED2_PORT, LED2_PIN, 0);
        else
              GPIO_WriteBit(LED2_PORT, LED2_PIN, 1);
        
    }
}



