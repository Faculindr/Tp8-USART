#ifndef USART_H
#define USART_H

#include "stm32f103xb.h"

void usart_init(USART_TypeDef * USARTx, uint32_t baudrate);
void usart_send_char(USART_TypeDef * USARTx, uint8_t data);
void usart_send_string(USART_TypeDef*, char*txt);
uint8_t usart_receive_char(USART_TypeDef * USARTx);

#endif