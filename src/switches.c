#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"
#include <lcdutils.h>
#include <lcddraw.h>

/*char SW1_state_down,SW2_state_down,SW3_state_down,SW4_state_down; */
char state, switch_state_down, switch_state_changed; /* effectively boolean */
int redrawScreen;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  switch_interrupt_handler();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  if(p2val & SW1 ? 0 : 1){
    state_advance(1);
    redrawScreen = 1;
  }
  else if(p2val & SW2 ? 0 : 1){
    state_advance(2);
    redrawScreen = 1;
  }
  else if(p2val & SW3 ? 0 : 1){
    state_advance(3);
    redrawScreen = 1;
  }
  else if(p2val & SW4 ? 0 : 1){
    state_advance(4);
    redrawScreen = 1;
  }
}
