#include <stdio.h>

#include "gpio.h"
#include "common.h"
#include "uart.h"

int cmd_low_power(int argc, char * const argv[])
{
    
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

    return 0;
}

