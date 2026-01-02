#include "uart.h"
#include "register.h"


int main(void)
{
    init_hardware();
    put_char('\n');

    while (1)
    {



    }

    return 0;
}

int uart_get_string(char *buffer, int max_len, char terminator) {
    int idx = 0;

    while (idx < (max_len - 1)) {  // sondaki '\0' için yer bırak
        uint8_t c = get_char();    // tek karakter oku

        if (c == terminator) {
            break;                 // terminator geldi → okumayı bitir
        }

        buffer[idx++] = c;         // buffer’a ekle
    }

    buffer[idx] = '\0';           // null terminator
    return idx;                   // okunan karakter sayısı
}

void USART1_IRQHandler(void)
{
    if(USART1->SR & 0x00000008)
    {
        printf("overrun error occured/n");
    }

    // get character from data reg
    uint8_t in_char = (USART1->DR & 0xFF);


}


void error_handler(){



}
