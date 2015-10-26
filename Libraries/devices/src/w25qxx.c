/**
  ******************************************************************************
  * @file    w25qxx.c
  * @author  YANDLD
  * @version V2.5
  * @date    2013.12.25
  * @brief   www.beyondcore.net   http://upcmcu.taobao.com 
  ******************************************************************************
  */

#include <string.h>

#include "w25qxx.h"

//оƬWQ25ָ��
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_ReadStatusReg2		0x35 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 


#ifndef USE_USER_MEM
//uint8_t SPI_FLASH_BUFFER[4096];
uint8_t SPI_FLASH_BUFFER[256];
#endif

#define W25QXX_DEBUG		0
#if ( W25QXX_DEBUG == 1 )
#define W25QXX_TRACE	printf
#else
#define W25QXX_TRACE(...)
#endif

//W25оƬ��Ϣ
static const struct w25qxx_attr_t w25qxx_tbl[] = 
{
    {"W25Q10",    128*1024, 0xEF10, 256, 4096, (64*1024)},
    {"W25Q20",    256*1024, 0xEF11, 256, 4096, (64*1024)},
    {"W25Q40",    512*1024, 0xEF12, 256, 4096, (64*1024)},
    {"W25Q80",   1024*1024, 0xEF13, 256, 4096, (64*1024)},
    {"W25Q16",   2048*1024, 0xEF14, 256, 4096, (64*1024)},
    {"W25Q32",   4096*1024, 0xEF15, 256, 4096, (64*1024)},
    {"W25Q64",   8192*1024, 0xEF16, 256, 4096, (64*1024)},
    {"W25Q128", 16384*1024, 0xEF17, 256, 4096, (64*1024)}, 
    {"W25P80",   1024*1024, 0x5114, 256, 4096, (64*1024)}, 
};



struct w25qxx_device 
{
    const char              *name;
    struct w25qxx_attr_t    attr;
    struct w25qxx_init_t    ops;
    void                    *user_data;
};

static struct w25qxx_device w25_dev;

static inline uint8_t spi_xfer(uint8_t data, uint8_t csStatus)
{
    
    uint8_t data_in;
    w25_dev.ops.xfer(&data_in, &data, 1, csStatus);
    while(w25_dev.ops.get_reamin() != 0);
    return data_in;
}


//оƬ�ϵ�
static int w25qxx_power_up(void)
{
    volatile uint32_t i;
    spi_xfer(W25X_ReleasePowerDown, W25QXX_CS_HIGH);
    
    /* delay 3us */
    for(i=0;i<1000*5;i++);
    return 0;
}

//оƬ��
static uint8_t w25qxx_read_sr2(void)
{
    uint8_t sr;
    
    spi_xfer(W25X_ReadStatusReg2, W25QXX_CS_LOW);
    sr = spi_xfer(0x00, W25QXX_CS_HIGH);
    
    return sr;
}

static uint8_t w25qxx_read_sr(void)
{
    uint8_t sr;
    
    spi_xfer(W25X_ReadStatusReg, W25QXX_CS_LOW);
    sr = spi_xfer(0x00, W25QXX_CS_HIGH);
    
    return sr;
}

//оƬдʹ��
static int w25qxx_write_enable(void)
{
    spi_xfer(W25X_WriteEnable, W25QXX_CS_HIGH);
    return 0;
}

//оƬд
static int w25qxx_write_sr(uint8_t value)
{
    w25qxx_write_enable();
    spi_xfer(W25X_WriteStatusReg, W25QXX_CS_LOW);
    spi_xfer(value, W25QXX_CS_HIGH);
    return 0;
}

//оƬ̽��
static int w25qxx_probe(void)
{
    uint32_t i;
    uint16_t id;
    uint8_t buf[2];

    /* read id */
    spi_xfer(W25X_ManufactDeviceID, W25QXX_CS_LOW);
    spi_xfer(0, W25QXX_CS_LOW);
    spi_xfer(0, W25QXX_CS_LOW);
    spi_xfer(0, W25QXX_CS_LOW);
    buf[0] = spi_xfer(0, W25QXX_CS_LOW);
    buf[1] = spi_xfer(0, W25QXX_CS_HIGH);
    id = ((buf[0]<<8) + buf[1]);
    W25QXX_TRACE("ID:0x%X\r\n", id);
    //see if we find a match
    for(i = 0; i< ARRAY_SIZE(w25qxx_tbl);i++)
    {
        if(w25qxx_tbl[i].id == id)
        {
            /* find a match */
            w25_dev.attr = w25qxx_tbl[i];
            w25qxx_power_up();
            buf[0] = w25qxx_read_sr();
            W25QXX_TRACE("SR:0x%X\r\n", buf[0]);
            buf[0] = w25qxx_read_sr2();
            W25QXX_TRACE("SR2:0x%X\r\n", buf[0]);
            // enable full access to all memory regin, something like unlock chip.
            w25qxx_write_sr(0x00);
            return 0; 
        }
    }
    return 1;
}

