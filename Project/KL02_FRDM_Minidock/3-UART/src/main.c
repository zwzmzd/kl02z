/************************************************************************
*例程功能：
*   实现串口以9600bps波特率打印CPU信息及其flash信息，另外可实现接收中断并返回接收字符
*************************************************************************/
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "uart.h"


void flash_identify (void);
void cpu_identify (void);
/********************************************************************/
/*!
 * \brief   Kinetis L Family Identify
 * \return  None
 *
 * This is primarly a reporting function that displays information
 * about the specific CPU to the default terminal including:
 * - Kinetis family
 * - package
 * - die revision
 * - P-flash size
 * - Ram size
 */
void cpu_identify (void)
{
  uint16 temp;
    /* Determine the Kinetis family */
    switch((SIM_SDID & SIM_SDID_FAMID(0x7))>>SIM_SDID_FAMID_SHIFT) 
    {  
    	case 0x0:
    		printf("\n\rKL0");
    		break;
    	case 0x1:
    		printf("\n\rKL1");
    		break;
    	case 0x2:
    		printf("\n\rKL2");
    		break;
    	case 0x3:
    		printf("\n\rKL3");
    		break;
    	case 0x4:
    		printf("\n\rKL4");
    		break;
	default:
		printf("\n\rUnrecognized Kinetis family device.\n\r");  
		break;  	
    }
    
    /* Determine Sub-Family ID */
    switch((SIM_SDID & SIM_SDID_SUBFAMID(0x7))>>SIM_SDID_SUBFAMID_SHIFT) 
    { 
        case 0x2:
    		printf("2");
    		break;
    	case 0x4:
    		printf("4");
    		break;
    	case 0x5:
    		printf("5");
    		break;
    	case 0x6:
    		printf("6");
    		break;
    	case 0x7:
    		printf("7");
    		break;                
	default:
		printf("\n\rUnrecognized Kinetis sub-family device.\n\r");  
		break;  	
    }
    
    /* Determine the package size */
    switch((SIM_SDID & SIM_SDID_PINID(0xF))>>SIM_SDID_PINID_SHIFT) 
    {  
    	case 0x0:
    		printf("16pin       ");
    		break;
    	case 0x1:
    		printf("24pin       ");
    		break;
    	case 0x2:
    		printf("32pin      ");
    		break;
    	case 0x4:
    		printf("48pin      ");
    		break;
    	case 0x5:
    		printf("64pin      ");
        case 0x6:
    		printf("80pin      ");
        case 0x8:
    		printf("100pin      ");        
    		break;
	default:
		printf("\n\rUnrecognized Kinetis package code.      ");  
		break;  	
    }
    
    /* Determine Attribute ID */
    switch((SIM_SDID & SIM_SDID_SERIESID(0x7))>>SIM_SDID_SERIESID_SHIFT) 
    {  
    	case 0x1:
    		printf("\n\rLow Power Line with Cortex M0+\n\r\n\r");
    		break;
	default:
		printf("\n\rUnrecognized Kinetis family attribute.\n\r");  
		break;  	
    }
    
    /* Determine the System SRAM Size */
    switch((SIM_SDID & SIM_SDID_SRAMSIZE(0x7))>>SIM_SDID_SRAMSIZE_SHIFT) 
    {  
    	case 0x0:
          printf("SRAM Size: 0.5 KB\n\r");
    		break;
        case 0x1:
          printf("SRAM Size:  1 KB\n\r");
          break;
        case 0x2:
          printf("SRAM Size:  2 KB\n\r");
          break;
        case 0x3:
          printf("SRAM Size:  4 KB\n\r");
          break;
        case 0x4:
          printf("SRAM Size:  8 KB\n\r");
          break;
        case 0x5:
          printf("SRAM Size:  16 KB\n\r");
          break;
        case 0x6:
          printf("SRAM Size:  32 KB\n\r");
          break;
        case 0x7:
          printf("SRAM Size:  64 KB\n\r");
          break;
	default:
		printf("\n\rUnrecognized SRAM Size.\n\r");  
		break;  	
    }                

    /* Determine the revision ID */
    temp = ((SIM_SDID_REVID(0xF))>>SIM_SDID_REVID_SHIFT);
    printf("Silicon rev %d\n\r ", temp);
    
    /* Determine the flash revision */
    flash_identify();    
    
    /* Determine the P-flash size */
  switch((SIM_FCFG1 & SIM_FCFG1_PFSIZE(0xF))>>SIM_FCFG1_PFSIZE_SHIFT)
    {
  	case 0x0:
    		printf("Flash size:  8 KB program flash, 0.25 KB protection region");
    		break;
    	case 0x1:
    		printf("Flash size:  16 KB program flash, 0.5 KB protection region	");
    		break;
        case 0x3:
    		printf("Flash size:  32 KB program flash, 1 KB protection region	");
    		break;
    	case 0x5:
    		printf("Flash size:  64 KB program flash, 2 KB protection region	");
    		break;
        case 0x7:
    		printf("Flash size:  128 KB program flash, 4 KB protection region	");
    		break;
        case 0x9:
    		printf("Flash size:  256 KB program flash, 4 KB protection region	");
    		break;
        case 0xF:
    		printf("Flash size:  128 KB program flash, 4 KB protection region	");
    		break;
	default:
		printf("ERR!! Undefined flash size\n\r");  
		break;  	  		
    }
}
/********************************************************************/
/*!
 * \brief   flash Identify
 * \return  None
 *
 * This is primarly a reporting function that displays information
 * about the specific flash parameters and flash version ID for 
 * the current device. These parameters are obtained using a special
 * flash command call "read resource." The first four bytes returned
 * are the flash parameter revision, and the second four bytes are
 * the flash version ID.
 */
