/*
File:main.c

Author:Kaan Acar
*/
#include<stdint.h>
#include "uart.h"
#include "common_defines.h"


char Buffer[20]={0};
int maxLen=20;

int main(void)
{
    init_hardware();
    uart_putbyte('\n');

    while (1)
    {



    }

    return 0;
}



void USART1_IRQHandler(void)
{
    if(USART1->SR & 0x00000008)
    {
        error_handler();
    }


    uint8_t in_char = (USART1->DR & 0xFF);


}

void TIM2_IRQn(void){

    uart_put_string(Buffer,maxLen,'/n');


}

void error_handler(){

while(1){



}

}
