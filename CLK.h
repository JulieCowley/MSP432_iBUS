/******************************************************************************/
/**
*      @file : CLK.h
*   @version : 0
*      @date : 9 September 2021
*    @author : J Cowley
*
*******************************************************************************/

#ifndef CLK_H
#define CLK_H

/*******************************    LIBRARIES   *******************************/

#include "msp.h"

/*******************************   FUNCTIONS    *******************************/

void SMCLK_12MHz_Init(void); // Initializes SMCLK to 12MHz
void SMCLK_16MHz_Init(void); // Initializes SMCLK to 16MHz
uint32_t millis();


#endif









