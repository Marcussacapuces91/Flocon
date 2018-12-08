#pragma once

#include <Arduino.h>

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
