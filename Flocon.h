#pragma once

#include <Arduino.h>

#define LEDS 18
#define LED_ORDER { 10, 5, 2, 13, A4, A0, 12, 7, 3, 8, A5, A3, 11, 6, 4, 9, A1, A2 }

class Flocon {
public:
  Flocon() :
    leds LED_ORDER
  {};

  void setup() {
    for (byte i = 0; i < LEDS ; ++i) {
      pinMode(leds[i], OUTPUT);
      digitalWrite(leds[i], LOW);
    }
  }

  inline
  void pwm() {
    static unsigned long rnd = 1;
    static byte nb = 0;
    
    rnd = (rnd * 69069) % 0x100000000;
    digitalWrite(leds[nb], vals[nb] > ((rnd) % 256) ? HIGH : LOW );
    nb = (nb + 1) % LEDS;
  }

  void clear() {
    for (byte i = 0; i < LEDS ; ++i) {
      vals[i] = 0;
      digitalWrite(leds[i], LOW);
    }
  }

  void center(const byte val) {
    for (byte i = 0; i < 6 ; ++i) {
      vals[i] = val;
    }
  }

  void median(const byte val) {
    for (byte i = 6; i < 12 ; ++i) {
      vals[i] = val;
    }
  }

  void external(const byte val) {
    for (byte i = 12; i < 18 ; ++i) {
      vals[i] = val;
    }
  }

  void flash(const int i = -1) {
    static unsigned long rnd = 1;
    
    if (i == -1) {
      rnd = (rnd * 69069) % 0x100000000;
      const byte v = vals[rnd % LEDS];
      vals[rnd % LEDS] = 255;
      delayMicroseconds(100);
      vals[rnd % LEDS] = v;
    } else {
      const byte v = vals[i % LEDS];
      vals[i % LEDS] = 255;
      delayMicroseconds(100);
      vals[i % LEDS] = v;
    }
  }
  
private:
  const byte leds[LEDS];
  volatile byte vals[LEDS];
  

};
