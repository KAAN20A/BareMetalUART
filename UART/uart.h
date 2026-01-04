/*
File:uart.h

Author:Kaan Acar
*/

#include<stdint.h>
#include"common_defines.h"



void init_hardware(void);
void init_clock(void);
void init_timer(void);
void init_usart(uint32_t baudrate);
void uart_putbyte(uint8_t byte,USART_TypeDef *USART);
void nvic_enable_irq(IRQn_Type IRQn);
