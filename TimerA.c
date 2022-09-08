/******************************************************************************/
/**
*      @file : TimerA.c
*   @version : 0
*      @date : 17 December 2021
*    @author : J Cowley
*
*******************************************************************************/


#include "TimerA.h"


//----------------------PWM_Init()---------------------------
void TA0_PWM_Init(uint16_t period, uint16_t duty1){
    P2->DIR |= (BIT4|BIT5|BIT6|BIT7);     //set Pin 2.4 thru 2.7 as output
    P2->SEL0|= (BIT4|BIT5|BIT6|BIT7);     //Select TimerA functionality
    P2->SEL1 &= ~(BIT4|BIT5|BIT6|BIT7);

    TIMER_A0->CCR[0] = period;   //set the counter compare register = to the period

    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_2;     //set output mode to Toggle/Reset  **PIN 2.4
    TIMER_A0->CCR[1] = duty1;                       //set initial duty cycle

    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_2;     //set output mode to Toggle/Reset  **PIN 2.5            // Pin 2.5 is busted on my launchpad
    TIMER_A0->CCR[2] = duty1;                       //set initial duty cycle

    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_2;     //set output mode to Toggle/Reset  **PIN 2.6
    TIMER_A0->CCR[3] = duty1;                       //set initial duty cycle

    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_2;     //set output mode to Toggle/Reset  **PIN 2.7
    TIMER_A0->CCR[4] = duty1;                       //set initial duty cycle


    TIMER_A0->EX0 = TIMER_A_EX0_IDEX__3;            //Divide clk by 3

    TIMER_A0->CTL = (TIMER_A_CTL_SSEL__SMCLK|       //Select SMCLK as as TimerA0 CLK source
                         TIMER_A_CTL_ID__2|         //Divide CLK source by 2
                         TIMER_A_CTL_MC__UPDOWN|    //Configure as up/down counter (essentially divides clk by another 2)
                         TIMER_A_CTL_CLR|
                         TIMER_A_CTL_IE);           //Enable Interrupts

}


