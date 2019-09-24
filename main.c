#include "main.h"

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

int main(void)
{

    /* Initialize UART */
    UART0_Init();           // Initialize UART0
    InterruptEnable(INT_VEC_UART0);       // Enable UART0 interrupts
    UART0_IntEnable(UART_INT_RX | UART_INT_TX); // Enable Receive and Transmit interrupts
    InterruptMasterEnable();      // Enable Master (CPU) Interrupts

    initCommandTable();
    initCommandString();

    buffer_ptr buffer_RX = bufferInit();

    printf("Print Test.");

    while(1)
    {
    	/* Wait for input data */
		GotData = FALSE;
		while (!GotData) ;
        pollRX(buffer_RX);
    }

    return 0;
}
