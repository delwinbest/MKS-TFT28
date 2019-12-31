#ifndef _SERIAL_H_
#define _SERIAL_H_

#ifdef __cplusplus
extern "C" {
#endif

////#include "stm32f10x.h"
#include "parseACK.h"
#include "usart.h"

typedef struct
{
  char *cache;
  uint16_t wIndex;
  uint16_t rIndex;
}DMA_CIRCULAR_BUFFER;

#define DMA_TRANS_LEN  ACK_MAX_SIZE

extern DMA_CIRCULAR_BUFFER dmaL1Data[_USART_CNT];
  
void Serial_Init(uint32_t baud);
void Serial_DeInit(void);
void Serial_Puts(uint8_t port, char *s);

#ifdef __cplusplus
}
#endif

#endif 




















