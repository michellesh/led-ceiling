#include <FastLED.h>

int thingWidth = 17;
int thingHeight = 10;

void thingScrollDiagonal() {
  for (int t = -thingHeight * 1.5, l = -thingWidth; t < NUM_ROWS && l < NUM_LEDS_MAX; l++, t++) {
    allBlack();
    bigRainbowThing(t, l);
    FastLED.show();
    delay(50);
  }
}

void thingScrollTopBottom() {
  for (int t = -thingHeight; t < NUM_ROWS; t++) {
    allBlack();
    bigRainbowThing(t, 8);
    FastLED.show();
    delay(50);
  }
}

void thingScrollLeftRight() {
  for (int l = -thingWidth; l < NUM_LEDS_MAX; l++) {
    allBlack();
    bigRainbowThing(10, l);
    FastLED.show();
    delay(50);
  }
}

void bigRainbowThing(int top, int left) {
  //int top = 10; // 13
  //int left = 8;

  columnRange(CRGB::Red, left, top + 1, top + 4);
  columnRange(CRGB::Red, left, top + 6, top + 9);

  columnRange(CRGB::OrangeRed, left + 1, top, top + 10);
  columnRange(CRGB::Yellow, left + 2, top, top + 10);
  columnRange(CRGB::Green, left + 3, top, top + 10);
  columnRange(CRGB::Blue, left + 4, top + 1, top + 9);

  columnRange(CRGB::Purple, left + 5, top + 3, top + 7);
  columnRange(CRGB::Red, left + 6, top + 3, top + 7);
  columnRange(CRGB::OrangeRed, left + 7, top + 3, top + 7);
  columnRange(CRGB::Yellow, left + 8, top + 3, top + 7);
  columnRange(CRGB::Green, left + 9, top + 3, top + 7);
  columnRange(CRGB::Blue, left + 10, top + 3, top + 7);
  columnRange(CRGB::Purple, left + 11, top + 3, top + 7);
  columnRange(CRGB::Red, left + 12, top + 3, top + 7);

  columnRange(CRGB::OrangeRed, left + 13, top + 2, top + 8);
  columnRange(CRGB::Yellow, left + 14, top + 2, top + 8);

  columnRange(CRGB::Green, left + 15, top + 3, top + 7);
  columnRange(CRGB::Blue, left + 16, top + 3, top + 7);

  columnRange(CRGB::Purple, left + 17, top + 4, top + 6);

  FastLED.show();
}

void columnRange(CRGB color, int x, int y1, int y2) {
  for (int y = y1; y < y2; y++) {
    if (inBounds(y, ctox(y, x))) {
      leds[getIndex(y, ctox(y, x))] = color;
    }
  }
}

void drawThing(int yanchor, int canchor) {
  int indices[6];
  indices[0] = getIndex(yanchor - 1, ctox(yanchor - 1, canchor)); // ball 1
  indices[1] = getIndex(yanchor, ctox(yanchor, canchor));
  indices[2] = getIndex(yanchor + 1, ctox(yanchor + 1, canchor)); // ball 2
  indices[3] = getIndex(yanchor, ctox(yanchor, canchor + 1));
  indices[4] = getIndex(yanchor, ctox(yanchor, canchor + 2));
  indices[5] = getIndex(yanchor, ctox(yanchor, canchor + 3)); 

  leds[indices[5]] = CRGB::Red;
  leds[indices[4]] = CRGB::OrangeRed;
  leds[indices[3]] = CRGB::Yellow;
  leds[indices[1]] = CRGB::Green;
  leds[indices[0]] = CRGB::Blue;
  leds[indices[2]] = CRGB::Purple;

  leds[indices[5]].fadeLightBy(MAX_BRIGHTNESS * 0.5);
  leds[indices[4]].fadeLightBy(MAX_BRIGHTNESS * 0.5);
  leds[indices[3]].fadeLightBy(MAX_BRIGHTNESS * 0.5);
  leds[indices[1]].fadeLightBy(MAX_BRIGHTNESS * 0.5);
  leds[indices[0]].fadeLightBy(MAX_BRIGHTNESS * 0.5);
  leds[indices[2]].fadeLightBy(MAX_BRIGHTNESS * 0.5);
}

CRGB randomRainbowColor() {
  CRGB rainbow[6];
  rainbow[0] = CRGB::Red;
  rainbow[1] = CRGB::OrangeRed;
  rainbow[2] = CRGB::Yellow;
  rainbow[3] = CRGB::Green;
  rainbow[4] = CRGB::Blue;
  rainbow[5] = CRGB::Purple;
  return rainbow[random(0, 5)];
}

void paintRainbow(unsigned long startMillis, unsigned long timePeriod, float inc) {

  float dist = 0;
  //float inc = 10; // speed. 0.05 is slow. 1 is fast.
  float w = 0.5; // width. threshold of how big to make the light speed dot


  initCircle();

  currentMillis = millis(); // get the current time
  while (currentMillis - startMillis <= timePeriod) {
    currentMillis = millis(); // get the current time

    float py = mapf(dist, 0, distToTravel, sy, dy);
    float px = mapf(dist, 0, distToTravel, sx, dx);

    for (int y = 0; y < NUM_ROWS; y++) {
      for (int c = 0; c < NUM_LEDS_MAX; c++) {
        int x = ctox(y, c);
        if (x < 0 || x >= size(y)) {
          continue;
        }
        int i = getIndex(y, x);

        float d = distance(c, y, px, py);

        //leds[i] = CRGB::Black;
        if (d < w) {
          //prominence[i] = w - d;
          //uint8_t colorIndex = mapf(prominence[i], 0, w, 0, NUM_COLORS);
          //leds[i] = getColor(color1, color2, NUM_COLORS, colorIndex);
          drawThing(y, c);
        }
        //leds[i].fadeLightBy(mapf(prominence[i], 0, w, MAX_BRIGHTNESS, 0));
      }
    }
    FastLED.show();

    dist += inc;

    if (dist >= distToTravel) {
      sdeg = ddeg;
      ddeg = random(0, 360);

      sx = dx;
      sy = dy;
      dx = pointAlongCircumferenceX(RADIUS, ORIGIN_X, ddeg);
      dy = pointAlongCircumferenceY(RADIUS, ORIGIN_Y, ddeg);
      distToTravel = distance(sx, sy, dx, dy);

      dist = 0;
    }
  }
}
