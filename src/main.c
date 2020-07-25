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

  or_sr(0x18);  // CPU off, GIE on
} 
