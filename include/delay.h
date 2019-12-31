#ifndef _DELAY_H_
#define _DELAY_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

void Delay_init(uint8_t clk);   
void Delay_ms(uint16_t ms);     
void Delay_us(uint32_t us);     
//void Delay(uint32_t time);     

#ifdef __cplusplus
}
#endif

#endif
