#include "gpio.h"


/* gloabl vars */
static GPIO_Type * const GPIO_InstanceTable[] = GPIO_BASES;
static PORT_Type * const PORT_InstanceTable[] = PORT_BASES;
//static GPIO_CallBackType GPIO_CallBackTable[ARRAY_SIZE(PORT_InstanceTable)] = {NULL};

static const struct reg_ops CLKTbl[] =
{
    {(void*)&(SIM->SCGC5), SIM_SCGC5_PORTA_MASK},
    {(void*)&(SIM->SCGC5), SIM_SCGC5_PORTB_MASK},
};


static const IRQn_Type GPIO_IRQnTable[] = 
{
    (IRQn_Type)(PORTA_IRQn+0),
    (IRQn_Type)(PORTA_IRQn+1),
    (IRQn_Type)(PORTA_IRQn+2),
    (IRQn_Type)(PORTA_IRQn+3),
    (IRQn_Type)(PORTA_IRQn+4),
};



//! @defgroup CHKinetis
//! @{


//! @defgroup GPIO
//! @brief GPIO API functions
//! @{

 /**
 * @brief Set Pinmux
 * @retval None
 */
void PORT_PinMuxConfig(uint32_t instance, uint8_t pinIndex, PORT_PinMux_Type pinMux)
{

    IP_CLK_ENABLE(instance);
    PORT_InstanceTable[instance]->PCR[pinIndex] &= ~(PORT_PCR_MUX_MASK);
    PORT_InstanceTable[instance]->PCR[pinIndex] |=  PORT_PCR_MUX(pinMux);
}
 /**
 * @brief  Set pin pull config
 */
void PORT_PinPullConfig(uint32_t instance, uint8_t pinIndex, PORT_Pull_Type pull)
{
    IP_CLK_ENABLE(instance);
    switch(pull)
    {
        case kPullDisabled:
            PORT_InstanceTable[instance]->PCR[pinIndex] &= ~PORT_PCR_PE_MASK;
            break;
        case kPullUp:
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_PE_MASK;
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_PS_MASK;
            break;
        case kPullDown:
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_PE_MASK;
            PORT_InstanceTable[instance]->PCR[pinIndex] &= ~PORT_PCR_PS_MASK;
            break;
        default:
            break;
    }
}


 /**
 * @brief  set GPIO pin direction
 */
void GPIO_PinConfig(uint32_t instance, uint8_t pinIndex, GPIO_PinConfig_Type mode)
{
    IP_CLK_ENABLE(instance);
    (mode == kOutput) ? (GPIO_InstanceTable[instance]->PDDR |= (1 << pinIndex)):(GPIO_InstanceTable[instance]->PDDR &= ~(1 << pinIndex));
}

 /**
 * @brief  Initalize a pin
 */
void GPIO_Init(GPIO_InitTypeDef * Init)
{
    /* config state */
    switch(Init->mode)
    {
        case kGPIO_Mode_IFT:
            PORT_PinPullConfig(Init->instance, Init->pinx, kPullDisabled);
            GPIO_PinConfig(Init->instance, Init->pinx, kInput);
            break;
        case kGPIO_Mode_IPD:
            PORT_PinPullConfig(Init->instance, Init->pinx, kPullDown);
            GPIO_PinConfig(Init->instance, Init->pinx, kInput);
            break;
        case kGPIO_Mode_IPU:
            PORT_PinPullConfig(Init->instance, Init->pinx, kPullUp);
            GPIO_PinConfig(Init->instance, Init->pinx, kInput);
            break;
        case kGPIO_Mode_OPP:
            PORT_PinPullConfig(Init->instance, Init->pinx, kPullDisabled);
            GPIO_PinConfig(Init->instance, Init->pinx, kOutput);
            break;
        default:
            break;					
    }
    /* config pinMux */
    PORT_PinMuxConfig(Init->instance, Init->pinx, kPinAlt1);
}

 /**
 * @brief  init a pin
 */
uint8_t GPIO_QuickInit(uint32_t instance, uint32_t pinx, GPIO_Mode_Type mode)
{
    GPIO_InitTypeDef GPIO_InitStruct1;
    GPIO_InitStruct1.instance = instance;
    GPIO_InitStruct1.mode = mode;
    GPIO_InitStruct1.pinx = pinx;
    GPIO_Init(&GPIO_InitStruct1);
    return  instance;
}

 /**
 * @brief write a digital pin
 */
