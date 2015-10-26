#ifndef __CH_LIB_KL_UART_H__
#define __CH_LIB_KL_UART_H__

#include <stdint.h>
#include <stdbool.h>
#include "MKL02Z4.h"


/*!< UART Ӳ��ģ��� */
#define     HW_UART0           (0x00U)
/*!< UART ���ٳ�ʼ���� */ 
/***************************************
                                offset io_base  mux io_instance ip_instance
*0X00008288U= 0b 00000000 00000 00010   00001    010    001         000
                                2��io   PTB1    MUX2    PTB       UART0
��ͬʱ����PTA6��PTA7 SPI0�� ����MUXΪ3
***************************************/
#define     UART0_RX_B2_TX_B1   (0x00008288U)


/*!< �жϼ�DMA���� */
typedef enum
{
    kUART_IT_Tx,                // ����ÿ����һ֡��������ж� 
    kUART_IT_Rx,                // ����ÿ����һ֡��������ж� 
}UART_ITConfig_Type;



/*!< UART��ʼ���ṹ */
typedef struct
{
    uint32_t                srcClock;       // ʱ��ԴƵ��
    uint8_t                 instance;       // UART ģ��� HW_UART0~HW_UART5
    uint32_t                baudrate;       // UART ������ 
}UART_InitTypeDef;

/*!< UART �ص��������� */
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


