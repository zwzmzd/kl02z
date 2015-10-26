#include "gpio.h"
#include "common.h"
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
#define KEY2_PORT   HW_GPIOA
#define KEY2_PIN    10
#define KEY1_PORT   HW_GPIOB
#define KEY1_PIN    5
#define KEY0_PORT   HW_GPIOA
#define KEY0_PIN    11

int cmd_gpio(int argc, char * const argv[])
{
    int i;
    /* LED */
    GPIO_QuickInit(LED0_PORT, LED0_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED1_PORT, LED1_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED2_PORT, LED2_PIN, kGPIO_Mode_OPP);
    GPIO_QuickInit(LED3_PORT, LED3_PIN, kGPIO_Mode_OPP);
    /* KEY */
    GPIO_QuickInit(KEY0_PORT, KEY0_PIN, kGPIO_Mode_IPU);
    GPIO_QuickInit(KEY1_PORT, KEY1_PIN, kGPIO_Mode_IPU);  //NMI
    GPIO_QuickInit(KEY2_PORT, KEY2_PIN, kGPIO_Mode_IPU);
    GPIO_QuickInit(KEY3_PORT, KEY3_PIN, kGPIO_Mode_IPU);

    PORTA_PCR12 |= PORT_PCR_IRQC(0x0b) |  PORT_PCR_PFE_MASK;
    NVIC_EnableIRQ(PORTA_IRQn); // 开启PORTA中断
    EnableInterrupts() ;          //开启总中断
    
    for(i=0;i<10;i++)
    {
        GPIO_ToggleBit(LED0_PORT, LED0_PIN);
        GPIO_ToggleBit(LED1_PORT, LED1_PIN);
        GPIO_ToggleBit(LED2_PORT, LED2_PIN);
        GPIO_ToggleBit(LED3_PORT, LED3_PIN);
        DelayMs(500);  
    }
    return 0;
}

