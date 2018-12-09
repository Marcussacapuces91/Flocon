/**
 *  Copyright (c) 2018 Marc Sibert
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the Software
 *  is furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 *  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * @file Flocon.ino
 * @licence https://opensource.org/licenses/mit-license.php
 * @author Marc Sibert
 */

#include "Flocon.h"
#include <TimerOne.h>
#include <avr/sleep.h>

Flocon flocon;

/**
 * Interrupt code.
 */
void PWM() {
  flocon.pwm();
}

unsigned readVcc() {
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  const uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  const uint8_t high = ADCH; // unlocks both
  const unsigned mesure = (high << 8) | low;

  const unsigned result = 1125300UL / mesure; // Calculate Vcc (in mV); 1125300 = 1.1 * 1023 * 1000
  return result; // Vcc in millivolts
}

/**
 * Setup the wall system, including timer1 & interrupt freq.
 */
void setup() {
  Serial.begin(250000);
  while(!Serial) {};

  flocon.setup();
  flocon.clear();

  Timer1.initialize(25); // 25 µs ~ 40 kHz => 18 leds => 1 led ~ 2.2 kHz before PWM !
  Timer1.attachInterrupt(PWM);
}

/**
 * Repetead animated sequence.
 */
void loop() {
  const unsigned vcc = readVcc();
  Serial.print(F("Voltage: "));
  Serial.println(vcc);

  if (vcc < 4800) {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
    sleep_enable();          // enables the sleep bit in the mcucr register
                             // so sleep is possible. just a safety pin    
    sleep_mode();            // here the device is actually put to sleep!!                             
  }

/*  

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

*/

  for (int i = 1; i <= 9; ++i) {
    flocon.vertical(i, 64);
    delay(50);
  }
  flocon.clear();
  delay(250);
  for (int i = 9; i >= 1; --i) {
    flocon.vertical(i, 64);
    delay(50);
  }
  flocon.clear();
  delay(250);


}
