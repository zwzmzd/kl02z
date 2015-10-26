#ifndef __CH_LIB_KL_UART_H__
#define __CH_LIB_KL_UART_H__

#include <stdint.h>
#include <stdbool.h>
#include "MKL02Z4.h"


/*!< UART 硬件模块号 */
#define     HW_UART0           (0x00U)
/*!< UART 快速初始化宏 */ 
/***************************************
                                offset io_base  mux io_instance ip_instance
*0X00008288U= 0b 00000000 00000 00010   00001    010    001         000
                                2个io   PTB1    MUX2    PTB       UART0
即同时配置PTA6，PTA7 SPI0， 引脚MUX为3
***************************************/
#define     UART0_RX_B2_TX_B1   (0x00008288U)


/*!< 中断及DMA配置 */
typedef enum
{
    kUART_IT_Tx,                // 开启每发送一帧传输完成中断 
    kUART_IT_Rx,                // 开启每接收一帧传输完成中断 
}UART_ITConfig_Type;



/*!< UART初始化结构 */
typedef struct
{
    uint32_t                srcClock;       // 时钟源频率
    uint8_t                 instance;       // UART 模块号 HW_UART0~HW_UART5
    uint32_t                baudrate;       // UART 波特率 
}UART_InitTypeDef;

/*!< UART 回调函数声明 */
typedef void (*UART_CallBackTxType)(uint16_t * pbyteToSend);
typedef void (*UART_CallBackRxType)(uint16_t byteReceived);

static void UART_putstr(uint32_t instance, const char *str);
static void printn(unsigned int n, unsigned int b);
int UART_printf(const char *fmt, ...);
void UART_WriteByte(uint32_t instance, char ch);
uint8_t UART_ReadByte(uint32_t instance, uint8_t *ch);

/* Interrupt functions */
void UART_ITConfig(uint32_t instance, UART_ITConfig_Type config, bool status);
void UART_Init(UART_InitTypeDef* Init);
uint8_t UART_QuickInit(uint32_t MAP, uint32_t baudrate);
void UART_CallbackTxInstall(uint32_t instance, UART_CallBackTxType AppCBFun);
void UART_CallbackRxInstall(uint32_t instance, UART_CallBackRxType AppCBFun);


	
#endif


