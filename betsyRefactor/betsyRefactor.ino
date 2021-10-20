#include <FastLED.h>

#include "utils.h"
#include "Spiral.h"

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(0));

  FastLED.addLeds<NEOPIXEL, 26>(leds[0],  7, 17);  // row 0,  17 leds
  FastLED.addLeds<NEOPIXEL, 27>(leds[1],  7, 17);  // row 1,  17 leds
  FastLED.addLeds<NEOPIXEL, 28>(leds[2],  6, 19);  // row 2,  19 leds
  FastLED.addLeds<NEOPIXEL, 29>(leds[3],  5, 21);  // row 3,  21 leds
  FastLED.addLeds<NEOPIXEL, 30>(leds[4],  5, 21);  // row 4,  21 leds
  FastLED.addLeds<NEOPIXEL, 31>(leds[5],  4, 23);  // row 5,  23 leds
  FastLED.addLeds<NEOPIXEL, 32>(leds[6],  4, 23);  // row 6,  23 leds
  FastLED.addLeds<NEOPIXEL, 33>(leds[7],  3, 25);  // row 7,  25 leds
  FastLED.addLeds<NEOPIXEL, 34>(leds[8],  3, 25);  // row 8,  25 leds
  FastLED.addLeds<NEOPIXEL, 35>(leds[9],  2, 27);  // row 9,  27 leds
  FastLED.addLeds<NEOPIXEL, 36>(leds[10], 1, 29);  // row 10, 29 leds
  FastLED.addLeds<NEOPIXEL, 37>(leds[11], 1, 29);  // row 11, 29 leds
  FastLED.addLeds<NEOPIXEL, 38>(leds[12], 0, 31);  // row 12, 31 leds
  FastLED.addLeds<NEOPIXEL, 39>(leds[13], 0, 31);  // row 13, 31 leds
  FastLED.addLeds<NEOPIXEL, 40>(leds[14], 0, 31);  // row 14, 31 leds
  FastLED.addLeds<NEOPIXEL, 41>(leds[15], 1, 29);  // row 15, 29 leds
  FastLED.addLeds<NEOPIXEL, 42>(leds[16], 1, 29);  // row 16, 29 leds
  FastLED.addLeds<NEOPIXEL, 43>(leds[17], 2, 27);  // row 17, 27 leds
  FastLED.addLeds<NEOPIXEL, 44>(leds[18], 3, 25);  // row 18, 25 leds
  FastLED.addLeds<NEOPIXEL, 45>(leds[19], 3, 25);  // row 19, 25 leds
  FastLED.addLeds<NEOPIXEL, 46>(leds[20], 4, 23);  // row 20, 23 leds
  FastLED.addLeds<NEOPIXEL, 47>(leds[21], 4, 23);  // row 21, 23 leds
  FastLED.addLeds<NEOPIXEL, 48>(leds[22], 5, 21);  // row 22, 21 leds
  FastLED.addLeds<NEOPIXEL, 49>(leds[23], 5, 21);  // row 23, 21 leds
  FastLED.addLeds<NEOPIXEL, 50>(leds[24], 6, 19);  // row 24, 19 leds
  FastLED.addLeds<NEOPIXEL, 51>(leds[25], 7, 17);  // row 25, 17 leds
  FastLED.addLeds<NEOPIXEL, 52>(leds[26], 7, 17);  // row 26, 17 leds
}

void loop() {
  playSpirals();
}

void playSpirals() {
  Spiral spiral;
  for (int density = 0; density <= 6; density++) {
    spiral.withDensity(density).directionInward().play(2);
  }
  for (int density = 0; density <= 6; density++) {
    spiral.withDensity(density).directionOutward().play(2);
  }
}