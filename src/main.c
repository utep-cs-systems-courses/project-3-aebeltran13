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
  u_char width = screenWidth, height = screenHeight;
  clearScreen(COLOR_BLUE);

  drawString5x7(10,10,"WORD", COLOR_WHITE, COLOR_RED);
  
  switch_init();
  led_init();
  buzzer_init();

  or_sr(0x18);  // CPU off, GIE on
} 
