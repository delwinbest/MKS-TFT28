#ifndef _DELAY_H_
#define _DELAY_H_
#include "stdint.h"

void Delay_init(uint8_t clk);   
void Delay_ms(uint16_t ms);     
void Delay_us(uint32_t us);     
void Delay(uint32_t time);     

#endif
