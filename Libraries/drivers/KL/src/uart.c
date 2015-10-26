
#include "uart.h"
#include "gpio.h"
#include "common.h"

#include <stdio.h>
#define UART_BASES  {UART0}
static const struct reg_ops CLKTbl[] =
{
    {(void*)&(SIM->SCGC4), SIM_SCGC4_UART0_MASK},
};
static const IRQn_Type UART_IRQnTable[] = 
{
    UART0_IRQn,
};
/* gloabl const table defination */
const void* UART_InstanceTable[] = UART_BASES;

/* special use for printf */
static uint8_t UART_DebugInstance;


uint8_t UART_QuickInit(uint32_t MAP, uint32_t baudrate)
{
    uint8_t i;
    uint32_t clock;
    UART_InitTypeDef Init;
    QuickInit_Type * pq = (QuickInit_Type*)&(MAP);
    Init.baudrate = baudrate;
    Init.instance = pq->ip_instance;
    
    /* clock source */
    if(pq->ip_instance == HW_UART0)
    {
        CLOCK_GetClockFrequency(kMCGOutClock, &clock);
        
        #ifdef SIM_SOPT2_UART0SRC_MASK
        /* use PLL/2 or FLL */
        SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
        SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);  
        #endif
        
        #ifdef MCG_C6_PLLS_MASK
        if(MCG->C6 & MCG_C6_PLLS_MASK) /* PLL */
        {
            SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
            clock /= 2;
        }
        else /* FLL */
        {
            SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
        }
        #endif
    }
    else
    {
        CLOCK_GetClockFrequency(kBusClock, &clock);
    }
    Init.srcClock = clock;
    
    /* init pinmux */
    for(i = 0; i < pq->io_offset; i++)
    {
        PORT_PinMuxConfig(pq->io_instance, pq->io_base + i, (PORT_PinMux_Type) pq->mux); 
    }
    
    /* init UART */
    UART_Init(&Init);
    
    return pq->ip_instance;
}

/**
 * @brief  配置UART模块的中断或DMA属性
 * @code
 *      //配置UART0模块开启接收中断功能
 *      UART_ITConfig(HW_UART0, kUART_IT_Rx, true);
 * @endcode
 * @param  instance      :芯片串口端口
 *         @arg HW_UART0 :芯片的UART0端口

 * @param  status      :开关
 * @param  config: 工作模式选择
 *         @arg kUART_IT_Tx:
 *         @arg kUART_IT_Rx:

 * @retval None
 */
void UART_ITConfig(uint32_t instance, UART_ITConfig_Type config, bool status)
{
    IP_CLK_ENABLE(instance);
    
   // UART0_Type * UARTx = (UART0_Type*)UART_InstanceTable[instance];
    
    switch(config)
    {
        case kUART_IT_Tx:
            (status)?
            (UART0->C2 |= UART0_C2_TIE_MASK):
            (UART0->C2 &= ~UART0_C2_TIE_MASK);
            NVIC_EnableIRQ(UART_IRQnTable[instance]);
            break; 
        case kUART_IT_Rx:
            (status)?
            (UART0->C2 |= UART0_C2_RIE_MASK):
            (UART0->C2 &= ~UART0_C2_RIE_MASK);
            NVIC_EnableIRQ(UART_IRQnTable[instance]);
            break;
        default:
            break;
    }
}

void UART_Init(UART_InitTypeDef* Init)
{
    uint16_t sbr;
    static bool is_fitst_init = true;
    
    IP_CLK_ENABLE(Init->instance);
    
    //UART0_Type * UARTx = (UART0_Type*)UART_InstanceTable[Init->instance];
    
    /* disable Tx Rx first */
    UART0->C2 &= ~((UART0_C2_TE_MASK)|(UART0_C2_RE_MASK));
	
    /* disable Tx Rx */
    UART0->C2 &= ~((UART0_C2_TE_MASK)|(UART0_C2_RE_MASK));
    
    /* config baudrate */
    sbr = Init->srcClock/((Init->baudrate)*16);
    UART0->BDH &= ~(UART0_BDH_SBR_MASK);
    UART0->BDH |= (sbr>>8) & UART0_BDH_SBR_MASK;
    UART0->BDL = (sbr & UART0_BDL_SBR_MASK);
    
    /* enable Tx Rx */
    UART0->C2 |= ((UART0_C2_TE_MASK)|(UART0_C2_RE_MASK));
    
    /* link debug instance */
    /* if it's first initalized ,link getc and putc to it */
    if(is_fitst_init)
    {
        UART_DebugInstance = Init->instance;
    }
    is_fitst_init = false;
}



