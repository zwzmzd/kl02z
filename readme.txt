# Freescale FRDMKL02_minidock Sample Package V1.0

----------
## IDE support
	- IAR EWARM 7.20
    - Keil 5.00
	
## Structure

����Libraries
��  ����devices
��  ��  ����inc: include folder of on board device, such as EEPORM, SPI_FLASH
��  ��  ����src: source folder of on board device, such as EEPORM, SPI_FLASH
��  ��          
��  ����drivers
��  ��  ����KL
��  ��      ����inc: include folder of KL driver
��  ��      ����src: source folder of KL driver
��  ��          
��  ��                      
��  ����startup
��      ����CoreSupport: Cortex CMSIS style start-up file
��      ��      
��      ����DeviceSupport: devices header file and startup file.
��                  
����Project
    ����KL02_FRDM_Minidock: KL02_FRDM_Minidock demo and demo's source code
        ����0-template
        ����1-LED  
        ����2-Key      
        ����3-UART     
        ����4-I2C_EEPROM      
        ����5-SPI_FLASH       
        ����6-ADC     
        ����7-BME      
        ����8-LowPower   
        ����9-LPTMR
        ����10-TPM

#############################################################################
0-templete
���̹��ܣ�
   ȫ�������̣�����ʵ��Low power, LED, ADC,SPI,I2C�Լ�BMEģ��Ĺ��ܣ�ģ�����ʵ��˳�����£�
1��low power, ����VLPSģʽ������ͨ������K2�������ѣ����Ѻ������һ������
2��LED��ʵ����չ�����ĸ�LED����˸
3��ADC��ʵ�ְ���RV1��λ����ѹ�Ĳɼ�����ͨ�����ڴ�ӡ
4��SPI��ʵ����չ�����ⲿSPIflash W25P80оƬ�Ķ���д���������ݴ�ӡ������
5��I2C��ʵ����չ�����ⲿI2C EEPROM�Ķ�д
6��BME��ʵ����ͨC�����Լ�BME ����ܵ�ִ��ʱ��Ƚ�
������ֹͣ��

1-LED

���̹��ܣ�
   ʵ����չ����LD1-LD4 4��С�Ƶ�ͬʱ��˸����ͨ��������9600�����ʴ�ӡ��1-LED demo hello world!��

2-Key
���̹��ܣ�
   ʵ����չ���ϰ�������LD�Ĺ��ܡ�
 K4����LD4��K3����LD3��K2����LD2���������£���ӦС�Ƶ������ɿ���������ӦС��Ϩ��K1��reset����������δ�����ơ�
 ������9600�����ʴ�ӡ��2-KEY demo!
ע��K3��FRDM����MMA8451Q INT2����,������չ��K3��������Ҫȥ��FRDM����R26����

3-UART
���̹��ܣ�
   ʵ�ִ�����9600bps�����ʴ�ӡCPU��Ϣ����flash��Ϣ�������ʵ�ֽ����жϲ����ؽ����ַ�

4-I2C_EEPROM
���̹��ܣ�
�ȶ�24C02����64�ֽڵ�����д������Ȼ����ͨ��������������ȡд���64�ֽڣ��Ƚ�ǰ�������Ƿ�һ��

5-SPI_FLASH
���̹��ܣ�
   ʵ����չ�����ⲿflashW25P80��һ��ҳ256�ֽڵĲ�д���ܣ���ͨ����ӡ��256�ֽڲ�ǰ����д�������
  �ⲿflash��д��ɺ���չ����LD4��˸
 ������9600�����ʴ�ӡ��5-SPI_FLASH demo!��

6-ADC
���̹��ܣ�
   ͨ��ADC�ɼ���չ����RV1��λ����ֵ����ͨ��ֵ�������ư���LD1-4�Ƶ�������ת��λ��������ʵ�ֲ�ͬλ��С�Ƶ���
   ��ͨ��������9600�����ʴ�ӡ��λ��ADCֵ���Լ�������Ϣ:6-ADC with LED flashing demo!��


7-BME
���̹��ܣ�
   �Ƚ�ʵ����ͨC�Լ�BME��ʽ�����������ִ��ʱ���С��
   ��ͨ������9600�����ʣ���ӡ��ͨC��BME��ʽ�������systickִ��ʱ��
  ������9600�����ʴ�ӡ��7-BME demo!��

8-LowPower
���̹��ܣ�
  ����͹���VLPS֮��ͨ��NMI������K2���������ѡ�
  ������9600�����ʴ�ӡ��8-LowPower demo!��

9-LPTMR
���̹��ܣ�
ÿ100ms��תRed led�Լ���չ���ϵ�LD1
������9600�����ʴ�ӡ��9-lptrm timer counter test

10-TPM
���̹��ܣ�
  PTA5������ں㶨��1Khz��,ռ�ձ�ѭ���仯��PWM
������9600�����ʴ�ӡ��10-PWM test, please measure waveform in PTA05
