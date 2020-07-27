#include <msp430.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <libTimer.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"

void main(void) 
{  
  configureClocks();
  lcd_init();
  switch_init();
  led_init();
  buzzer_init();

  clearScreen(COLOR_ROYAL_BLUE);
  drawString8x12(37,10,"Teehee", COLOR_WHITE, COLOR_BLACK);
  drawString8x12(17,25,"Press Sumn", COLOR_WHITE, COLOR_BLACK);
  
  or_sr(0x18);  // CPU off, GIE on
} 
