#include <FastLED.h>

CRGB leds[650];

void setup() {
  randomSeed(analogRead(0));
  FastLED.addLeds<NEOPIXEL, 26>(leds, 0, 18);   // 0/17
  FastLED.addLeds<NEOPIXEL, 27>(leds, 17, 17);  // 1/17
  FastLED.addLeds<NEOPIXEL, 28>(leds, 34, 19);  // 2/19
  FastLED.addLeds<NEOPIXEL, 29>(leds, 53, 21);  // 3/21
  FastLED.addLeds<NEOPIXEL, 30>(leds, 74, 21);  // 4/21
  FastLED.addLeds<NEOPIXEL, 31>(leds, 95, 23);  // 5/23
  FastLED.addLeds<NEOPIXEL, 32>(leds, 118, 23); // 6/23
  FastLED.addLeds<NEOPIXEL, 33>(leds, 141, 25); // 7/25
  FastLED.addLeds<NEOPIXEL, 34>(leds, 166, 25); // 8/25
  FastLED.addLeds<NEOPIXEL, 35>(leds, 191, 27); // 9/27
  FastLED.addLeds<NEOPIXEL, 36>(leds, 218, 29); // 10/29
  FastLED.addLeds<NEOPIXEL, 37>(leds, 247, 29); // 11/29
  FastLED.addLeds<NEOPIXEL, 38>(leds, 276, 31); // 12/31
  FastLED.addLeds<NEOPIXEL, 39>(leds, 307, 31); // 13/31
  FastLED.addLeds<NEOPIXEL, 40>(leds, 338, 31); // 14/31
  FastLED.addLeds<NEOPIXEL, 41>(leds, 369, 29); // 15/29
  FastLED.addLeds<NEOPIXEL, 42>(leds, 398, 29); // 16/29
  FastLED.addLeds<NEOPIXEL, 43>(leds, 427, 27); // 17/27
  FastLED.addLeds<NEOPIXEL, 44>(leds, 454, 25); // 18/25
  FastLED.addLeds<NEOPIXEL, 45>(leds, 479, 25); // 19/25
  FastLED.addLeds<NEOPIXEL, 46>(leds, 504, 23); // 20/23
  FastLED.addLeds<NEOPIXEL, 47>(leds, 527, 23); // 21/23
  FastLED.addLeds<NEOPIXEL, 48>(leds, 550, 21); // 22/21
  FastLED.addLeds<NEOPIXEL, 49>(leds, 571, 21); // 23/21
  FastLED.addLeds<NEOPIXEL, 50>(leds, 592, 19); // 24/19
  FastLED.addLeds<NEOPIXEL, 51>(leds, 611, 17); // 25/17
  FastLED.addLeds<NEOPIXEL, 52>(leds, 628, 17); // 26/17
  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {
  for (int i = 0; i < 650; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
}
