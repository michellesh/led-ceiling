#include <FastLED.h>

void ripples(int count, bool concentric, int w, int w2, float r1, float minRadius, float offset) {
  float maxRadius = 26.0;
  //float maxRadius = 36.0; // this is a hack to make it not freeze at max radius
  //float minRadius = -4.0;

  CRGB color1 = CRGB(0, 0, 255);
  CRGB color2 = CRGB(0, 0, 255);
  //float radius = 0;
  //float radius2 = minRadius - 4.0;
  float radius = r1;
  float radius2 = minRadius - offset;
  int cy = concentric ? NUM_ROWS / 2 : 21;
  int cx = concentric ? NUM_LEDS_MAX / 2 : 21;
  int cy2 = concentric ? NUM_ROWS / 2 : 7;
  int cx2 = concentric ? NUM_LEDS_MAX / 2 : 7;
  int rippleWidth = w == -1 ? random(2, 10) : w;
  int rippleWidth2 = w2 == -1 ? random(2, 10) : w2;
  bool done1 = false;
  bool done2 = false;

  int numRipples = 0;
  while (!done1 || !done2) {
    donuts(cy, cx, cy2, cx2, rippleWidth, rippleWidth2, radius, radius2, color1, color2, done1, done2, maxRadius);
    radius += 0.2;
    radius2 += 0.2;
    if (!done1 && radius > maxRadius) {
      rippleWidth = w == -1 ? random(2, 10) : w;
      color1 = CHSV(random8(), 255, 255);
      if (concentric) {
        cy = NUM_ROWS / 2;
        cx = NUM_LEDS_MAX / 2;
      } else {
        cy = random(0, NUM_ROWS);
        cx = random(0, NUM_LEDS_MAX);
      }
      radius = minRadius;//r1 == -1 ? minRadius : r1;
      numRipples++;
      if (numRipples > count) {
        done1 = true;
      }
    }
    if (!done2 && radius2 > maxRadius) {
      rippleWidth2 = w2 == -1 ? random(2, 10) : w2;
      color2 = CHSV(random8(), 255, 255);
      if (concentric) {
        cy2 = NUM_ROWS / 2;
        cx2 = NUM_LEDS_MAX / 2;
      } else {
        cy2 = random(0, NUM_ROWS);
        cx2 = random(0, NUM_LEDS_MAX);
      }
      radius2 = minRadius;
      numRipples++;
      if (numRipples > count) {
        done2 = true;
      }
    }
  }
  // end sequence
}

void donuts(int cy, int cx, int cy2, int cx2, float w, float w2, float radius, float radius2, CRGB color1, CRGB color2, bool done1, bool done2, float maxRadius) {
  uint8_t colorIndex;
  float brightness;
  float prominence;
  float d;
  float d2;
  float percentDone1 = radius / maxRadius;
  float percentDone2 = radius2 / maxRadius;
  for (int y = 0; y < NUM_ROWS; y++) {
    for (int c = 0; c < NUM_LEDS_MAX; c++) {
      int x = ctox(y, c);
      if (x < 0 || x > size(y)) {
        continue;
      }
      int i = getIndex(y, x);

      d = distance(cx, cy, c, y);
      d2 = distance(cx2, cy2, c, y);

      if (!done1 && d < (radius + (w / 2)) && d > (radius - (w / 2))) {
        prominence = abs(radius - d);
        colorIndex = mapf(prominence, 0, (w / 2), 0, NUM_COLORS);
        brightness = mapf(prominence, 0, (w / 2), 0, MAX_BRIGHTNESS);
        leds[i] = getColor(CRGB::White, color1, NUM_COLORS, colorIndex);
        leds[i].fadeLightBy(max(MAX_BRIGHTNESS * percentDone1, brightness));
      } else if (!done2 && d2 < (radius2 + (w2 / 2)) && d2 > (radius2 - (w2 / 2))) {
        prominence = abs(radius2 - d2);
        colorIndex = mapf(prominence, 0, (w2 / 2), 0, NUM_COLORS);
        brightness = mapf(prominence, 0, (w2 / 2), 0, MAX_BRIGHTNESS);
        leds[i] = getColor(CRGB::White, color2, NUM_COLORS, colorIndex);
        leds[i].fadeLightBy(max(MAX_BRIGHTNESS * percentDone2, brightness));
      } else {
        leds[i] = CRGB::Black;
      }
    }
  }
  FastLED.show();
}
