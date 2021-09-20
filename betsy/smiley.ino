#include <FastLED.h>

void smiley() {
  float radius = 7;
  float w = 1;

  for (int y = 0; y < NUM_ROWS; y++) {
    for (int c = 0; c < NUM_LEDS_MAX; c++) {
      int x = ctox(y, c);
      if (x < 0 || x > size(y)) {
        continue;
      }
      int i = getIndex(y, x);
      float d = distance(c, y, ORIGIN_X, ORIGIN_Y);

      // outline
      if (d < (radius + (w / 2)) && d > (radius - (w / 2))) {
        leds[i] = CRGB::Yellow;

      // smile
      } else if (d < ((radius/2) + (w / 2)) && d > ((radius/2) - (w / 2)) && y >= NUM_ROWS / 2) {
        leds[i] = CRGB::Yellow;

      } else {
        leds[i] = CRGB::Black;
      }
    }
  }

  // eyes
  leds[getIndex(ORIGIN_Y - 3, ctox(ORIGIN_Y - 3, ORIGIN_X - 3))] = CRGB::Yellow;
  leds[getIndex(ORIGIN_Y - 3, ctox(ORIGIN_Y - 3, ORIGIN_X + 3))] = CRGB::Yellow;

  FastLED.show();
}
