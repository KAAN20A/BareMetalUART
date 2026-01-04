/*
File:common_defines.c

Author:Kaan Acar
*/
#include"common_defines.h"

void init_clock(void)
{

    FLASH->ACR      |= 0x00000004;
    RCC->CFGR       |= 0x00000400;
    RCC->CR         |= 0x00010000;
    while( !(RCC->CR & 0x00020000) );

    RCC->CFGR       |= 0x00010000;
    RCC->CFGR       |= 0x001C0000;
    RCC->CR         |= 0x01000000;
    while( !(RCC->CR & 0x02000000) );

    RCC->CFGR       |= 0x00000002U;

    while( !(RCC->CFGR & 0x00000008U) );
}


void init_timer(void)
{

    RCC->APB1ENR |= 0x00000001;

    TIM2->PSC = 8000 - 1;
    TIM2->ARR = 1000 - 1;

    TIM2->DIER |= 0x00000001;
    nvic_enable_irq(TIM2_IRQn);

    TIM2->CR1 |= 0x00000001;

}

void nvic_enable_irq(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {

    NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));

  }
}
