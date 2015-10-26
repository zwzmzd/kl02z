#include <string.h>
#include "common.h"
#include "systick.h"


#define MCGOUT_TO_CORE_DIVIDER           (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK)>>SIM_CLKDIV1_OUTDIV1_SHIFT) + 1)
#define MCGOUT_TO_SYSTEM_DIVIDER         (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK)>>SIM_CLKDIV1_OUTDIV1_SHIFT) + 1)
#define MCGOUT_TO_BUS_DIVIDER            (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT) + 1)
#define MCGOUT_TO_PERIPHERAL_DIVIDER     (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK)>>SIM_CLKDIV1_OUTDIV2_SHIFT) + 1)
#define MCGOUT_TO_FLASH_DIVIDER          (((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT) + 1)

void EnterSTOPMode(bool enSleepOnExit)
{
    /* Set the SLEEPDEEP bit to enable deep sleep mode (STOP) */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    if (enSleepOnExit)
    {
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }
    else
    {
        SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
    }
    
    /* WFI instruction will start entry into STOP mode */
    __ASM("WFI");
}
 /**
 * @brief  Get clock frequecy
 * @code
 * 
 *         uint32_t BusClock;
 *         CLOCK_GetClockFrequency(kBusClock, &BusClock);
 *
 *         printf("BusClock:%dHz\r\n", BusClock);
 * @endcode
 * @param  clockName:
 *         @arg kCoreClock
 *         @arg kSystemClock
 *         @arg kBusClock
 *         @arg kFlexBusClock
 *         @arg kFlashClock
 * @param  FrequenctInHz:
 * @retval 0: Succ 1:Error
 */
int32_t CLOCK_GetClockFrequency(CLOCK_Source_Type clockName, uint32_t* FrequenctInHz)
{
    uint32_t MCGOutClock = 0;
    /* calualte MCGOutClock system_MKxxx.c must not modified */
    MCGOutClock = SystemCoreClock * MCGOUT_TO_CORE_DIVIDER;
    switch (clockName)
    {
        case kCoreClock:
            *FrequenctInHz = MCGOutClock / MCGOUT_TO_CORE_DIVIDER;
            break;
        case kSystemClock:
            *FrequenctInHz = MCGOutClock / MCGOUT_TO_SYSTEM_DIVIDER;
            break;	
        case kBusClock:
            *FrequenctInHz = SystemCoreClock / MCGOUT_TO_BUS_DIVIDER;
            break;
        case kFlashClock:
            *FrequenctInHz = SystemCoreClock / MCGOUT_TO_FLASH_DIVIDER;	
            break;
        case kMCGOutClock:
            *FrequenctInHz = MCGOutClock;
            break;
        default:
            return 1;
    }
    return 0;
}


uint32_t QuickInitEncode(QuickInit_Type * type)
{
    return *(uint32_t*)type;
}


void QuickInitDecode(uint32_t map, QuickInit_Type * type)
{
    QuickInit_Type * pMap = (QuickInit_Type*)&(map);
    memcpy(type, pMap, sizeof(QuickInit_Type));  
}

/**
 * @brief  Systick Init
 * @param  None
 * @retval None
 */
#pragma weak DelayInit
void DelayInit(void)
{
    SYSTICK_DelayInit();
}

/**
 * @brief DelayMs
 * @param  ms :
 * @retval None
 */

#pragma weak DelayMs
void DelayMs(uint32_t ms)
{
    SYSTICK_DelayMs(ms);
}

/**
 * @brief DelayUs
 * @param  us :
 * @retval None
 */
#pragma weak DelayUs
void DelayUs(uint32_t us)
{
    SYSTICK_DelayUs(us);
}

void NMI_Handler(void)
{
    
}

/*
    for(i=0;i<ARRAY_SIZE(I2C_QuickInitTable);i++)
    {
        printf("(0X%08XU)\r\n", QuickInitEncode(&I2C_QuickInitTable[i]));
    }
*/

