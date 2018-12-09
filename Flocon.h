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
 * @file Flocon.h
 * @brief Declare & define Flocon class.
 * @licence https://opensource.org/licenses/mit-license.php
 * @author Marc Sibert
 */

#pragma once

#include <Arduino.h>


/**
 * Class for managing Flocon's hardware by a Arduino.
 * User should define pinout, using @see LEDS_ORDER.
 */
class Flocon {
public:
/**
 * Initialize all leds' pins as output and low level. Also zeroing all @vals.
 */
  void setup() {
    byte lo[LEDS];
    memcpy_P(&lo, LEDS_ORDER, sizeof(LEDS_ORDER));
    
    for (byte i = 0; i < LEDS ; ++i) {
      pinMode(lo[i], OUTPUT);
      digitalWrite(lo[i], LOW);
      vals[i] = 0;
    }
  }

/**
 * Inline pwm action, should be called regulary by interrupt.
 * Produce random ligtning regarding @vals value for each led. 
 * It is a way to mix current to all leds, but not all toghether.
 */
  inline
  void pwm() {
    static unsigned long rnd = 1;
    static byte nb = 0;
    
    rnd = (rnd * 69069) % 0x100000000;
    const byte lo = pgm_read_byte(LEDS_ORDER + nb);
    digitalWrite(lo, vals[nb] > byte(rnd) ? HIGH : LOW );
    if (++nb == LEDS) nb = 0;
  }

/**
 * Clear all leds.
 */
  void clear() {
    for (byte i = 0; i < LEDS ; ++i) {
      vals[i] = 0;
    }
  }

/**
 * Set a led brightness.
 * @param led Led rank between [0..17]
 * @param val Brightness value in [0..255]
 */
  void setLed(const byte led, const byte val) {
    vals[led] = val;
  }

/**
 * Set central leds brightness.
 * @param val Brightness value in [0.255].
 */
  void center(const byte val) {
    for (byte i = 0; i < 6 ; ++i) {
      vals[i] = val;
    }
  }

/**
 * Set median leds brightness.
 * @param val Brightness value in [0.255].
 */
  void median(const byte val) {
    for (byte i = 6; i < 12 ; ++i) {
      vals[i] = val;
    }
  }

/**
 * Set external leds brightness.
 * @param val Brightness value in [0.255].
 */
  void external(const byte val) {
    for (byte i = 12; i < 18 ; ++i) {
      vals[i] = val;
    }
  }

  void vertical(const byte rank, const byte val) {
    clear();
    switch (rank) {
      case 1 :
        setLed(13, val);
        setLed(14, val);
        break;
      case 2 :
        setLed(7, val);
        setLed(8, val);
        break;
      case 3 :
        setLed(1, val);
        break;
      case 4 :
        setLed(0, val);
        setLed(2, val);
        setLed(6, val/8);
        setLed(9, val/8);
        break;
      case 5 :
        setLed(12, val);
        setLed(15, val);
        setLed(6, val);
        setLed(9, val);
        break;
      case 6 :
        setLed(3, val);
        setLed(5, val);
        setLed(6, val/8);
        setLed(9, val/8);
        break;
      case 7 :
        setLed(4, val);
        break;
      case 8 :
        setLed(10, val);
        setLed(11, val);
        break;
      case 9 :
        setLed(16, val);
        setLed(17, val);
        break;
    }
  }

/**
 * Flash one led.
 * @param i led rank ou random if none indicated.
 */
  void flash(const int i = -1) {
    static unsigned long rnd = 1;
    
    rnd = (rnd * 69069) % 0x100000000;
    const byte l = (i == -1) ? rnd % LEDS : i % LEDS;
    const byte v = vals[l];
    vals[l] = 255;
    delay(25);
    vals[l] = v;
  }
  
private:
/// Number of leds
  static const byte LEDS = 18;

/// Leds port oder fron inner to outer.  
  static const byte LEDS_ORDER[LEDS] PROGMEM;

/// Storage for each led wanted brightness.
  volatile byte vals[LEDS];

};

/**
 * Depending of your leds order, fill that array.
 */
const byte Flocon::LEDS_ORDER[LEDS] PROGMEM = { 10, 5, 2, 13, A4, A0, 12, 7, 3, 8, A5, A3, 11, 6, 4, 9, A1, A2 };
