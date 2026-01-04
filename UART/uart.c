/*
File:uart.c

Author:Kaan Acar
*/

#include"uart.h"

#define USART_BAUD 115200
void init_hardware(void)
{
    init_clock();
    init_usart(USART_BAUD);
    init_timer();
}



void init_usart(uint32_t baudrate)
{
    RCC->APB2ENR    |= 0x00000004;
    RCC->APB2ENR    |= 0x00004000;

    GPIOA->CRH &= ~(0x000000C0  | 0x00000030);
    GPIOA->CRH &= ~(0x00000C00 | 0x00000300);

    GPIOA->CRH |= 0x00000020 | 0x00000010;
    GPIOA->CRH |= 0x00000080;
    GPIOA->CRH |= 0x00000400;


    uint32_t baud   = (uint32_t)(8 000 000/baudrate);
    USART1->BRR     = baud;
    USART1->CR1     = 0x00000008 | 0x00000004 | 0x00000020 | 0x00002000;


    nvic_enable_irq(USART1_IRQn);
}
void uart_putbyte(uint8_t byte,USART_TypeDef *USART)
{
    if(byte == '\n')
    {
        put_char('\r');
    }
    USART->DR = (int)(byte);
    while (!(USART->SR & 0x00000080));
}

int uart_put_string(char *buffer, int max_len, char terminator) {
    int idx = 0;

    while (idx < (max_len - 1)) {
        uint8_t c = uart_putbyte();

        if (c == terminator) {
            break;
        }

        buffer[idx++] = c;
    }

    buffer[idx] = '\0';
    return idx;
}
