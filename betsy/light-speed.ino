#include <FastLED.h>

#define NUM_STARS 10

int MAX_RADIUS = 30;

float deg[NUM_STARS];
float starRadii[NUM_STARS];
float rx[NUM_STARS];
float ry[NUM_STARS];

void initLightSpeed() {
  for (int s = 0; s < NUM_STARS; s++) {
    deg[s] = random(0, 360);
    deg[0] = 320;
    rx[s] = pointAlongCircumferenceX(0, ORIGIN_X, deg[s]);
    ry[s] = pointAlongCircumferenceX(0, ORIGIN_Y, deg[s]);
    starRadii[s] = random(0, MAX_RADIUS);//0;
  }
  FastLED.show();
}

void lightSpeed(unsigned long startMillis, unsigned long timePeriod) {
  currentMillis = millis(); // get the current time

  //int ORIGIN_X = 15;
  //int ORIGIN_Y = 13;
  int cx = 14;
  int cy = 12;
  float radius = 0;
  float speed;
  float d;
  float w = 0.5; // width. threshold of how big to make the light speed dot
  float prominence;
  float brightness;
  uint8_t colorIndex;
  float MAX_SPEED = 5;//0.6;
  float MIN_SPEED = 0.05;//0.1;
  //int top = -1, left, bottom, right;
  int tops[NUM_STARS];
  int bottoms[NUM_STARS];
  int lefts[NUM_STARS];
  int rights[NUM_STARS];
  for (int i = 0; i < NUM_STARS; i++) {
    tops[i] = -1;
  }

  Serial.println("start");
  Serial.println(currentMillis);
  Serial.println(startMillis);
  Serial.println(timePeriod);

  while (currentMillis - startMillis <= timePeriod) {
    currentMillis = millis(); // get the current time

    for (int s = 0; s < 4; s++) {

      if (tops[s] != -1) {
        leds[getIndex(tops[s], ctox(tops[s], lefts[s]))] = CRGB::Black;
        leds[getIndex(tops[s], ctox(tops[s], rights[s]))] = CRGB::Black;
        leds[getIndex(bottoms[s], ctox(bottoms[s], lefts[s]))] = CRGB::Black;
        leds[getIndex(bottoms[s], ctox(bottoms[s], rights[s]))] = CRGB::Black;
      }

      // find the pixels closest to its current radius
      lefts[s] = floor(rx[s]);
      rights[s] = ceil(rx[s]);
      tops[s] = floor(ry[s]);
      bottoms[s] = ceil(ry[s]);

      if (inBounds(tops[s], ctox(tops[s], lefts[s]))) {
        setColorAndBrightness(ry[s], ctox(ry[s], rx[s]), tops[s], ctox(tops[s], lefts[s]), w, true);
        //setColorAndBrightness(ry[s], rx[s], top, left, w, true);
      }
      if (inBounds(tops[s], ctox(tops[s], rights[s]))) {
        setColorAndBrightness(ry[s], ctox(ry[s], rx[s]), tops[s], ctox(tops[s], rights[s]), w, false);
        //setColorAndBrightness(ry[s], rx[s], top, right, w, false);
      }
      if (inBounds(bottoms[s], ctox(bottoms[s], lefts[s]))) {
        setColorAndBrightness(ry[s], ctox(ry[s], rx[s]), bottoms[s], ctox(bottoms[s], lefts[s]), w, false);
        //setColorAndBrightness(ry[s], rx[s], bottom, left, w, false);
      }
      if (inBounds(bottoms[s], ctox(bottoms[s], rights[s]))) {
        setColorAndBrightness(ry[s], ctox(ry[s], rx[s]), bottoms[s], ctox(bottoms[s], rights[s]), w, false);
        //setColorAndBrightness(ry[s], rx[s], bottom, right, w, false);
      }

      // increase the increment value so it speeds up as it closer to the edge
      speed = mapf(starRadii[s], 0, MAX_RADIUS, MIN_SPEED, MAX_SPEED);

      starRadii[s] += 1;//speed;
      if (starRadii[s] > MAX_RADIUS) {
        starRadii[s] = 0;
      }

      rx[s] = pointAlongCircumferenceX(starRadii[s], ORIGIN_X, deg[s]);
      ry[s] = pointAlongCircumferenceY(starRadii[s], ORIGIN_Y, deg[s]);
    }
      FastLED.show();
  }
}

void setColorAndBrightness(float ry, float rx, float y, float x, float w, bool printlog) {
  float d = distance(x, y, rx, ry);
  if (printlog) {
    Serial.println(x);
    Serial.println(y);
    Serial.println(rx);
    Serial.println(ry);
    Serial.println(d);
  }
  if (d < w) {
    float prominence = ((float)abs((w*100) - (d*100))) / 100;
    if (printlog) {
      //Serial.println(prominence);
    }
    uint8_t colorIndex = mapf(prominence, 0, w, 0, NUM_COLORS);
    leds[getIndex(y, x)] = getColor(CRGB::Blue, CRGB::White, NUM_COLORS, colorIndex);
    leds[getIndex(y, x)].fadeLightBy(mapf(prominence, 0, w, MAX_BRIGHTNESS, 0));
  }
  if (printlog) {
    Serial.println();
  }
}

void lightSpeedBad(unsigned long startMillis, unsigned long timePeriod) {
  currentMillis = millis(); // get the current time

  //int ORIGIN_X = 15;
  //int ORIGIN_Y = 13;
  int cx = 14;
  int cy = 12;
  float radius = 0;
  float speed;
  float d;
  float w = 0.5; // width. threshold of how big to make the light speed dot
  float prominence;
  float brightness;
  uint8_t colorIndex;
  float MAX_SPEED = 5;//0.6;
  float MIN_SPEED = 0.05;//0.1;

  while (currentMillis - startMillis <= timePeriod) {
    currentMillis = millis(); // get the current time

    for (int s = 0; s < 10; s++) {
      // increase the increment value so it speeds up as it closer to the edge
      speed = mapf(starRadii[s], 0, MAX_RADIUS, MIN_SPEED, MAX_SPEED);

      starRadii[s] += speed;
      if (starRadii[s] > MAX_RADIUS) {
        starRadii[s] = 0;
      }

      rx[s] = pointAlongCircumferenceX(starRadii[s], ORIGIN_X, deg[s]);
      ry[s] = pointAlongCircumferenceY(starRadii[s], ORIGIN_Y, deg[s]);
    }

    for (int y = 0; y < NUM_ROWS; y++) {
      for (int c = 0; c < NUM_LEDS_MAX; c++) {
        int x = ctox(y, c);
        if (x < 0 || x > size(y)) {
          continue;
        }
        int i = getIndex(y, x);

        leds[i] = CRGB::Black;

        for (int s = 0; s < 10; s++) {
          d = distance(c, y, rx[s], ry[s]);
          if (d < w) {
            prominence = w - d;
            colorIndex = mapf(prominence, 0, w, 0, NUM_COLORS);
            leds[i] = getColor(CRGB::Blue, CRGB::White, NUM_COLORS, colorIndex);
            brightness = mapf(prominence, 0, w, MAX_BRIGHTNESS, 0);
            leds[i].fadeLightBy(brightness);
          }
        }
      }
    }
    FastLED.show();
  }
}
