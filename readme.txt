# Freescale FRDMKL02_minidock Sample Package V1.0

----------
## IDE support
	- IAR EWARM 7.20
    - Keil 5.00
	
## Structure

├─Libraries
│  ├─devices
│  │  ├─inc: include folder of on board device, such as EEPORM, SPI_FLASH
│  │  └─src: source folder of on board device, such as EEPORM, SPI_FLASH
│  │          
│  ├─drivers
│  │  └─KL
│  │      ├─inc: include folder of KL driver
│  │      └─src: source folder of KL driver
│  │          
│  │                      
│  └─startup
│      ├─CoreSupport: Cortex CMSIS style start-up file
│      │      
│      └─DeviceSupport: devices header file and startup file.
│                  
└─Project
    └─KL02_FRDM_Minidock: KL02_FRDM_Minidock demo and demo's source code
        ├─0-template
        ├─1-LED  
        ├─2-Key      
        ├─3-UART     
        ├─4-I2C_EEPROM      
        ├─5-SPI_FLASH       
        ├─6-ADC     
        ├─7-BME      
        ├─8-LowPower   
        ├─9-LPTMR
        └─10-TPM

#############################################################################
0-templete
例程功能：
   全功能例程，可以实现Low power, LED, ADC,SPI,I2C以及BME模块的功能，模块代码实现顺序如下：
1，low power, 进入VLPS模式，可以通过板上K2按键唤醒，唤醒后进入下一个功能
2，LED，实现扩展板上四个LED的闪烁
3，ADC，实现板上RV1电位器电压的采集，并通过串口打印
4，SPI，实现扩展板上外部SPIflash W25P80芯片的读擦写，并将数据打印出来。
5，I2C，实现扩展板上外部I2C EEPROM的读写
6，BME，实现普通C代码以及BME 异或功能的执行时间比较
最后程序停止。

1-LED

例程功能：
   实现扩展板上LD1-LD4 4个小灯的同时闪烁，并通过串口以9600波特率打印：1-LED demo hello world!。

2-Key
例程功能：
   实现扩展板上按键控制LD的功能。
 K4控制LD4，K3控制LD3，K2控制LD2，按键按下，相应小灯点亮，松开按键，相应小灯熄灭。K1与reset引脚相连，未做控制。
 串口以9600波特率打印：2-KEY demo!
注意K3和FRDM板上MMA8451Q INT2共用,若用扩展板K3按键，需要去掉FRDM板上R26电阻

3-UART
例程功能：
   实现串口以9600bps波特率打印CPU信息及其flash信息，另外可实现接收中断并返回接收字符

4-I2C_EEPROM
例程功能：
先对24C02进行64字节的连续写操作，然后再通过连续读操作读取写入的64字节，比较前后数据是否一致

5-SPI_FLASH
例程功能：
   实现扩展板上外部flashW25P80第一个页256字节的擦写功能，并通过打印这256字节擦前擦后写后的数据
  外部flash读写完成后，扩展板上LD4闪烁
 串口以9600波特率打印：5-SPI_FLASH demo!。

6-ADC
例程功能：
   通过ADC采集扩展板上RV1电位器的值，并通过值域来控制板上LD1-4灯的亮灭，旋转电位器，可以实现不同位置小灯点亮
   并通过串口以9600波特率打印电位器ADC值，以及例程信息:6-ADC with LED flashing demo!。


7-BME
例程功能：
   比较实用普通C以及BME方式运行异或语句的执行时间大小。
   并通过串口9600波特率，打印普通C和BME方式异或语句的systick执行时间
  串口以9600波特率打印：7-BME demo!。

8-LowPower
例程功能：
  进入低功耗VLPS之后，通过NMI（板上K2按键）唤醒。
  串口以9600波特率打印：8-LowPower demo!。

9-LPTMR
例程功能：
每100ms翻转Red led以及扩展板上的LD1
串口以9600波特率打印：9-lptrm timer counter test

10-TPM
例程功能：
  PTA5输出周期恒定（1Khz）,占空比循环变化的PWM
串口以9600波特率打印：10-PWM test, please measure waveform in PTA05
