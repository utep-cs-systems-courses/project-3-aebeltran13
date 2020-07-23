#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

/* This is the state machine */
void state_advance(int state){
  switch(state){
  case 1:
    led_dim();
    clearScreen(COLOR_BLUE);
    state = 0;
    break;
  case 2:
    clearScreen(COLOR_ROYAL_BLUE);
    song();
    drawString8x12(10,10,"This is a screen", COLOR_GREEN, COLOR_BLUE);
    drawString8x12(10,22,"where words should", COLOR_GREEN, COLOR_BLUE);
    drawString8x12(10,34,"appear. Hello!", COLOR_GREEN, COLOR_BLUE);
    drawString8x12(10,46,"And Goodbye!", COLOR_GREEN, COLOR_BLUE);
    state = 0;
    break;
  case 3:
    siren_song();
    state = 0;
    break;
  case 4:
    led_siren();
    state = 0;
    break;
  default:
    break;
  }
}
