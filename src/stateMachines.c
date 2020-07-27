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
    fillCircle(50,50,15,COLOR_PINK);
    led_dim();
    state = 0;
    break;
  case 2:
    clearScreen(COLOR_SKY_BLUE);
    drawString8x12(10,60,"Its pretty", COLOR_GREEN, COLOR_BLUE);
    drawString8x12(30,72,"huh", COLOR_GREEN, COLOR_BLUE);
    fillTriangle(10,10,10,COLOR_YELLOW);
    fillTriangle(30,110,45,COLOR_YELLOW);
    fillTriangle(70,25,25,COLOR_ORANGE);
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
