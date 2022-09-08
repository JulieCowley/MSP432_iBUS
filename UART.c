/******************************************************************************/
/**
*      @file : UART.c
*   @version : 0
*      @date : 10 December 2021
*    @author : J Cowley
*
*******************************************************************************/

#include "UART.h"



#define RX_BUFFER_SIZE 64
#define RX_BUFFER_ELEM_SIZE 1

static char rx_buffer[RX_BUFFER_SIZE];


volatile uint8_t rx_data;


//-----------------UART_Init()-----------------

void UART_Init(void){

    //Select Pins 3.2(RX) and 3.3(TX) for UART
    P3->SEL0 |= BIT2|BIT3;

    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST;         //Hold UART in Reset mode for configuration
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;   //Use SMCLK as source

    //set the baud rate to 115200
    EUSCI_A2->BRW = 0x06;                            // UCBR = 6
    EUSCI_A2->MCTLW |= EUSCI_A_MCTLW_OS16;           // enable over sampling mode in Modulation Control Word register
    EUSCI_A2->MCTLW |= (0x08 << EUSCI_A_MCTLW_BRF_OFS); // set BRF = 8
    EUSCI_A2->MCTLW |= (0x11 << EUSCI_A_MCTLW_BRS_OFS); // set BRS = 0x11

    //initialize the RX ring buffer
    rb_config_t rx_config = {sizeof(rx_buffer[0]), RX_BUFFER_SIZE, rx_buffer};

    if(ringBuffer_Init(&rx_config) == 0){
        //make UART operational
        EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

        //enable receive interrupts
        EUSCI_A2->IE |= EUSCI_A_IE_RXIE;
    }
}


//------------- UART_getchar() ------------------
int UART_getchar(void){
    int retval = -1;
    char c = 1;
    if(ringBuffer_read(&c) == 0){
        retval = (int) c;
    }
    return retval;
}

//----------UART_RX_Interrupt_Handler------------

//receive info from iBUS
void EUSCIA2_IRQHandler(void){
    uint16_t status = EUSCI_A2->IFG;      // grab the current status of the interrupt register

    if(status & EUSCI_A_IFG_RXIFG){
        const char c = EUSCI_A2->RXBUF;
        ringBuffer_write(&c);
        EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;  // clear the RX interrupt flag

    }
}



