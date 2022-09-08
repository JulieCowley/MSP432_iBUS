/******************************************************************************/
/**
*      @file : TimerA.h
*      @date : 17 December 2021
*    @author : J Cowley
*
*******************************************************************************/
#ifndef TIMER_A_H
#define TIMER_A_H

/*******************************    LIBRARIES   *******************************/

#include "msp.h"

/*******************************    FUNCTIONS   *******************************/

//--------------PWM_Init()----------------------------------
//  @brief:     A function to initialize PWM with Timer A0 (pins 2.4, 2.5, 2.6, 2.7)
//  @detail:    Initializes pins 2.4 thru 2.7 for PWM output and
//              configures TimerA0 in UPDOWN mode with interrupts enabled
//  @param:     period(20,000) and duty1(initial duty cycle)
//  @return:    none

void TA0_PWM_Init(uint16_t period, uint16_t duty1);

#endif
