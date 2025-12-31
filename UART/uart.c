void init_hardware(void)
{
    init_clock();
    init_usart(USART_BAUD);
    init_timer();
}
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

    // Timer yapılandırma
    RCC->APB1ENR |= 0x00000001;   // TIM2 clock aç

    TIM2->PSC = 8000 - 1;   // Prescaler: 8000
    TIM2->ARR = 1000 - 1;   // Auto-reload: 1000

    TIM2->DIER |= 0x00000001;   // Update interrupt enable
    NVIC_EnableIRQ(TIM2_IRQn);    // NVIC interrupt enable

    TIM2->CR1 |= 0x00000001;     // Timer’i başlat

}
void init_usart(uint32_t baudrate)
{
    RCC->APB2ENR    |= 0x00000004;      // enable GPIOA clock
    RCC->APB2ENR    |= 0x00004000;    // enable USART1 clock

    GPIOA->CRH &= ~(0x000000C0  | 0x00000030);   // reset PA9
    GPIOA->CRH &= ~(0x00000C00 | 0x00000300);  // reset PA10

    GPIOA->CRH |= 0x00000020 | 0x00000010;  // 0b11 50MHz output
    GPIOA->CRH |= 0x00000080;    // PA9: output @ 50MHz - Alt-function Push-pull
    GPIOA->CRH |= 0x00000400;   // PA10 RX - Mode = 0b00 (input) - CNF = 0b01 (input floating)

    // configure USART1 registers
    uint32_t baud   = (uint32_t)(8 000 000/baudrate);
    USART1->BRR     = baud;
    USART1->CR1     = 0x00000008 | 0x00000004 | 0x00000020 | 0x00002000;

    // configure NVIC
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

void nvic_enable_irq(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {

    NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));

  }
}