void UART_WriteByte(uint32_t instance, char ch)
{
    UART0_Type * UARTx = (UART0_Type*)UART_InstanceTable[instance];
    while(!(UARTx->S1 & UART0_S1_TDRE_MASK));
    UARTx->D = (uint8_t)ch;
    
}
uint8_t UART_ReadByte(uint32_t instance, uint8_t *ch)
{
  
    UART0_Type * UARTx = (UART0_Type*)UART_InstanceTable[instance];
    
    /* clear OverRun */
    //UARTx->S1 |= UART_S1_OR_MASK;
    
    if(UARTx->S1 & UART0_S1_RDRF_MASK)
    {
        *ch = (uint8_t)(UARTx->D);	
        return 0; 		  
    }

    return 1;
}



#ifdef __CC_ARM // MDK Support
struct __FILE 
{ 
	int handle;
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;
FILE __stdin;
__weak int fputc(int ch,FILE *f)
{
	
	 UART_WriteByte(UART_DebugInstance, ch);
	return ch;
}

__weak int fgetc(FILE *f)
{
     uint8_t ch;
    
	 while(UART_ReadByte(UART_DebugInstance, &ch));
    return (ch & 0xFF);
}

#elif __ICCARM__ /* IAR support */
#include <yfuns.h>
__weak size_t __write(int handle, const unsigned char * buffer, size_t size)
{
    size_t nChars = 0;
    if (buffer == 0)
    {
        /* This means that we should flush internal buffers.  Since we*/
        /* don't we just return.  (Remember, "handle" == -1 means that all*/
        /* handles should be flushed.)*/
        return 0;
    }
    /* This function only writes to "standard out" and "standard err",*/
    /* for all other file handles it returns failure.*/
    if ((handle != _LLIO_STDOUT) && (handle != _LLIO_STDERR))
    {
        return _LLIO_ERROR;
    }
    /* Send data.*/
    while (size--)
    {
       UART_WriteByte(UART_DebugInstance, *buffer++);
        ++nChars;
    }
    return nChars;
}

__weak size_t __read(int handle, unsigned char * buffer, size_t size)
{
    size_t nChars = 0;
    uint8_t ch = 0;
    if (buffer == 0)
    {
        /* This means that we should flush internal buffers.  Since we*/
        /* don't we just return.  (Remember, "handle" == -1 means that all*/
        /* handles should be flushed.)*/
        return 0;
    }
    /* This function only writes to "standard out" and "standard err",*/
    /* for all other file handles it returns failure.*/
    if ((handle != _LLIO_STDIN) && (handle != _LLIO_STDERR))
    {
        return _LLIO_ERROR;
    }
    /* read data.*/
    while (size--)
    {

      while(UART_ReadByte(UART_DebugInstance, &ch));
        *buffer++ = (char)ch & 0xFF;
        ++nChars;
    }
    return nChars;
}
#endif

static void UART_putstr(uint32_t instance, const char *str)
{
    while(*str != '\0')
    {
      UART_WriteByte(instance, *str++);
    }
}

static void printn(unsigned int n, unsigned int b)
{
    static char *ntab = "0123456789ABCDEF";
    unsigned int a, m;
    if (n / b)
    {
        a = n / b;
        printn(a, b);  
    }
    m = n % b;
   
    UART_WriteByte(UART_DebugInstance, ntab[m]);
}

int UART_printf(const char *fmt, ...)
{
    char c;
    unsigned int *adx = (unsigned int*)(void*)&fmt + 1;
_loop:
    while((c = *fmt++) != '%')
    {
        if (c == '\0') return 0;
        UART_WriteByte(UART_DebugInstance, c);
    }
    c = *fmt++;
    if (c == 'd' || c == 'l')
    {
        printn(*adx, 10);
    }
    if (c == 'o' || c == 'x')
    {
        printn(*adx, c=='o'? 8:16 );
    }
    if (c == 's')
    {
      UART_putstr(UART_DebugInstance, (char*)*adx);
    }
    adx++;
    goto _loop;
}
