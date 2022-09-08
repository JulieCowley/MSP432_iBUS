/**************************************
 *          iBUS Test
 * ************************************
 * Goal: Read iBUS signal via UART and receive PWM data for motors
 *
 *
 *
 * TO DO:
 * - *DONE* initialize UART 115200 baud rate
 * - *DONE* set up UART receive interrupt (EUSCIA2 ?) pin 3.2 on the launch pad
 * - *DONE* iBUS Protocol
 * - *DONE* implement millis() so that we can time events in the protocol
 *
 */

#include "msp.h"
#include "TimerA.h"
#include "CLK.h"
#include "UART.h"
#include "iBUS.h"


#define PERIOD 20000
#define INIT_DUTY_CYCLE 1000

uint16_t ch1 = 1000;
uint16_t ch2 = 1000;
uint16_t ch3 = 1000;
uint16_t ch4 = 1000;

#define RED_LED   BIT0  //connect red led to pin2
#define GREEN_LED BIT1  //connect green led to pin3

enum States{DISARMED,ARMED};
uint8_t state = DISARMED;    //set initial state to disarmed

void updateState(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    P2->DIR = RED_LED | GREEN_LED;
    P2->OUT = RED_LED;

    // configure clocks
    SMCLK_12MHz_Init();
    TA0_PWM_Init(PERIOD, INIT_DUTY_CYCLE);
    UART_Init();
    iBUS_Init();

    //Enable interrupts
    NVIC_EnableIRQ(TA0_N_IRQn);
    NVIC_EnableIRQ(EUSCIA2_IRQn);
    __enable_interrupts();

    while(1){
        iBUS_loop();
        updateState();

        ch1 = iBUS_readChannel(0);
        ch2 = iBUS_readChannel(1);
        ch3 = iBUS_readChannel(2);
        ch4 = iBUS_readChannel(3);



    } //wait for an interrupt

}

//Update a new PWM signal every 20ms
void TA0_N_IRQHandler(void){
    TIMER_A0->CCR[1] = ch1;
    TIMER_A0->CCR[2] = ch2;
    TIMER_A0->CCR[3] = ch3;
    TIMER_A0->CCR[4] = ch4;
    TIMER_A0->CTL &= ~TAIFG;
}


void updateState(void){
  switch(state){
    case ARMED:
      P2->OUT |= GREEN_LED;      //turn on red led on pin2
      P2->OUT &= ~(RED_LED); //turn off green led on pin3
      //check to see if state is ARMED
      if(ch3 < 1040 && ch4<1040 && ch4 > 1000){
        state = DISARMED;       //thrust down, yaw left to arm
      }
      break;

    case DISARMED:
      P2->OUT |= RED_LED;    //turn on green led on pin3
      P2->OUT &= ~(GREEN_LED);   //turn off led on pin2
      //check to see if state is DISARMED
      if(ch3 < 1040 && ch4>1960){
        state = ARMED;    //thrust down, yaw right to disarm
      }
      break;
  }
}













