# MKS-TFT28 v4.0
Inspired by https://github.com/robotsrulz/MKS-TFT, MKS TFT32/28 Opensource Firmware.

## WHY and Warning
The MKS board has a propriety bootloader and firmware. I've been unable to find the source and, in my attempts to probe the board, I disabled the code protection and accidently erased the STM32F107 bootloader :). The board was dead.  
I've ordered a replacement and have decided to use the corpse of the old board for development. 

## What This Is
Scratch pad where I plan to develop a base firmware for the Makersbase TFT28 v4.0 Board. This module has been closed source and a major pain point for many enthusiasts. Feel free to borrow or learn form any of the work here. Hopefully it takes shape into something amazing. 

## Disclaimer !! 
As of 9 October, I'm still in the process of reverse engineering the board and getting all drivers into the operational state. 

## Connecting ST-LINK v2 to the MKS TFT: 

    ST-LINK    MKS-TFT32: 
    5v         AUX-1 5v 
    GND        AUX-1 GND 
    SWDIO      JTAG pin 4 
    SWCLK      JTAG pin 5 

## Board JTAG connector (left-to-right):

    3.3v   GND   GND 
    SWDIO  SWCLK RESET

Disconnect MKS TFT from printer before connecting ST-LINK. Do not connect ST-LINK 3.3v pin.


## Board Configuration

    BOOT Mode: Boot0 = 0, Boot 1 = 0

    SPI1 (default): SPIFlash: Winbond 8MB (64Mb) Serial Flash Memory W25Q CS: PB9,MOSI=PA7,PIN_SPI_MISO=PA6,PIN_SPI_SCK=PA5
    SPI1 (default): SDCard CS: PD11, MOSI=PA7,PIN_SPI_MISO=PA6,PIN_SPI_SCK=PA5
    SPI3 (remapped): URTouch CS: PC5
    I2C: Two-wire Serial EEPROM AT24C16B 
    UART1: Wifi connector
    UART2: Octopi
    UART4: Touch controller
    PX11/12, UART1_CTS/RTS: USB
    PA2: Buzzer


