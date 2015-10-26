#ifndef __CH_LIB_ADC_H__
#define __CH_LIB_ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* ADC instance */
#define HW_ADC0  (0)


/* ADC conver select */
#define kADC_MuxA                (0x00)
#define kADC_MuxB                (0x01)

/* ADC channel pin select */
#define kADC_ChlMuxA             (0x00)
#define kADC_ChlMuxB             (0x01)
     
   
#define ADC0_SE0A_PA12      (0x00002c00U)   //具体结构查看adc.c最下面的注释
#define ADC0_SE1A_PB05      (0x00084a08U) 
#define ADC0_SE2A_PA09      (0x00105200U)
#define ADC0_SE3A_PA08      (0x00185000U)
#define ADC0_SE4A_PB02      (0x00204408U)
#define ADC0_SE5A_PB01      (0x00204208U)
#define ADC0_SE6A_PB00      (0x00282008U)
#define ADC0_SE7A_PA07      (0x00a02e00U)   
#define ADC0_SE8A_PB11      (0x00a85608U)
#define ADC0_SE9A_PB10      (0x00605408U)
#define ADC0_SE10A_PB09     (0x00685208U)
#define ADC0_SE11A_PB08     (0x00705008U)
#define ADC0_SE12A_PA00     (0x00782000U)
#define ADC0_SE13A_PB13     (0x00805a10U)
typedef enum
{
    kADC_ClockDiv1,  
    kADC_ClockDiv2,
    kADC_ClockDiv4,
    kADC_ClockDiv8,
}ADC_ClockDiv_Type;


typedef enum
{
    kADC_SingleDiff8or9 = 0,
    kADC_SingleDiff12or13 = 1,
    kADC_SingleDiff10or11 = 2,  
    //kADC_SingleDIff16 = 3,
}ADC_ResolutionMode_Type;


typedef enum
{
    kADC_TriggerSoftware,
    kADC_TriggerHardware,
}ADC_TriggerSelect_Type;


typedef enum
{
    kADC_ContinueConversionEnable,
    kADC_ContinueConversionDisable,
}ADC_ContinueMode_Type;


typedef enum
{
    kADC_Single,
    kADC_Differential,
}ADC_SingleOrDiffMode_Type;

//!< rerference select
typedef enum
{
    kADC_VoltageVREF,
    kADC_VoltageVALT,
}ADC_VoltageRef_Type;

//!< hardware average
typedef enum
{
    kADC_HardwareAverageDisable,
    kADC_HardwareAverage_4,
    kADC_HardwareAverage_8,
    kADC_HardwareAverage_16,
    kADC_HardwareAverage_32,
}ADC_HardwareAveMode_Type;

//!< interrupt and DMA config
typedef enum
{
    kADC_IT_EOF,
    kADC_DMA_EOF,
}ADC_ITDMAConfig_Type;

/* callback install */
typedef void (*ADC_CallBackType)(void);

//!< ADC Init struct
typedef struct
{
    uint32_t                    instance;
    ADC_TriggerSelect_Type      triggerMode;
    ADC_ClockDiv_Type           clockDiv;
    ADC_ResolutionMode_Type     resolutionMode;
    ADC_SingleOrDiffMode_Type   singleOrDiffMode;
    ADC_ContinueMode_Type       continueMode;
    ADC_HardwareAveMode_Type    hardwareAveMode;
    ADC_VoltageRef_Type         vref;
}ADC_InitTypeDef;


//!< API functions
void ADC_CallbackInstall(uint32_t instance, ADC_CallBackType AppCBFun);
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct);
uint8_t ADC_QuickInit(uint32_t MAP, ADC_ResolutionMode_Type resolutionMode);
void ADC_ITDMAConfig(uint32_t instance, uint32_t mux, ADC_ITDMAConfig_Type config, bool status);
int32_t ADC_QuickReadValue(uint32_t MAP);
int32_t ADC_ReadValue(uint32_t instance, uint32_t mux);
void ADC_StartConversion(uint32_t instance, uint32_t chl, uint32_t mux);
uint8_t ADC_IsConversionCompleted(uint32_t instance, uint32_t mux);
void ADC_ChlMuxConfig(uint32_t instance, uint32_t mux);


#ifdef __cplusplus
}
#endif



#endif
