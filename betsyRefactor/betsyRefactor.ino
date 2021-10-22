#include <FastLED.h>

#include "utils.h"
#include "Colors.h"
#include "Timer.h"
#include "Spiral.h"
#include "Paintbrush.h"

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
  paint();
  //hourLoop();
}

void paint() {
  Paintbrush paintbrush;

  // TODO how come new brushes still start at the top?

  // Paint the canvas blue
  //paintbrush.color(CHSV_BLUE, CHSV_DODGERBLUE).play(minutes(1));
  paintbrush.color(CHSV_BLUE, CHSV_BLUE).speed(0.5).play(seconds(30));

  // Paint over the blue with yellow, blend to green
  paintbrush.color(CHSV_YELLOW, CHSV_YELLOW).blend().play(minutes(3));

  // Erase the canvas with black
  paintbrush.color(CHSV_GREEN).erase().play(minutes(3));

  // Paint the canvas slowly with firey red/gold
  paintbrush.color(CHSV_RED, CHSV_YELLOW).speed(0.1).play(minutes(3));

  // Erase quickly
  paintbrush.color(CHSV_RED, CHSV_YELLOW).erase().speed(10).play(minutes(1));

  // Paint a rainbow
  paintbrush.rainbow().speed(0.5).play(minutes(1));
}

void hourLoop() {
  spirals();
}

void spirals() {
  Spiral spiral;
  for (int density = 0; density <= 6; density++) {
    spiral.withDensity(density).directionInward().play(2);
  }
  for (int density = 0; density <= 6; density++) {
    spiral.withDensity(density).directionOutward().play(2);
  }
}
