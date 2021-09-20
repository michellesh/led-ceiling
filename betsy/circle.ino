#include <FastLED.h>

#define RADIUS 15

float sx;
float sy;
float dx;
float dy;
float sdeg = 0;
float ddeg = 45;
float distToTravel;
float dist = 0;

void initCircle() {
  sx = pointAlongCircumferenceX(RADIUS, ORIGIN_X, sdeg);
  sy = pointAlongCircumferenceY(RADIUS, ORIGIN_Y, sdeg);
  dx = pointAlongCircumferenceX(RADIUS, ORIGIN_X, ddeg);
  dy = pointAlongCircumferenceY(RADIUS, ORIGIN_Y, ddeg);
  distToTravel = distance(sx, sy, dx, dy);
}

void circle(unsigned long startMillis, unsigned long timePeriod) {

  //float dist = 0;
  float inc = 0.1; // speed. 0.05 is slow. 1 is fast.
  float w = 3; // width. threshold of how big to make the light speed dot

  CRGB scolor1 = CRGB::Blue;
  CRGB scolor2 = CRGB::White;
  CRGB dcolor1 = CRGB::Green;
  CRGB dcolor2 = CRGB::White;

  //initCircle();

  currentMillis = millis(); // get the current time
  while (currentMillis - startMillis <= timePeriod) {
    currentMillis = millis(); // get the current time

    float py = mapf(dist, 0, distToTravel, sy, dy);
    float px = mapf(dist, 0, distToTravel, sx, dx);

    CRGB color1 = getColor(scolor1, dcolor1, NUM_COLORS, mapf(dist, 0, distToTravel, 0, NUM_COLORS));
    CRGB color2 = getColor(scolor2, dcolor2, NUM_COLORS, mapf(dist, 0, distToTravel, 0, NUM_COLORS));

    for (int y = 0; y < NUM_ROWS; y++) {
      for (int c = 0; c < NUM_LEDS_MAX; c++) {
        int x = ctox(y, c);
        if (x < 0 || x >= size(y)) {
          continue;
        }
        int i = getIndex(y, x);

        float d = distance(c, y, px, py);

        if (d < w) {
          float prominence = w - d;
          uint8_t colorIndex = mapf(prominence, 0, w, 0, NUM_COLORS);
          leds[i] = getColor(color1, color2, NUM_COLORS, colorIndex);
          float brightness = mapf(prominence, 0, w, MAX_BRIGHTNESS, 0);
          leds[i].fadeLightBy(brightness);
        } else {
          leds[i] = CRGB::Black;
        }
      }
    }
    FastLED.show();

    dist += inc;

    if (dist >= distToTravel) {
      float op = distance(sx, sy, sx, ORIGIN_Y);
      float hyp = distance(sx, sy, ORIGIN_X, ORIGIN_Y);
      float theta = degrees(asin(op / hyp));

      float old_ddeg = ddeg;
      ddeg = (int)(sdeg + (2 * theta)) % 360;
      sdeg = old_ddeg;

      sx = dx;
      sy = dy;
      dx = pointAlongCircumferenceX(RADIUS, ORIGIN_X, ddeg);
      dy = pointAlongCircumferenceY(RADIUS, ORIGIN_Y, ddeg);
      distToTravel = distance(sx, sy, dx, dy);

      dist = 0;

      scolor1 = dcolor1;
      scolor2 = dcolor2;
      dcolor1 = CHSV(random8(), 255, 255);
      dcolor2 = CHSV(random8(), 255, 255);
    }
  }
}

float prominence[650];

void initPaint() {
  for (int i = 0; i < 650; i++) {
    prominence[i] = 0;
  }
}

// color1 is the color of the slime trail
// color2 is the brighter center of the blob
// inc is the speed?
void paintColor(unsigned long startMillis, unsigned long timePeriod, CRGB color1, CRGB color2, float inc) {

  //float dist = 0;
  //float inc = 10; // speed. 0.05 is slow. 1 is fast.
  float w = 2; // width. threshold of how big to make the light speed dot


  //initCircle();

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

        if (d < w) {
          prominence[i] = w - d;
          uint8_t colorIndex = mapf(prominence[i], 0, w, 0, NUM_COLORS);
          leds[i] = getColor(color1, color2, NUM_COLORS, colorIndex);
        }
        leds[i].fadeLightBy(mapf(prominence[i], 0, w, MAX_BRIGHTNESS * 0.6, 0));
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

// paintBlend is mostly the same as paintColor except
// the slime trail it leaves behind is a different color
// as the blob
void paintBlend(unsigned long startMillis, unsigned long timePeriod, CRGB color1, CRGB color2, CRGB slimeColor1, CRGB slimeColor2, float inc) {

  //float dist = 0;
  //float inc = 10; // speed. 0.05 is slow. 1 is fast.
  float w = 2; // width. threshold of how big to make the light speed dot

  bool allDone = false;
  bool visited[650];
  for (int i = 0; i < 650; i++) {
    visited[i] = false;
  }

  //initCircle();

  currentMillis = millis(); // get the current time
  //while (currentMillis - startMillis <= timePeriod || !allDone) {
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

        if (d < w) {
          prominence[i] = w - d;
          uint8_t colorIndex = mapf(prominence[i], 0, w, 0, NUM_COLORS);
          leds[i] = getColor(color1, color2, NUM_COLORS, colorIndex);
          visited[i] = true;
        } else if (visited[i] && prominence[i] > 0) {
          uint8_t colorIndex = mapf(prominence[i], 0, w, 0, NUM_COLORS);
          leds[i] = getColor(slimeColor1, slimeColor2, NUM_COLORS, colorIndex);
        }
        leds[i].fadeLightBy(mapf(prominence[i], 0, w, MAX_BRIGHTNESS, 0));
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
    allDone = all(visited);
  }
}

// color1 and color2 are the colors of the ball that moves around
void paintErase(unsigned long startMillis, unsigned long timePeriod, CRGB color1, CRGB color2, float inc) {

  //float dist = 0;
  //float inc = 0.1; // speed. 0.05 is slow. 1 is fast.
  float w = 2; // width. threshold of how big to make the light speed dot

  bool allErased = false;
  bool erased[650];
  bool visited[650];
  for (int i = 0; i < 650; i++) {
    erased[i] = false;
    visited[i] = false;
  }

  //initCircle();

  currentMillis = millis(); // get the current time
  while (currentMillis - startMillis <= timePeriod || !allErased) {
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

        if (erased[i]) {
          leds[i] = CRGB::Black;
        }

        if (d < w) {
          float prominence = w - d;
          uint8_t colorIndex = mapf(prominence, 0, w, 0, NUM_COLORS);
          leds[i] = getColor(color1, color2, NUM_COLORS, colorIndex);
          float brightness = mapf(prominence, 0, w, MAX_BRIGHTNESS, 0);
          leds[i].fadeLightBy(brightness);
          visited[i] = true;
        } else if (visited[i]) {
          erased[i] = true;
        }
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

    allErased = all(erased);
  }
}
