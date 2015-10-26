#include <stdio.h>
#include "adc.h"
#include "common.h"
#include "uart.h"

int cmd_adc(int argc, char * const argv[])
{
    int i;
    uint32_t val;
    ADC_QuickInit(ADC0_SE11A_PB08, kADC_SingleDiff12or13); 
    
    
    for(i=0;i<10;i++)
    {
        val = ADC_QuickReadValue(ADC0_SE11A_PB08);
        printf("ADC0_SE11A_PB08:%d\r\n", val);
        DelayMs(200);
    }
    return 0;
}

