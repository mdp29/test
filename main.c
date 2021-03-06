/*!*****************************************************************************
 * @file
 * Test UART.


struct wtimer_desc __xdata wtdesc;
uint8_t ledsave;

void wtcallback(struct wtimer_desc __xdata *desc)
{
    wtdesc.time += 320;
    wtimer0_addabsolute(&wtdesc);
    led0_toggle();
}


#endif
{
    DPS = 0;

    EIE = 0x00;
    E2IE = 0x00;
    IE = 0x00;
    GPIOENABLE = 1;

    if (PCON & 0x40)    return warmstart;
    else                return coldstart;
}

#undef coldstart
#undef warmstart

#if defined(SDCC)
extern uint8_t _start__stack[];
#endif

void main(void)
{
#if !defined(SDCC) && !defined(__ICC8051__)
    _sdcc_external_startup();
#endif

#if defined(SDCC)
    __asm
    G$_start__stack$0$0 = __start__stack
    .globl G$_start__stack$0$0
    __endasm;
#endif

    flash_apply_calibration();

    CLKCON = 0x00;

    if (!(PCON & 0x40))
    {
        DIRC |= 0x04;
        PALTC |= 0x04;
        PINSEL |= 0x08;
        uart_timer1_baud(CLKSRC_FRCOSC, 9600, 20000000);
        uart0_init(1, 8, 1);
    }

    EA = 1;

    PCON = 0x0C;

    for (;;)
    {
#ifdef TEST_UART_RX
        if(uart0_rxcount())
        {
            uart0_tx(uart0_rx());       // TODO question 1
        }
        else
        {
            uart0_poll();
        }
#endif

#ifdef TEST_UART_TX
        delay(0xffff);                  // TODO question 2
        uart0_tx('s');
#endif
    }
}
