//****************************
//例程功能：
//PTA5输出周期恒定（1Khz）,占空比循环变化的PWM
//***************************

#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "tpm.h"
#include "common.h"
#include "uart.h"



int main(void)
{
//    int i, ret;
    int duty=0;
    /* 开机延时 */
    DelayInit();
    /* UART 初始化 */
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600);
    UART_ITConfig(HW_UART0, kUART_IT_Rx, true);
    
    printf("10-PWM test, please measure waveform in PTA05\r\n");
    /* do test */
    
    TPM_PWM_QuickInit(TPM0_CH1_PA05, kPWM_EdgeAligned, 1000);
    
    while(1)
    {
        
        duty%=10000;
        TPM_PWM_ChangeDuty(HW_TPM0, kTPM_IT_CH1, duty++);
        DelayMs(1);
    }
    
}


