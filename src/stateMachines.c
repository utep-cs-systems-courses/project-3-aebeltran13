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
    clearScreen(COLOR_BLUE);
    drawMOON();
    led_dim();
    state = 0;
    break;
  case 2:
    clearScreen(COLOR_SKY_BLUE);
    songBGR();
    song();
    state = 0;
    break;
  case 3:
    fillTeehee();
    siren_song();
    state = 0;
    break;
  case 4:
    clearScreen(COLOR_FOREST_GREEN);
    drawFace();
    led_siren();
    state = 0;
    break;
  default:
    break;
  }
}
