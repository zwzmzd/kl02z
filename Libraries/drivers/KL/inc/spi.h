#ifndef __CH_LIB_KL_SPI_H__
#define __CH_LIB_KL_SPI_H__

#include <stdint.h>
#include <stdbool.h>
  
//!< SPIģ���豸
#define HW_SPI0     (0x00)


//!< SPI֡��ʽѡ��
typedef enum
{
    kSPI_CPOL0_CPHA0,
    kSPI_CPOL0_CPHA1,
    kSPI_CPOL1_CPHA0,
    kSPI_CPOL1_CPHA1
}SPI_FrameFormat_Type;

typedef enum
{
    kSPI_Master,
    kSPI_Slave,
} SPI_Mode_Type;


//!< interrupt and DMA select
typedef enum
{
    kSPI_IT_Rx,            //!< SPI���յ�һ֡
    kSPI_IT_Tx,            //!< SPI������һ֡
}SPI_ITDMAConfig_Type;


#define kSPI_MSBFirst             (0x00)      //!< �ȷ������λ
#define kSPI_LSBFirst             (0x01)      //!< �ȷ������λ

//!< ��ʼ���ṹ
typedef struct
{
    uint32_t                instance;               //!< ģ���
    SPI_Mode_Type           mode;                   //!< ����ģʽ
    uint8_t                 dataSize;               //!< ÿ֡�����ж���λ ͨ��Ϊ8��16
    uint8_t                 bitOrder;               //!< �ȷ���λ�����ȷ���λ
    SPI_FrameFormat_Type    frameFormat;            //!< ����֡��ʽѡ��
    uint32_t                baudrate;               //!< ����
}SPI_InitTypeDef;

/***************************************
                                offset io_base  mux io_instance ip_instance
*0X00008CC0U= 0b 00000000 00000 00010   00110    011    000         000
                                2��io   PTA6    MUX3    PTA     SPI0
��ͬʱ����PTA6��PTA7 SPI0�� ����MUXΪ3
***************************************/
#define SPI0_MOSI_PA7_MISO_PA6  (0X00008CC0U)


//!< Callback Type
typedef void (*SPI_CallBackType)(void);

//!< API functions
void SPI_Init(SPI_InitTypeDef * SPI_InitStruct);
uint32_t SPI_QuickInit(uint32_t MAP, SPI_FrameFormat_Type frameFormat, uint32_t baudrate);
uint16_t SPI_ReadWriteByte(uint32_t instance, uint16_t data);
void SPI_ITDMAConfig(uint32_t instance, SPI_ITDMAConfig_Type config, bool status);
void SPI_CallbackInstall(uint32_t instance, SPI_CallBackType AppCBFun);



#endif

