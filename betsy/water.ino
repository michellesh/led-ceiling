#include <FastLED.h>

double MAX_POSITION = 100;//SPACING;//INT8_MAX;
double MIN_POSITION = -100;//-SPACING;//INT8_MIN;

double velocity[650];
double position[650];

void initWater() {
  for (int i = 0; i < 650; i++) {
    position[i] = (int8_t)random(MIN_POSITION, MAX_POSITION);
    velocity[i] = 0;
    leds[i] = CRGB::Black;
  }
  // fade each pixel from black to designated color
  float fadeIn = 0;
  float maxFade = 100;
  while (fadeIn < maxFade) {
    for (int i = 0; i < 650; i++) {
      leds[i] = getColor(CRGB(0, 0, 0), positionToColor(position[i]), maxFade, fadeIn);
      leds[i].fadeLightBy(mapi(abs(position[i]), 0, MAX_POSITION, MAX_BRIGHTNESS, 0));
    }
    fadeIn += 0.5;
    FastLED.show();
  }
}

void water(unsigned long startMillis, unsigned long timePeriod) {

  double TENSION = 55;//70; // the tension in the strings
  double SPACING = 10; // the distance between masses on the string
  //double MASS = 0.005; // the mass of each pixel
  double MASS = 0.005; // the mass of each pixel
  double GAMMA = 0.0185; // the damping constant (without this the waves will reflect off the free end and continue forever)
  double TSTEP = 0.0015;

  double positionTerm;
  double damping;
  double force;

  initWater();

  currentMillis = millis(); // get the current time

  while (currentMillis - startMillis <= timePeriod) {
    currentMillis = millis(); // get the current time
    for (int i = 0; i < 650; i++) {
      int y = itoy(i);
      int x = itox(i);

      positionTerm = 0;

      // above
      if (x >= 0 && x < size(y-1)) {
        positionTerm += position[i] - position[getIndex(y-1, x)];
      }
      // below
      if (x >= 0 && x < size(y+1)) {
        positionTerm += position[i] - position[getIndex(y+1, x)];
      }
      // left
      if ((x-1) >= 0 && (x-1) < size(y)) {
        positionTerm += position[i] - position[getIndex(y, x-1)];
      }
      // right
      if ((x+1) >= 0 && (x+1) < size(y)) {
        positionTerm += position[i] - position[getIndex(y, x+1)];
      }

      damping = GAMMA * velocity[i];
      force = -(TENSION/SPACING) * positionTerm - damping;

      position[i] = position[i] > MAX_POSITION ? MAX_POSITION : position[i];
      position[i] = position[i] < MIN_POSITION ? MIN_POSITION : position[i];

      position[i] = position[i] + (velocity[i] * TSTEP) + 0.5 * (force / MASS) * TSTEP * TSTEP;
      velocity[i] = velocity[i] + (force / MASS) * TSTEP;

      // get the color!
      leds[i] = positionToColor(position[i]);
      // TODO is it ok to reverse brightness?
      leds[i].fadeLightBy(mapi(abs(position[i]), 0, MAX_POSITION, MAX_BRIGHTNESS, 25));
      //if (x == 0 && y == 23) {
      //  Serial.println(mapi(abs(position[i]), 0, MAX_POSITION, MAX_BRIGHTNESS, 0));
      //}
    }
    FastLED.show();
    //delay(5);
  }
}

CRGB positionToColor(int16_t position) {
  int16_t colorIndex = mapi(position, MIN_POSITION, MAX_POSITION, 0, NUM_COLORS);
  return getColor(CRGB(255, 255, 255), CRGB(0, 0, 255), NUM_COLORS, colorIndex);
}

int16_t mapi(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double ptof(int16_t p) { return (double)p / 10000.0; }

int16_t ftop(double p) { return (int16_t)(p * 10000.0); }