void GPIO_WriteBit(uint32_t instance, uint8_t pinIndex, uint8_t data)
{
    (data) ? (GPIO_InstanceTable[instance]->PSOR |= (1 << pinIndex)):(GPIO_InstanceTable[instance]->PCOR |= (1 << pinIndex));
}
 /**
 * @brief  read a pin
 */
uint8_t GPIO_ReadBit(uint32_t instance, uint8_t pinIndex)
{
    /* input or output */
    if(((GPIO_InstanceTable[instance]->PDDR) >> pinIndex) & 0x01)
    {
        return ((GPIO_InstanceTable[instance]->PDOR >> pinIndex) & 0x01);
    }
    else
    {
        return ((GPIO_InstanceTable[instance]->PDIR >> pinIndex) & 0x01);
    }
}

 /**
 * @brief  toggle a pin
 */
void GPIO_ToggleBit(uint32_t instance, uint8_t pinIndex)
{
    GPIO_InstanceTable[instance]->PTOR |= (1 << pinIndex);
}

void GPIO_SetBit(uint32_t instance, uint8_t pinIndex)
{
    GPIO_InstanceTable[instance]->PDOR |= (1 << pinIndex);
}
void GPIO_ClearBit(uint32_t instance, uint8_t pinIndex)
{
    GPIO_InstanceTable[instance]->PDOR &= ~(1 << pinIndex);
}
/**
 * @brief  read GPIO port
 */
uint32_t GPIO_ReadPort(uint32_t instance)
{
    return (GPIO_InstanceTable[instance]->PDIR);
}
/**
 * @brief  write GPIO port
 */
void GPIO_WritePort(uint32_t instance, uint32_t data)
{
    GPIO_InstanceTable[instance]->PDOR = data;
}

/**
 * @brief  set interrupt
 */
void GPIO_ITDMAConfig(uint32_t instance, uint8_t pinIndex, GPIO_ITDMAConfig_Type config, bool status)
{
    IP_CLK_ENABLE(instance);
    PORT_InstanceTable[instance]->PCR[pinIndex] &= ~PORT_PCR_IRQC_MASK;
    
    if(!status)
    {
        NVIC_DisableIRQ(GPIO_IRQnTable[instance]);
        return;
    }
    
    switch(config)
    {
        case kGPIO_DMA_RisingEdge:
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_IRQC(1);
            break;
        case kGPIO_DMA_FallingEdge:
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_IRQC(2);
            break;
        case kGPIO_DMA_RisingFallingEdge:
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_IRQC(3);
            break;
        case kGPIO_IT_Low:
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_IRQC(8);
            NVIC_EnableIRQ(GPIO_IRQnTable[instance]);
            break;
        case kGPIO_IT_RisingEdge:
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_IRQC(9);
            NVIC_EnableIRQ(GPIO_IRQnTable[instance]);
            break;
        case kGPIO_IT_FallingEdge:
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_IRQC(10);
            NVIC_EnableIRQ(GPIO_IRQnTable[instance]);
            break;
        case kGPIO_IT_RisingFallingEdge:
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_IRQC(11);
            NVIC_EnableIRQ(GPIO_IRQnTable[instance]);
            break;
        case kGPIO_IT_High:
            PORT_InstanceTable[instance]->PCR[pinIndex] |= PORT_PCR_IRQC(12);
            NVIC_EnableIRQ(GPIO_IRQnTable[instance]);
            break;
        default:
            break;
    }
}



void PORTA_IRQHandler(void)
{
    
       if(PORTA_ISFR == (1<<12)) //KEY4 PTA12 上升下降沿中断
       { 
        PORTA_PCR12 |= PORT_PCR_ISF_MASK;
       
         if( GPIOA_PDIR & (1 <<12) ) //  KEY4弹起，关闭LED1 LD3
         {
            GPIOB_PDOR |= 1 << 10;   //关闭LED1
         }
         else          // KEY4按下，点亮LED1 LD3
         {
           GPIOB_PDOR &= ~(1 << 10);  //打开LED1
          }
    }

}




//! @}
