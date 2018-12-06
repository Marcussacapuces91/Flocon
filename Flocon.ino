#include <TimerOne.h>
#include "Flocon.h"

Flocon flocon;

void PWM() {
  flocon.pwm();
}

void setup() {
  flocon.setup();
  flocon.clear();

  Timer1.initialize(25); // freq (µs)
  Timer1.attachInterrupt(PWM);
}

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
