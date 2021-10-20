#ifndef UTILS_H
#define UTILS_H

#include <FastLED.h>

#define NUM_ROWS      27
#define NUM_COLUMNS   31
#define RADIUS        16

CRGB leds[NUM_ROWS][NUM_COLUMNS];

struct px {
  double row;
  double col;
  int rowInt() {
    return (int)row;
  }
  int colInt() {
    return (int)col;
  }
  bool inBounds() {
    return row > 0 && row < NUM_ROWS && col > 0 && col < NUM_COLUMNS;
  }
  px getRounded(int deg) {
    if ((deg >= 0 && deg < 90) || (deg > 180 && deg < 270)) {
      return {floor(row), ceil(col)};
    } else {
      return {floor(row), floor(col)};
    }
  }
};

px ORIGIN = {NUM_ROWS / 2, NUM_COLUMNS / 2};

px pointOnCircumference(double radius, px origin, double d) {
  double degs = (d - 90 < 0) ? (d + 270) : (d - 90);
  double rads = degs * PI / 180;
  return {
    origin.row + radius * sin(rads),
    origin.col + radius * cos(rads)
  };
}

void allBlack() {
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLUMNS; col++) {
      leds[row][col] = CRGB::Black;
    }
  }
}

#endif
