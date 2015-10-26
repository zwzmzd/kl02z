#ifndef __CH_LIB_KL_COMMON_H__
#define __CH_LIB_KL_COMMON_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#ifdef LIB_DEBUG
#include <stdio.h>
#endif

#ifdef MKL25Z4
#include "MKL25Z4.h"
#elif MKL27Z4
#include "MKL27Z4.h"
#elif MKL28Z7
#include "MKL28Z7.h"
#elif  MKL26Z4
#include "MKL26Z4.h"
#elif  MKL02Z4
#include "MKL02Z4.h"
#elif  MKL03Z4
#include "MKL03Z4.h"
#elif  MKL46Z4
#include "MKL46Z4.h"
#elif  MKL43Z4
#include "MKL43Z4.h"
#else
#error "No CPU defined!"

#endif


/* means you can use printf via UART */
#define UART_USE_STDIO

/* version information */
#define CHK_VERSION                   2L              //!< major version number
#define CHK_SUBVERSION                6L              //!< minor version number
#define CHK_REVISION                  0L              //!< revise version number

/* CH_Kinetis version */
#define FW_VERSION                ((CHK_VERSION * 10000) + \
                                  (CHK_SUBVERSION * 100) + CHK_REVISION)

  
#if defined(LIB_DEBUG)
#define LIB_TRACE	printf
#else
#define LIB_TRACE(...)
#endif


#define NVIC_PriorityGroup_0         ((uint32_t)0x7) /*!< 0 bits for pre-emption priority   4 bits for subpriority */                                               
#define NVIC_PriorityGroup_1         ((uint32_t)0x6) /*!< 1 bits for pre-emption priority   3 bits for subpriority */                                                  
#define NVIC_PriorityGroup_2         ((uint32_t)0x5) /*!< 2 bits for pre-emption priority   2 bits for subpriority */                                                   
#define NVIC_PriorityGroup_3         ((uint32_t)0x4) /*!< 3 bits for pre-emption priority   1 bits for subpriority */                                                   
#define NVIC_PriorityGroup_4         ((uint32_t)0x3) /*!< 4 bits for pre-emption priority   0 bits for subpriority */

#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#define ABS(a)         (((a) < 0) ? (-(a)) : (a))
#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))

#define BSWAP_16(x)     (uint16_t)((((x) & 0xFF00) >> 0x8) | (((x) & 0xFF) << 0x8))
#define BSWAP_32(val)	(uint32_t)((BSWAP_16((uint32_t)(val) & (uint32_t)0xFFFF) << 0x10) |  \
                                   (BSWAP_16((uint32_t)((val) >> 0x10))))


/* QuickInitType */
typedef struct
{
    uint32_t ip_instance:3;
    uint32_t io_instance:3;
    uint32_t mux:3;
    uint32_t io_base:5;
    uint32_t io_offset:5;
    uint32_t channel:5;
    uint32_t reserved:8;
}QuickInit_Type;

/* clock */
typedef enum
{
    kCoreClock,
    kSystemClock,
    kBusClock,
    kFlashClock,
    kMCGOutClock,
    kClockNameCount,
}CLOCK_Source_Type; 

struct reg_ops
{
    void *      addr;
    uint32_t    mask;
};

#define BME_AND_MASK  (1<<26)
#define BME_OR_MASK   (1<<27)
#define BME_XOR_MASK  (3<<26)
#define BME_BFI_MASK(BIT,WIDTH)   (1<<28) | (BIT<<23) | ((WIDTH-1)<<19)
#define BME_UBFX_MASK(BIT,WIDTH)  (1<<28) | (BIT<<23) | ((WIDTH-1)<<19)

/* Decorated Store: Logical AND */
#define BME_AND8(addr, wdata) (*(volatile uint8_t*)((uintptr_t)addr | BME_AND_MASK) = wdata)
#define BME_AND16(addr, wdata) (*(volatile uint16_t*)((uintptr_t)addr | BME_AND_MASK) = wdata)
#define BME_AND32(addr, wdata) (*(volatile uint32_t*)((uintptr_t)addr | BME_AND_MASK) = wdata)

/* Decorated Store: Logical OR */
#define BME_OR8(addr, wdata) (*(volatile uint8_t*)((uintptr_t)addr | BME_OR_MASK) = wdata)
#define BME_OR16(addr, wdata) (*(volatile uint16_t*)((uintptr_t)addr | BME_OR_MASK) = wdata)
#define BME_OR32(addr, wdata) (*(volatile uint32_t*)((uintptr_t)addr | BME_OR_MASK) = wdata)

/* Decorated Store: Logical XOR */
#define BME_XOR8(addr, wdata) (*(volatile uint8_t*)((uintptr_t)addr | BME_XOR_MASK) = wdata)
#define BME_XOR16(addr, wdata) (*(volatile uint8_t*)((uintptr_t)addr | BME_XOR_MASK) = wdata)
#define BME_XOR32(addr, wdata) (*(volatile uint8_t*)((uintptr_t)addr | BME_XOR_MASK) = wdata)

#define IP_CLK_ENABLE(x)        (*((uint32_t*) CLKTbl[x].addr) |= CLKTbl[x].mask)
#define IP_CLK_DISABLE(x)       (*((uint32_t*) CLKTbl[x].addr) &= ~CLKTbl[x].mask)

typedef unsigned char		uint8;  /*  8 bits */
typedef unsigned short int	uint16; /* 16 bits */
typedef unsigned long int	uint32; /* 32 bits */

typedef char			int8;   /*  8 bits */
typedef short int	        int16;  /* 16 bits */
typedef int		        int32;  /* 32 bits */

typedef volatile int8		vint8;  /*  8 bits */
typedef volatile int16		vint16; /* 16 bits */
typedef volatile int32		vint32; /* 32 bits */

typedef volatile uint8		vuint8;  /*  8 bits */
typedef volatile uint16		vuint16; /* 16 bits */
typedef volatile uint32		vuint32; /* 32 bits */


//!< API functions
#define EnableInterrupts()   __enable_irq()
#define DisableInterrupts()  __disable_irq()
#define SystemSoftReset    NVIC_SystemReset
uint32_t QuickInitEncode(QuickInit_Type * type);
void QuickInitDecode(uint32_t map, QuickInit_Type* type);
void DelayMs(uint32_t ms);
void DelayUs(uint32_t ms);
void DelayInit(void);
int32_t CLOCK_GetClockFrequency(CLOCK_Source_Type clockName, uint32_t* FrequenctInHz);
void EnterSTOPMode(bool enSleepOnExit);
#endif
