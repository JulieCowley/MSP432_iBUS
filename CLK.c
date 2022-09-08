/******************************************************************************/
/**
*      @file : CLK.c
*   @version : 0
*      @date : 22 December 2021
*    @author : J Cowley
*
*******************************************************************************/

#include "CLK.h"

volatile uint32_t msTicks = 0;


//-------------- SMCLK 12MHz Init() --------------------------------------
void SMCLK_12MHz_Init(void){
    CS->KEY = CS_KEY_VAL;                //open CS registers
    CS->CTL0 &= ~CS_CTL0_DCORSEL_MASK;   //Clear default frequency of 3MHz
    CS->CTL0 |= CS_CTL0_DCORSEL_3;       //SET DCO frequency to 12MHz
    CS->CTL1 |= CS_CTL1_SELS_3;          //Select DCO as SMCLK source
    CS->CTL1 |= CS_CTL1_SELM_3;          //Select 12MHZ DCO as core clock
    CS->KEY = 0;                         //lock CS registers


    //Initialize SysTick 1ms Interrupt
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);
}

//-------------- SysTick Interrupt Handler --------------------------------
void SysTick_Handler(void)  {
  msTicks++; // Increment msTicks every 1ms
}


//----------------------- millis() ----------------------------------------
uint32_t millis(){
    return msTicks;
}


//-------------- SMCLK 16MHz Init() ---------------------------------------
void SMCLK_16MHz_Init(void){
     CS->KEY = CS_KEY_VAL;                //open CS registers
     CS->CTL0 &= ~CS_CTL0_DCORSEL_MASK;   //Clear default frequency of 3MHz
     CS->CTL0 |= CS_CTL0_DCORSEL_3;       //Select frequency range 3

     //tune DCO to 16MHz
     CS->CTL0 &= ~(CS_CTL0_DCOTUNE_MASK); //clear DCOTUNE bits

     /*tried using equation from p.387 of Technical reference manual and got 93 for N_DCOTUNE,
         const int TARGET_FREQ = 16;          //some equation variables
         const int CENTER_FREQ = 12;

         //get DCOTUNE equation vals K and FCAL
         const uint32_t FCAL = TLV->DCOIR_FCAL_RSEL04; // FCAL = 396
         const float K = TLV->DCOIR_CONSTK_RSEL04;     // K = 1.00084627e09

         //calculate N_DCOTUNE (equation found on p.386 of MSP432 technical reference manual)
         //int N_DCOTUNE = ((TARGET_FREQ - CENTER_FREQ)*(1+K*(768-FCAL)))/(K*TARGET_FREQ);*/


     //trial and error to get 139 instead, which works for my timer
     int N_DCOTUNE = 139;
     CS->CTL0 |= (N_DCOTUNE & CS_CTL0_DCOTUNE_MASK);

     CS->CTL1 |= CS_CTL1_SELS_3;          //Select DCO as SMCLK source
     CS->CTL1 |= CS_CTL1_SELM_3;
     CS->KEY = 0;                         //lock CS registers
 }



