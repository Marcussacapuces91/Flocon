#include <TimerOne.h>
#include "Flocon.h"

Flocon flocon;

/**
 * Interrupt code.
 */
void PWM() {
  flocon.pwm();
}

/**
 * Setup the wall system, including timer1 & interrupt freq.
 */
void setup() {
  flocon.setup();
  flocon.clear();

  Timer1.initialize(25); // 25 µs ~ 40 kHz => 18 leds => 1 led ~ 2.2 kHz before PWM !
  Timer1.attachInterrupt(PWM);
}

/**
 * Repetead animated sequence.
 */
void loop() {

  const byte maximum = 32;
  for (int i = 0; i < maximum; ++i) {
    flocon.center(i);
    delay(10);
  }
  for (int i = 0; i < maximum; ++i) {
    flocon.median(i);
    delay(10);
  }
  for (int i = 0; i < maximum; ++i) {
    flocon.external(i);
    flocon.center(maximum - 1 - i);
    delay(10);
  }
  for (int i = 0; i < maximum; ++i) {
    flocon.median(maximum - 1 - i);
    delay(10);
  }
  for (int i = 0; i < maximum; ++i) {
    flocon.external(maximum - 1 - i);
    delay(10);
  }
  
  delay(1000);

  for (int i = 0; i < 20; ++i) {
    flocon.flash();
    delay(50);
  }
  
  delay(1000);
}
