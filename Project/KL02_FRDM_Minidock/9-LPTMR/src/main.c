/**************************************************************
*例程功能：每100ms翻转Red led以及扩展板上的LD1
****************************************************************/

#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "common.h"
#include "lptmr.h"
#include "uart.h"




static void LPTMR_ISR(void)
{
    static uint32_t i;
    
    i++;
    if(i == 10)
    {
        GPIO_WriteBit(HW_GPIOB, 6, 0);
    }
    else if(i > 20)
    {
        GPIO_WriteBit(HW_GPIOB, 6, 1);
        i=0;
    }
}

int main(void)
{
//    int i, ret;
    /* 开机延时 */
    DelayInit();
    /* UART 初始化 */
        /* GPIO */
    GPIO_QuickInit(HW_GPIOB, 6, kGPIO_Mode_OPP);
    
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600);
    UART_ITConfig(HW_UART0, kUART_IT_Rx, true);
    
    printf("9-lptrm timer counter test\r\n");
    
    LPTMR_TC_InitTypeDef LPTMR_TC_InitStruct1; 
    LPTMR_TC_InitStruct1.timeInMs = 10;
    LPTMR_TC_Init(&LPTMR_TC_InitStruct1);
    
    LPTMR_CallbackInstall(LPTMR_ISR);
    LPTMR_ITDMAConfig(kLPTMR_IT_TOF, true);
    
   
    while(1)
    {
  
    }
}



