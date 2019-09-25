#include "main.h"

buffer_ptr buffer_RX;
buffer_ptr buffer_TX;

void InterruptEnable(unsigned long InterruptIndex)
{
    /* Indicate to CPU which device is to interrupt */
    if(InterruptIndex < 32)
        NVIC_EN0_R = 1 << InterruptIndex;       // Enable the interrupt in the EN0 Register
    else
        NVIC_EN1_R = 1 << (InterruptIndex - 32);    // Enable the interrupt in the EN1 Register
}


void InterruptMasterEnable(void)
{
    /* enable CPU interrupts */
    __asm(" cpsie   i");
}


void main(void)
{

    /* Initialize UART */
    UART0_Init();           // Initialize UART0
    InterruptEnable(INT_VEC_UART0);       // Enable UART0 interrupts
    UART0_IntEnable(UART_INT_RX | UART_INT_TX); // Enable Receive and Transmit interrupts
    InterruptMasterEnable();      // Enable Master (CPU) Interrupts

    initCommandTable();
    initCommandString();

    buffer_RX = bufferInit();
    buffer_TX = bufferInit();

    while(1)
    {
        pollRX(buffer_RX);
    }
}
