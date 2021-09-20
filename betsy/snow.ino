#include <FastLED.h>

double speeds[NUM_LEDS_MAX]; // the pixel in each column has its own speed
double positions[NUM_LEDS_MAX]; // this keeps track of how far it is
CRGB color1[NUM_LEDS_MAX];
CRGB color2[NUM_LEDS_MAX];
double widths[NUM_LEDS_MAX];

int MIN_WIDTH = 1;
int MAX_WIDTH = 2;
double MIN_SPEED = 10;
double MAX_SPEED = 20;

void initSnow() {
  MAX_WIDTH = 2;
  for (int i = 0; i < NUM_LEDS_MAX; i++) {
    positions[i] = (double)random(0, NUM_ROWS);
    color1[i] = CHSV(random8(), 255, 255);
    color2[i] = CHSV(random8(), 255, 255);
    speeds[i] = (double)random(MIN_SPEED * 100, MAX_SPEED * 100) / 10000;
    widths[i] = (double)random(MIN_WIDTH * 100, MAX_WIDTH * 100) / 100;
  }
}

void snow(unsigned long startMillis, unsigned long timePeriod) {

  unsigned long timeBlock = minutes(2);
  unsigned long blockMillis = 0;

  initSnow();

  currentMillis = millis(); // get the current time

  while (currentMillis - startMillis <= timePeriod) {
    currentMillis = millis(); // get the current time

    if (currentMillis - blockMillis >= timeBlock) {
      blockMillis = millis();
      MAX_WIDTH++;
    }

    drawSnowflakes(true);

  }
  bool done = false;
  while(!done) {
    done = drawSnowflakes(false);
  }
}

bool drawSnowflakes(bool overAndOver) {
  uint8_t colorIndex;
  uint8_t brightness;
  bool done[NUM_LEDS_MAX];
  for(int d = 0; d < NUM_LEDS_MAX; d++) {
    done[d] = false;
  }

  double d;
  double prominence;
  //double rippleWidth = 3;

  CRGB color;
  for (int cx = 0; cx < NUM_LEDS_MAX; cx++) {
    for (int y = 0; y < NUM_ROWS; y++) {
      int x = ctox(y, cx);
      if (x <= 0 || x > size(y)) {
        continue;
      }
      int i = getIndex(y, x);

      d = distance(y, x, 0, x);
      if (d < (positions[cx] + widths[cx]) && d > (positions[cx] - widths[cx])) {
        prominence = abs(positions[cx] - d); // how close is it to the current position
        colorIndex = mapf(prominence, 0, widths[cx], 0, NUM_COLORS);
        color = getColor(color1[cx], color2[cx], NUM_COLORS, colorIndex);
        brightness = mapf(prominence, 0, widths[cx], 0, MAX_BRIGHTNESS);
        leds[i] = color;
        leds[i].fadeLightBy(brightness);
      } else {
        leds[i] = CRGB::Black;
        //leds[i] = color2;
        //leds[i].fadeLightBy(MAX_BRIGHTNESS * 0.95);
      }
    }
    positions[cx] += speeds[cx];
    if (positions[cx] >= (NUM_ROWS + 10)) {
      if (overAndOver) {
        positions[cx] = -10;
        color1[cx] = color2[cx];
        color2[cx] = CHSV(random8(), 255, 255);
        widths[cx] = (double)random(MIN_WIDTH * 100, MAX_WIDTH * 100) / 100;
      } else {
        done[cx] = true;
      }
    }
  }
  FastLED.show();
  return all(done);
}

void oneFallingSnowflake() {
  double width = 2;
  double position = 0;
  while(position < NUM_ROWS / 2) {
    for (int y = 0; y <= NUM_ROWS / 2; y++) {
      int x = ctox(y, NUM_LEDS_MAX / 2);
      double d = distance(y, x, 0, x);
      if (d < (position + width) && d > (position - width)) {
        double prominence = abs(position - d); // how close is it to the current position
        uint8_t brightness = mapf(prominence, 0, width, 0, MAX_BRIGHTNESS);
        leds[getIndex(y, x)] = CRGB::White;
        leds[getIndex(y, x)].fadeLightBy(brightness);
      } else {
        leds[getIndex(y, x)] = CRGB::Black;
      }
    }
    FastLED.show();
    position += 0.05;
  }
  leds[getIndex(NUM_ROWS/2, NUM_LEDS_MAX/2)] = CRGB::White;
  FastLED.show();
}
