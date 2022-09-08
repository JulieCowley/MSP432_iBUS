/******************************************************************************/
/**
*      @file : UART.h
*   @version : 0
*      @date : 10 December 2021
*    @author : J Cowley
*
*******************************************************************************/
#ifndef UART_H
#define UART_H

/*******************************    LIBRARIES   *******************************/

#include "msp.h"
#include "ringBuffer.h"

/*******************************    FUNCTIONS   *******************************/

//--------------UART_Init()-------------------------------
//  @brief:     A function to initialize UART on pins 3.2(RX) and 3.3(TX)
//  @detail:    initializes (EUSCI_A2) with a baud rate of 115200
//  @param:     none
//  @return:    none

void UART_Init(void);


//--------------UART_getchar()-------------------------------
//  @brief:     A function to read a character from the rx buffer
//  @detail:
//  @param:     none
//  @return:    -1 if buffer is empty, else a char from the buffer

int UART_getchar(void);


#endif
