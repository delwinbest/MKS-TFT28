/*
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
#if defined(HAL_ETH_MODULE_ENABLED)
#undef HAL_ETH_MODULE_ENABLED
#endif
// Right side
#define PB11 0
#define PB10 1
#define PB2  2
#define PB0  3  // A0
#define PA7  4  // A1
#define PA6  5  // A2
#define PA5  6  // A3
#define PA4  7  // A4
#define PA3  8  // A5
#define PA2  9  // A6
#define PA1  10 // A7
#define PA0  11 // A8
#define PC15 12
#define PC14 13
#define PC13 14
// Left side
#define PB7  15
#define PB6  16
#define PB5  17
#define PB4  18
#define PB3  19
#define PA15 20
#define PA14 21 // SWCLK
#define PA13 22 // SWDI0
#define PA12 23 // USB DP
#define PA11 24 // USB DM
#define PA10 25
#define PA9  26
#define PA8  27
#define PB15 28
#define PB14 29
#define PB13 30
#define PB12 31
// Other
#define PB8  32 //  - User buttons
#define PB1  33 // LED
#define PB9  34 // USB DISC

#define PD14 35//LCD_LED
#define PD15 36//LCD RD
#define PC8 37//LCD CS
#define PC5 38//Touch IRQ
#define PD11 39 //SDCARD Chip Select
#define PD15 40//LCD_RD 
#define PC12 41//unknown yet
#define PE0 42
#define PE1 43
#define PE2 44
#define PE3 45
#define PE4 46
#define PE5 47
#define PE6 48
#define PD13 49 //LCD_RS
#define PC9 50//TOUCH_CS
#define PE7 51//PE7
#define PC10 52
#define PC11 53
#define PC12 54
#define PC13 55
#define PD8 56
#define PD9 57
#define PD10 58
#define PD11 59
#define PD5 60
#define PD6 61


#define TOUCH_SCK PC10
#define LCD_LED PD14
#define SPEAKER PA2
#define FILIMENT PB0
#define POWER PB1
#define LCD_WR PB14
#define LCD_RS PD13
#define LCD_CS PC8
#define LCD_RD PD15
#define SDCARD_CS PD11
#define SDCARD_DT PB15
#define TOUCH_DI PC5
#define TOUCH_CS PC9
#define WIFI_DI PA9
#define FLASH_CS PB9
#define LCD_TOUCH_INPUT TOUCH_DI
#define LCD_BACKLIGHT_PIN LCD_LED
#define SDCARD_STATE SDCARD_DT
#define FILIMENT_Pin FILIMENT
#define POWER_Pin POWER
#define EEPROM_CS PIN_SPI2_SS

#define SERIALRX2 PD8 //uart 3 alt config
#define SERIALTX2 PD9//uart 3 alt config

// This must be a literal
#define NUM_DIGITAL_PINS        62 //dont forget to update this when adding new pins to pinarray darkspr1te- segfault hey 
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       9
#define NUM_ANALOG_FIRST        35

// On-board LED pin number
#define LED_BUILTIN             PD14
#define LED_GREEN               LED_BUILTIN
#define LED_RED  PB0

// SPI Definitions
#define PIN_SPI_SS              PA4
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5

// SPI Definitions
#define PIN_SPI2_SS              PA15
#define PIN_SPI2_MOSI            PB5
#define PIN_SPI2_MISO            PB4
#define PIN_SPI2_SCK             PB3

// SPI2 Definitions
#define PIN_SPI1_SS              PC9
#define PIN_SPI1_MOSI            PC12
#define PIN_SPI1_MISO            PC11
#define PIN_SPI1_SCK             PC10

#define PIN_SPI0_SS              PB12
#define PIN_SPI0_MOSI            PB15
#define PIN_SPI0_MISO            PB14
#define PIN_SPI0_SCK             PB13

  
// I2C Definitions
#define PIN_WIRE_SDA            PB7
#define PIN_WIRE_SCL            PB6

// Timer Definitions
// Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM4

// Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

// UART Definitions
#define SERIAL_UART_INSTANCE    1
// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA10//def usart1 wifi rx labels are correct for tx/rx
#define PIN_SERIAL_TX           PA9//def usart1 wifi tx 

#define PIN_SERIAL2_RX           PD6//uart2 connect to AUX-1 //PA3//PA3//
#define PIN_SERIAL2_TX           PD5//uart2 connect to AUX-1 //PA2//PA2 speaker

#define PIN_SERIAL3_TX           PD8 //PB10 //wifi txd // uart 3 default config PD9 label on board are swapped for tx/rx 
#define PIN_SERIAL3_RX           PD9 //PB11 //wifi rxd //uart 3 defualt config 
// USB
#define USB_DISC_PIN            PB9

//#define MAIN_PR_OFFSET 0x8000
//#define HSE_VALUE               25000000U /*!< Default value of the External oscillator in Hz.*/
//#define VECT_TAB_SRAM 1
/*
VECT_TAB_OFFSET
VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. 
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. *
#endif

*/
 //#define VECT_TAB_SRAM
 #define SPEAKER_Pin             GPIO_PIN_2
 #define SPEAKER_GPIO_Port       GPIOA
 #define FILAMENT_DI_Pin         GPIO_PIN_0
 #define FILAMENT_DI_GPIO_Port   GPIOB
 #define POWER_DI_Pin            GPIO_PIN_1
 #define POWER_DI_GPIO_Port      GPIOB
 #define LCD_nWR_Pin             GPIO_PIN_14
 #define LCD_nWR_GPIO_Port       GPIOB
 #define LCD_RS_Pin              GPIO_PIN_13
 #define LCD_RS_GPIO_Port        GPIOD
 #define LCD_BACKLIGHT_Pin       GPIO_PIN_14
 #define LCD_BACKLIGHT_GPIO_Port GPIOD
 #define LCD_nRD_Pin             GPIO_PIN_15
 #define LCD_nRD_GPIO_Port       GPIOD
 #define LCD_nCS_Pin             GPIO_PIN_8
 #define LCD_nCS_GPIO_Port       GPIOC
 #define SDCARD_nCS_Pin          GPIO_PIN_11
 #define SDCARD_nCS_GPIO_Port    GPIOD
 #define SDCARD_DETECT_Pin       GPIO_PIN_15
 #define SDCARD_DETECT_GPIO_Port GPIOB
 #define TOUCH_DI_Pin            GPIO_PIN_5
 #define TOUCH_DI_GPIO_Port      GPIOC
 #define TOUCH_nCS_Pin           GPIO_PIN_9
 #define TOUCH_nCS_GPIO_Port     GPIOC
 #define WIFI_DI_Pin             GPIO_PIN_9
 #define WIFI_DI_GPIO_Port       GPIOA
 #define FLASH_nCS_Pin           GPIO_PIN_9
 #define FLASH_nCS_GPIO_Port     GPIOB
//define STM32F107xC
#define MKS_TFT


#define HSE_VALUE    25000000U /*!< Value of the External oscillator in Hz */



//#define HAL_WWDG_MODULE_ENABLED
#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR     Serial
#define SERIAL_PORT_HARDWARE    Serial
//#define SERIAL_PORT_HARDWARE_OPEN Serial3
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