int w25qxx_get_attr(struct w25qxx_attr_t* attr)
{
    memcpy(attr, &w25_dev.attr, sizeof(struct w25qxx_attr_t));
    return 0;
}

//��ȡ����
int w25qxx_read(uint32_t addr, uint8_t *buf, uint32_t len)
{
    /* send addr */
    spi_xfer(W25X_ReadData, W25QXX_CS_LOW);
    spi_xfer((uint8_t)((addr)>>16), W25QXX_CS_LOW);
    spi_xfer((uint8_t)((addr)>>8), W25QXX_CS_LOW);
    spi_xfer((uint8_t)addr, W25QXX_CS_LOW);
   
    w25_dev.ops.xfer(buf, NULL, len, W25QXX_CS_HIGH);
    while(w25_dev.ops.get_reamin() != 0)
    {
        w25_dev.ops.delayms(10);
    }
    
    return 0;
}

//дһҳ����
int w25qxx_write_page(uint32_t addr, uint8_t *buf, uint32_t len)
{
    w25qxx_write_enable();

    /* send addr */
    spi_xfer(W25X_PageProgram, W25QXX_CS_LOW);
    spi_xfer((uint8_t)((addr)>>16), W25QXX_CS_LOW);
    spi_xfer((uint8_t)((addr)>>8), W25QXX_CS_LOW);
    spi_xfer((uint8_t)addr, W25QXX_CS_LOW);
    
    w25_dev.ops.xfer(NULL, buf, len, W25QXX_CS_HIGH);
    while(w25_dev.ops.get_reamin() != 0)
    {
        w25_dev.ops.delayms(10);
    }

    
    /* wait busy */
    while((w25qxx_read_sr() & 0x01) == 0x01)
    {
        w25_dev.ops.delayms(1);
    }
    return 0;
}

//д����
static int w25qxx_write_no_check(uint32_t addr, uint8_t *buf, uint32_t len)  
{ 			 		 
	uint16_t pageremain;	   
        W25QXX_TRACE("w25qxx - write_no_check: addr:%d len:%d\r\n", addr, len);
    
	pageremain = w25_dev.attr.page_size-(addr%w25_dev.attr.page_size); //��ҳʣ����ֽ���		 	    
	if(len <= pageremain) pageremain = len;//������256���ֽ�
	while(1)
	{	   
           if(w25qxx_write_page(addr, buf, pageremain))
           {
              return 1;
           }
	   if(len == pageremain)break;//д�������
	   else //NumByteToWrite>pageremain
	   {
		buf += pageremain;
		addr += pageremain;	
		len -= pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
		if(len > 256)pageremain=256; //һ�ο���д��256���ֽ�
		else pageremain = len; 	  //����256���ֽ���
	    }
	}
    return 0;
} 

//��������
int w25qxx_erase_sector(uint32_t addr)
{
    
    addr /= w25_dev.attr.sector_size;
    addr *= w25_dev.attr.sector_size; //round addr to N x W25X_SECTOR_SIZE
    
    w25qxx_write_enable();
    while((w25qxx_read_sr() & 0x01) == 0x01);
    
    spi_xfer(W25X_SectorErase, W25QXX_CS_LOW);
    spi_xfer((uint8_t)((addr)>>16), W25QXX_CS_LOW);
    spi_xfer((uint8_t)((addr)>>8), W25QXX_CS_LOW);
    spi_xfer((uint8_t)addr, W25QXX_CS_HIGH);
    
    while((w25qxx_read_sr() & 0x01) == 0x01)
    {
        w25_dev.ops.delayms(10);
    }
    return 0;
}

//��������оƬ
int w25qxx_erase_chip(void)
{
    w25qxx_write_enable();
    while((w25qxx_read_sr() & 0x01) == 0x01);
    
    spi_xfer(W25X_ChipErase, W25QXX_CS_HIGH);

    while((w25qxx_read_sr() & 0x01) == 0x01)
    {
        w25_dev.ops.delayms(10);
    }
    return 0;
}

//��оƬд����
int w25qxx_write(uint32_t addr, uint8_t *buf, uint32_t len)  
{ 

   w25qxx_write_no_check(addr, buf, len);

    return 0;
}



//оƬ��ʼ��
int w25qxx_init(struct w25qxx_init_t* init)
{
    memcpy(&w25_dev.ops, init, sizeof(struct w25qxx_init_t));
    return w25qxx_probe();
}

