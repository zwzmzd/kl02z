#ifndef __CH_LIB_KL_GPIO_H__
#define __CH_LIB_KL_GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "common.h"
#include <stdint.h>

/* GPIO instance define */
#define HW_GPIOA  (0x00U)
#define HW_GPIOB  (0x01U)

/* PinMux */
typedef enum
{
    kPinAlt0,
    kPinAlt1,
    kPinAlt2,
    kPinAlt3,
    kPinAlt4,
    kPinAlt5,
    kPinAlt6,
    kPinAlt7,
}PORT_PinMux_Type;

typedef enum
{
    kPullDisabled,
    kPullUp,
    kPullDown,
}PORT_Pull_Type;


typedef enum
{
    kGPIO_Mode_IFT = 0x00,       /* Input floating  */
    kGPIO_Mode_IPD = 0x01,       /* Pull down input */
    kGPIO_Mode_IPU = 0x02,       /* Pull up input    */
    kGPIO_Mode_OPP = 0x04,       /* Push pull output */
}GPIO_Mode_Type;

/* �˿��������ģʽѡ�� */
typedef enum
{
    kInput,
    kOutput,
}GPIO_PinConfig_Type;

/*!< Interrupts and DMA */
typedef enum
{
    kGPIO_DMA_RisingEdge,	      //�����ش���DMA
    kGPIO_DMA_FallingEdge,        //�½��ش���DMA
    kGPIO_DMA_RisingFallingEdge,  //�����غ��½��ش���DMA
    kGPIO_IT_Low,                 //�͵�ƽ�����ж�
    kGPIO_IT_RisingEdge,          //�����ش����ж�
    kGPIO_IT_FallingEdge,         //�½��ش����ж�
    kGPIO_IT_RisingFallingEdge,   //�����غ��½��ش����ж�
    kGPIO_IT_High,                //�ߵ�ƽ�����ж�
}GPIO_ITDMAConfig_Type;


typedef struct
{
    uint8_t                instance;    //���Ŷ˿�HW_GPIOA~HW_GPIOB
    GPIO_Mode_Type         mode;        //����ģʽ
    uint32_t               pinx;        //���ź�0~31
}GPIO_InitTypeDef;

/* �˿��жϻص��������� */
typedef void (*GPIO_CallBackType)(uint32_t pinxArray);


//!< API functions
void GPIO_Init(GPIO_InitTypeDef * Init);
uint8_t GPIO_QuickInit(uint32_t instance, uint32_t pinx, GPIO_Mode_Type mode);
void GPIO_WriteBit(uint32_t instance, uint8_t pinIndex, uint8_t data);
uint8_t GPIO_ReadBit(uint32_t instance, uint8_t pinIndex);
void GPIO_ToggleBit(uint32_t instance, uint8_t pinIndex);
void GPIO_ITDMAConfig(uint32_t instance, uint8_t pinIndex, GPIO_ITDMAConfig_Type config, bool status);
void GPIO_CallbackInstall(uint32_t instance, GPIO_CallBackType AppCBFun);
//!< low level functions
void PORT_PinPullConfig(uint32_t instance, uint8_t pinIndex, PORT_Pull_Type pull);
void GPIO_PinConfig(uint32_t instance, uint8_t pinIndex, GPIO_PinConfig_Type mode);
void PORT_PinMuxConfig(uint32_t instance, uint8_t pinIndex, PORT_PinMux_Type pinMux);
uint32_t GPIO_ReadPort(uint32_t instance);
void GPIO_WritePort(uint32_t instance, uint32_t data);
    
#ifdef __cplusplus
}
#endif

#endif


