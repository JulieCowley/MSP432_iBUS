/******************************************************************************/
/**
*      @file : iBUS.h
*   @version : 0
*      @date : 23 December 2021
*    @author : J Cowley
*
*
*
*******************************************************************************/
#ifndef iBUS_H
#define iBUS_H

/*******************************    LIBRARIES   *******************************/

#include "msp.h"
#include "UART.h"

/*******************************    FUNCTIONS   *******************************/


//--------------------- iBUS_Init() ----------------------------------
//  @brief:     initializes the iBUS struct in iBUS.c
//  @detail:
//  @param:     none
//  @return:    none
void iBUS_Init(void);


//--------------------- iBUS_loop() ----------------------------------
//  @brief:     decodes data packets coming from UART2 on pin 3.2
//  @detail:    to be called in a main loop
//  @param:     none
//  @return:    none
void iBUS_loop(void);


//---------------- iBUS_readChannel() ----------------------------------
//  @brief:     reads a channel from the iBUS struct
//  @detail:
//  @param:     a channel number between 0 and 9
//  @return:    16 bit PWM value of specified channel (1000 - 2000 ms)
uint16_t iBUS_readChannel(uint8_t channelNum);


#endif /* iBUS_H */