void flash_identify (void)
{
    /* Get the flash parameter version */

    /* Write the flash FCCOB registers with the values for a read resource command */
    FTFA_FCCOB0 = 0x03;
    FTFA_FCCOB1 = 0x00;
    FTFA_FCCOB2 = 0x00;
    FTFA_FCCOB3 = 0x00;
    FTFA_FCCOB8 = 0x01;

    /* All required FCCOBx registers are written, so launch the command */
    FTFA_FSTAT = FTFA_FSTAT_CCIF_MASK;

    /* Wait for the command to complete */
    while(!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK));
    
    printf("Flash parameter version %d ",FTFA_FCCOB4);
    printf(" %d ",FTFA_FCCOB5);
    printf(" %d ",FTFA_FCCOB6);
    printf(" %d\n\r",FTFA_FCCOB7);

    /* Get the flash version ID */   

    /* Write the flash FCCOB registers with the values for a read resource command */
    FTFA_FCCOB0 = 0x03;
    FTFA_FCCOB1 = 0x00;
    FTFA_FCCOB2 = 0x00;
    FTFA_FCCOB3 = 0x04;
    FTFA_FCCOB8 = 0x01;

    /* All required FCCOBx registers are written, so launch the command */
    FTFA_FSTAT = FTFA_FSTAT_CCIF_MASK;

    /* Wait for the command to complete */
    while(!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK));

    printf("Flash version ID %d ",FTFA_FCCOB4);  
    printf(" %d",FTFA_FCCOB5);  
    printf(" %d ",FTFA_FCCOB6);  
    printf("%d\n\r",FTFA_FCCOB7);  
}

inline void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void qsort(int nums[], int a, int b)
{
	int low = a, high = b;
	while (low < high) {
		while (low < high && nums[low] < nums[high])
			low++;
		if (low < high)
            swap(&nums[low], &nums[high]);
        while (low < high && nums[low] < nums[high])
			high--;
		if (low < high)
            swap(&nums[low], &nums[high]);
	}
    if (a < low-1) qsort(nums, a, low-1);
    if (high + 1 < b) qsort(nums, high + 1, b);
}

void custom() 
{
    printf("\n\r");
    uint32_t freq;
    
    printf("CPU frequency\n\r");
    CLOCK_GetClockFrequency(kCoreClock, &freq);
    printf("kCoreClock: %d hz\n\r", freq);
    
    CLOCK_GetClockFrequency(kSystemClock, &freq);
    printf("kSystemClock: %d hz\n\r", freq);
    
    CLOCK_GetClockFrequency(kBusClock, &freq);
    printf("kBusClock: %d hz\n\r", freq);
    
    CLOCK_GetClockFrequency(kFlashClock, &freq);
    printf("kFlashClock: %d hz\n\r", freq);
    
    CLOCK_GetClockFrequency(kMCGOutClock, &freq);
    printf("kMCGOutClock: %d hz\n\r", freq);
    
    CLOCK_GetClockFrequency(kClockNameCount, &freq);
    printf("kClockNameCount: %d hz\n\r", freq);
}
int main(void)
{

    /* 开机延时 */
    DelayInit();
    /* UART 初始化 */
    UART_QuickInit(UART0_RX_B2_TX_B1, 9600);
    UART_ITConfig(HW_UART0, kUART_IT_Rx, true);
    
    printf("3-UART demo!\r\n");
    /* do test */
    cpu_identify ();
	custom();
    while(1)
    {		
    }
}
/**
 * @brief  UART0 中断服务函数
 * @param  None
 * @retval None
 */
void UART0_IRQHandler(void)
{
    uint8_t ch;
    UART_ReadByte(HW_UART0, &ch);
    printf("\n%c", ch);
}

