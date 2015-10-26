#include <string.h>
#include <stdio.h>

#include "w25qxx.h"
#include "spi.h"
#include "gpio.h"

#define PAGE_SIZE 256

void print_buf(void *buf, uint16 size)
{
    int i;
    uint8 *p = (uint8*)buf;
    for(i=0;i<size;i++)
    {
        printf("0x%.2x,", p[i]);
        if(((i+1)&0x3) == 0)
            printf("  ");
        if(((i+1)&0x7) == 0)
            printf("\n");
    }

    printf("\n");
}

static uint32_t xfer(uint8_t *buf_in, uint8_t *buf_out, uint32_t len, uint8_t cs_state)
{
    uint8_t dummy_in;
    
    if(!buf_in)
        buf_in = &dummy_in;
    GPIO_WriteBit(HW_GPIOA, 5, 0);  //cs
    while(len--)
    {
        *buf_in = SPI_ReadWriteByte(HW_SPI0, *buf_out); 
        if(buf_out)
            buf_out++;
        if(buf_in != &dummy_in)
            buf_in++;
    }
    GPIO_WriteBit(HW_GPIOA, 5, cs_state);  //cs
    return len;
}

static uint32_t _get_reamin(void)
{
    return 0;
}

int cmd_spi(int argc, char * const argv[])
{
    struct w25qxx_init_t init;
    uint32_t i, buf_size;
    static uint8_t buf[256];
    struct w25qxx_attr_t w25qxx;
    
    init.delayms = DelayMs;
    init.get_reamin = _get_reamin;
    init.xfer = xfer;
    
    SPI_QuickInit(SPI0_MOSI_PA7_MISO_PA6, kSPI_CPOL1_CPHA1, 100*1000);//����PTA7ΪMOSI PTA6ΪMISO, ������Ϊ100K������ʵ�ʲ�����Ҫ����ƥ������ļĴ���ֵ�㣬��Щ���
    GPIO_QuickInit(HW_GPIOA, 5, kGPIO_Mode_OPP); //PTA5 SS
    GPIO_WriteBit(HW_GPIOA, 5, 1);  
    PORT_PinMuxConfig(HW_GPIOB,0,kPinAlt3); //PTB0 SCK
       
    w25qxx_init(&init);   //�ⲿflash��ʼ��
    w25qxx_get_attr(&w25qxx);
    buf_size = sizeof(buf); 
    
    /*��ȡ�ⲿflash256���ֽ�*/
    printf("reading page...\n");
    w25qxx_read(0, buf, buf_size);
    print_buf(buf,PAGE_SIZE);
    /*���������ⲿflashоƬ*/  
    printf("erase all chips...\r\n");
    w25qxx_erase_chip();
    printf("erase complete\r\n");
    /*��ȡ�ⲿflash256���ֽ�*/
    printf("reading page...\n");
    w25qxx_read(0, buf, buf_size);
    print_buf(buf,PAGE_SIZE);
    /*����ⲿflash256���ֽ�*/
    printf("programing a page...\n");
    for(i=0;i<256;i++)
        buf[i] = i;
    w25qxx_write(0, buf, buf_size);
     
    printf("clearing buffer..\n");
    for(i=0;i<256;i++)
        buf[i] = 0;
    /*��ȡ�ⲿflash256���ֽ�*/
    printf("reading page...\n");
    w25qxx_read(0, buf, buf_size);
    print_buf(buf,PAGE_SIZE);
    
    printf("demo end.\n");
 

    return 0;
}


