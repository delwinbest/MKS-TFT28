#ifndef _INCLUDES_H_
#define _INCLUDES_H_



#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <Arduino.h>

#include "w25qxx.h"
#include "buzzer.h"
#include "lcd.h"
#include "UTFT.h"
#include "URTouch.h"
#include "eeprom_config.h"
#include "sd.h"
#include "ff.h"
#include "vfs.h"
#include "myfatfs.h"
#include "Language.h"
#include "misc.h"


#define LCD_WIDTH	  320
#define LCD_HEIGHT	240

#define BYTE_HEIGHT 16
#define BYTE_WIDTH  (BYTE_HEIGHT/2)

#define ICON_WIDTH  70
#define ICON_HEIGHT 70
#define TITLE_END_Y 40

#define LIST_ICON_WIDTH   55
#define LIST_ICON_HEIGHT  50

#define WORD_UNICODE            0x280000 // unicode (+0x480000 4.5M)
#define BYTE_ASCII_ADDR         0x700000 // ascii (+0x1000 4K)

#endif
