#include <FastLED.h>

void spiral(int totalCount, int offsetInc, bool fromCenter) {

  int offset = 0;
  int offsetBegin = offset;
  bool toggle = true;
  int numRays = 8;
  int degs[numRays];
  int inc = 360 / numRays;
  for (int i = 0; i < numRays; i++) {
    degs[i] = i * inc;
  }

  allBlack();

  int count = 0;
  while (count < totalCount) { // * 2 for toggle
    count++;

    if (fromCenter) {
      for(float radius = 0; radius < RADIUS; radius += 0.25) {
        for (int d = 0; d < numRays; d++) {

          float px = pointAlongCircumferenceX(radius, ORIGIN_X, degs[d] + offset);
          float py = pointAlongCircumferenceY(radius, ORIGIN_Y, degs[d] + offset);

          int x = ((degs[d] > 0 && degs[d] < 90) || (degs[d] > 180 && degs[d] < 270))
            ? ceil(px)
            : floor(px);
          int y = floor(py);
          int i = getIndex(y, ctox(y, x));

          if (toggle) {
            //leds[i] = d % 2 == 0 ? CRGB::Blue : CRGB::White;
            leds[i] = getColor(CRGB::Blue, CRGB::White, 4, d % 4);
            float dist = distance(px, py, x, y);
            //leds[i].fadeLightBy(mapf(dist, 0, 1, MAX_BRIGHTNESS, 0));
          } else {
            leds[i] = CRGB::Black;
          }
        }

        offset += offsetInc;

        FastLED.show();
      }
    } else {
      for(float radius = RADIUS; radius >= 0; radius-=0.25) {
        for (int d = 0; d < numRays; d++) {

          float px = pointAlongCircumferenceX(radius, ORIGIN_X, degs[d] + offset);
          float py = pointAlongCircumferenceY(radius, ORIGIN_Y, degs[d] + offset);

          int x = ((degs[d] > 0 && degs[d] < 90) || (degs[d] > 180 && degs[d] < 270))
            ? ceil(px)
            : floor(px);
          int y = floor(py);
          int i = getIndex(y, ctox(y, x));

          if (toggle) {
            //leds[i] = d % 2 == 0 ? CRGB::Blue : CRGB::White;
            leds[i] = getColor(CRGB::Blue, CRGB::White, 4, d % 4);
            float dist = distance(px, py, x, y);
            //leds[i].fadeLightBy(mapf(dist, 0, 1, MAX_BRIGHTNESS, 0));
          } else {
            leds[i] = CRGB::Black;
          }
        }

        offset += offsetInc;

        FastLED.show();
      }
    }

    toggle = !toggle;
    offset = offsetBegin;
    if (toggle) {
      offsetBegin = offset;
    }
  }
}

int wrap(int offset) {
  return offset < RADIUS ? offset : (offset - RADIUS);
}


// this version shoots bolts out of the center one at a time in a circle
void boltsFromCenter(unsigned long startMillis, unsigned long timePeriod) {

  currentMillis = millis(); // get the current time

  int numRays = 4;
  int degs[numRays];
  int inc = 360 / numRays;
  for (int i = 0; i < numRays; i++) {
    degs[i] = i * inc;
  }

  while (currentMillis - startMillis <= timePeriod) {
    currentMillis = millis(); // get the current time

    allBlack();

    for (int d = 0; d < numRays; d++) {
      for(int radius = 0; radius < RADIUS; radius++) {

        float px = pointAlongCircumferenceX(radius, ORIGIN_X, degs[d]);
        float py = pointAlongCircumferenceY(radius, ORIGIN_Y, degs[d]);

        int x = floor(px);
        int y = floor(py);

        leds[getIndex(y, ctox(y, x))] = CRGB::White;

        FastLED.show();
      }
      //for(int radius = RADIUS; radius >= 0; radius--) {
      for(int radius = 0; radius < RADIUS; radius++) {

        float px = pointAlongCircumferenceX(radius, ORIGIN_X, degs[d]);
        float py = pointAlongCircumferenceY(radius, ORIGIN_Y, degs[d]);

        int x = floor(px);
        int y = floor(py);

        leds[getIndex(y, ctox(y, x))] = CRGB::Black;

        FastLED.show();
      }
    }
  }
}
