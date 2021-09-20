#include <FastLED.h>

#define NUM_ROWS 27
#define NUM_LEDS_MAX 31
#define ORIGIN_X 15
#define ORIGIN_Y 13

CRGB leds[650];
unsigned long startMillis;
unsigned long currentMillis;

void setup() {
  randomSeed(analogRead(0));
  FastLED.addLeds<NEOPIXEL, 26>(leds, 0, 18);   // 0/17
  FastLED.addLeds<NEOPIXEL, 27>(leds, 17, 17);  // 1/17
  FastLED.addLeds<NEOPIXEL, 28>(leds, 34, 19);  // 2/19
  FastLED.addLeds<NEOPIXEL, 29>(leds, 53, 21);  // 3/21
  FastLED.addLeds<NEOPIXEL, 30>(leds, 74, 21);  // 4/21
  FastLED.addLeds<NEOPIXEL, 31>(leds, 95, 23);  // 5/23
  FastLED.addLeds<NEOPIXEL, 32>(leds, 118, 23); // 6/23
  FastLED.addLeds<NEOPIXEL, 33>(leds, 141, 25); // 7/25
  FastLED.addLeds<NEOPIXEL, 34>(leds, 166, 25); // 8/25
  FastLED.addLeds<NEOPIXEL, 35>(leds, 191, 27); // 9/27
  FastLED.addLeds<NEOPIXEL, 36>(leds, 218, 29); // 10/29
  FastLED.addLeds<NEOPIXEL, 37>(leds, 247, 29); // 11/29
  FastLED.addLeds<NEOPIXEL, 38>(leds, 276, 31); // 12/31
  FastLED.addLeds<NEOPIXEL, 39>(leds, 307, 31); // 13/31
  FastLED.addLeds<NEOPIXEL, 40>(leds, 338, 31); // 14/31
  FastLED.addLeds<NEOPIXEL, 41>(leds, 369, 29); // 15/29
  FastLED.addLeds<NEOPIXEL, 42>(leds, 398, 29); // 16/29
  FastLED.addLeds<NEOPIXEL, 43>(leds, 427, 27); // 17/27
  FastLED.addLeds<NEOPIXEL, 44>(leds, 454, 25); // 18/25
  FastLED.addLeds<NEOPIXEL, 45>(leds, 479, 25); // 19/25
  FastLED.addLeds<NEOPIXEL, 46>(leds, 504, 23); // 20/23
  FastLED.addLeds<NEOPIXEL, 47>(leds, 527, 23); // 21/23
  FastLED.addLeds<NEOPIXEL, 48>(leds, 550, 21); // 22/21
  FastLED.addLeds<NEOPIXEL, 49>(leds, 571, 21); // 23/21
  FastLED.addLeds<NEOPIXEL, 50>(leds, 592, 19); // 24/19
  FastLED.addLeds<NEOPIXEL, 51>(leds, 611, 17); // 25/17
  FastLED.addLeds<NEOPIXEL, 52>(leds, 628, 17); // 26/17
  Serial.begin(9600); // open the serial port at 9600 bps:
  startMillis = millis();
}

uint8_t NUM_COLORS = 100; // the number of shades of blue
uint8_t MAX_BRIGHTNESS = 255;

void loopTemp() {

  //spiral(2, 0, false); // base case
  //spiral(2, 1, false); // base case
  //spiral(2, 2, false); // base case
  //spiral(2, 3, false); // base case
  //spiral(2, 4, false); // base case
  //spiral(2, 5, false); // base case

  //spiral(2, 0, true); // base case
  //spiral(2, 1, true); // base case
  //spiral(2, 2, true); // base case
  //spiral(2, 3, true); // base case
  //spiral(2, 4, true); // base case
  //spiral(2, 5, true); // base case
  //delay(2000);

  //ripples(2, true, 3, 3, 0, -4, 4); // base case
  //ripples(2, true, 10, 10, -10, -10, 10);
  //ripples(2, true, 15, 15, -15, -15, 15);
  //ripples(4, true, 25, 25, -25, -25, 25); // continuous

  //water(millis(), minutes(5));

  //allBlack();

  //thingScrollLeftRight();

  //circle(millis(), minutes(5));

  initPaint();
  // paint over the grid blue
  paintColor(millis(), minutes(1), CRGB::Blue, CRGB::DodgerBlue, 0.3);
  // paint over the blue with yellow to make green
  delay(3000);
  paintBlend(millis(), minutes(1), CRGB::Gold, CRGB::Yellow, CRGB::DarkGreen, CRGB::ForestGreen, 0.3);
  // erase the grid with a green blob
  delay(3000);
  paintErase(millis(), minutes(1), CRGB::DarkGreen, CRGB::ForestGreen, 1);

  thingScrollTopBottom();

  // paint over the grid red/orange
  //paintColor(millis(), minutes(1), CRGB::DarkRed, CRGB::Gold, 0.1);
  // FAST erase with a red/orange blob
  //paintErase(millis(), minutes(1), CRGB::DarkRed, CRGB::Gold, 10);

  //CRGB color1 = CHSV(random16(), 255, 255);
  //CRGB color2 = CHSV(random16(), 255, 255);
  //paintColor(millis(), minutes(1), color1, color2, 10); // super fast coloring!
  //paintColor(millis(), minutes(1), CRGB::Black, CRGB::Black, 10); // super fast erasing!

  // set all to black after erasing just in case
  allBlack();

  //paintRainbow(millis(), minutes(1), 1); 

  //initLightSpeed(); // :(
  //lightSpeed(millis(), minutes(10)); // TODO while true

  snow(millis(), minutes(10)); // note that the range increases every minute
  
  thingScrollDiagonal();

  oneFallingSnowflake(); // transitions into ripples
  ripples(2, true, 3, 3, 0, -4, 4); // base case
  ripples(2, true, 10, 10, -10, -10, 10);
  ripples(2, true, 15, 15, -15, -15, 15);
  ripples(4, true, 25, 25, -25, -25, 25); // continuous
  ripples(4, false, -1, -1, 0, -4, 4); // random
  // 2 2 2 4 4 -> 3.5 minutes

  water(millis(), minutes(10));
  
  delay(5000);
}

void loop() {
  //shortLoop();
  hourLoop();
  //lumenLoop();
}

void lumenLoop() {
  // all spirals: 45 seconds
  spiral(2, 0, false); // base case
  spiral(2, 1, false); // base case
  spiral(2, 2, false); // base case
  spiral(2, 3, false); // base case
  spiral(2, 4, false); // base case
  spiral(2, 5, false); // base case
  spiral(2, 6, false); // base case

  spiral(2, 0, true); // base case
  spiral(2, 1, true); // base case
  spiral(2, 2, true); // base case
  spiral(2, 3, true); // base case
  spiral(2, 4, true); // base case
  spiral(2, 5, true); // base case
  spiral(2, 6, true); // base case
  delay(2000);

  // concentric ripples: 3 min 30 sec
  ripples(2, true, 3, 3, 0, -4, 4); // base case
  ripples(2, true, 10, 10, -10, -10, 10);
  ripples(2, true, 15, 15, -15, -15, 15);
  ripples(8, true, 25, 25, -25, -25, 25); // continuous

  // random ripples: 2 min 10 sec
  ripples(20, false, -1, -1, 0, -4, 4); // random. 40 takes 4 minutes
  // 2 2 2 4 4 -> 3.5 minutes

  water(millis(), minutes(4));
    
  delay(5000);
}

void shortLoop() {
  spiral(2, 0, false); // base case
  spiral(2, 1, false); // base case
  spiral(2, 2, false); // base case
  spiral(2, 3, false); // base case
  spiral(2, 4, false); // base case
  spiral(2, 5, false); // base case
  spiral(2, 6, false); // base case

  spiral(2, 0, true); // base case
  spiral(2, 1, true); // base case
  spiral(2, 2, true); // base case
  spiral(2, 3, true); // base case
  spiral(2, 4, true); // base case
  spiral(2, 5, true); // base case
  spiral(2, 6, true); // base case
  delay(2000);

  initPaint();
  initCircle();
  paintColor(millis(), minutes(1), CRGB::Blue, CRGB::DodgerBlue, 0.5);
  paintBlend(millis(), minutes(1), CRGB::Gold, CRGB::Yellow, CRGB::DarkGreen, CRGB::ForestGreen, 0.5);
  paintRainbow(millis(), minutes(1), 0.5);
  //paintErase(millis(), minutes(3), CRGB::DarkGreen, CRGB::ForestGreen, 0.5);
  //paintColor(millis(), minutes(3), CRGB::DarkRed, CRGB::Gold, 0.1);
  //paintErase(millis(), minutes(1), CRGB::DarkRed, CRGB::Gold, 10);
  //paintRainbow(millis(), minutes(1), 0.5);

  allBlack(); // set all to black after erasing just in case

  snow(millis(), minutes(1)); // note that the range increases every minute
  
  oneFallingSnowflake(); // transitions into ripples
  ripples(2, true, 3, 3, 0, -4, 4); // base case
  ripples(2, true, 10, 10, -10, -10, 10);
  ripples(2, true, 15, 15, -15, -15, 15);
  ripples(4, true, 25, 25, -25, -25, 25); // continuous
  ripples(8, false, -1, -1, 0, -4, 4); // random. 40 takes 4 minutes
  // 2 2 2 4 4 -> 3.5 minutes

  water(millis(), minutes(5));

  smiley();
  
  delay(5000);
}

void hourLoop() {

  spiral(2, 0, false); // base case
  spiral(2, 1, false); // base case
  spiral(2, 2, false); // base case
  spiral(2, 3, false); // base case
  spiral(2, 4, false); // base case
  spiral(2, 5, false); // base case
  spiral(2, 6, false); // base case

  spiral(2, 0, true); // base case
  spiral(2, 1, true); // base case
  spiral(2, 2, true); // base case
  spiral(2, 3, true); // base case
  spiral(2, 4, true); // base case
  spiral(2, 5, true); // base case
  spiral(2, 6, true); // base case
  delay(2000);

  ripples(2, true, 3, 3, 0, -4, 4); // base case
  ripples(2, true, 10, 10, -10, -10, 10);
  ripples(2, true, 15, 15, -15, -15, 15);
  ripples(4, true, 25, 25, -25, -25, 25); // continuous

  water(millis(), minutes(5));

  //bigRainbowThing(10, 8); // middle

  //circle(millis(), minutes(5));

  //thingScrollLeftRight();

  initPaint();
  initCircle();

  // 15000 = 15 seconds
  paintColor(millis(), minutes(3), CRGB::Blue, CRGB::DodgerBlue, 0.5);
  //delay(5000);

  paintBlend(millis(), minutes(3), CRGB::Gold, CRGB::Yellow, CRGB::DarkGreen, CRGB::ForestGreen, 0.5);
  //delay(5000);

  paintErase(millis(), minutes(3), CRGB::DarkGreen, CRGB::ForestGreen, 0.5);
  //delay(5000);

  paintColor(millis(), minutes(3), CRGB::DarkRed, CRGB::Gold, 0.1);
  //delay(5000);

  paintErase(millis(), minutes(1), CRGB::DarkRed, CRGB::Gold, 10);
  //delay(5000);

  paintRainbow(millis(), minutes(1), 0.5);
  //delay(5000);

  //CRGB color1 = CHSV(random16(), 255, 255);
  //CRGB color2 = CHSV(random16(), 255, 255);
  //paintColor(millis(), minutes(1), color1, color2, 10); // super fast coloring!
  //paintColor(millis(), minutes(1), CRGB::Black, CRGB::Black, 10); // super fast erasing!

  allBlack(); // set all to black after erasing just in case

  thingScrollTopBottom();

  snow(millis(), minutes(10)); // note that the range increases every minute
  
  oneFallingSnowflake(); // transitions into ripples
  ripples(2, true, 3, 3, 0, -4, 4); // base case
  ripples(50, false, -1, -1, 0, -4, 4); // random. 40 takes 4 minutes
  // 2 2 2 4 4 -> 3.5 minutes

  water(millis(), minutes(10));

  thingScrollDiagonal();

  smiley();
  
  delay(10000);
}

CRGB randomColor() {
  return CHSV(random16(), 255, 255);
}

bool inBounds(int y, int x) {
  return y >= 0 && y < NUM_ROWS && x >= 0 && x < size(y);
}

void allBlack() {
  for (int i = 0; i < 650; i++) {
    leds[i] = CRGB::Black;
  }
}

unsigned long minutes(unsigned long numMinutes) { return numMinutes * 60000; }

float distance(float x1, float y1, float x2, float y2) {
  return (float)sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

CRGB getColor(CRGB color1, CRGB color2, int16_t n, int16_t x) {
  uint8_t r = color1[0] + x * (color2[0] - color1[0]) / n;
  uint8_t g = color1[1] + x * (color2[1] - color1[1]) / n;
  uint8_t b = color1[2] + x * (color2[2] - color1[2]) / n;
  return CRGB(r, g, b);
};

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double pointAlongCircumferenceX(double radius, double originX, double d) {
  double degs = (d - 90 < 0) ? (d + 270) : (d - 90);
  double rads = degs * PI / 180;
  return originX + radius * cos(rads);
}

double pointAlongCircumferenceY(double radius, double originY, double d) {
  double degs = (d - 90 < 0) ? (d + 270) : (d - 90);
  double rads = degs * PI / 180;
  return originY + radius * sin(rads);
}


bool all(bool done[]) {
  for(int d = 0; d < NUM_LEDS_MAX; d++) {
    if (!done[d]) {
      return false;
    }
  }
  return true;
}

int size(int y) {
  if (y == 0 || y == 1 || y == 25 || y == 26) {
    return 17;
  } else if (y == 2 || y == 24) {
    return 19;
  } else if (y == 3 || y == 4 || y == 22 || y == 23) {
    return 21;
  } else if (y == 5 || y == 6 || y == 20 || y == 21) {
    return 23;
  } else if (y == 7 || y == 8 || y == 18 || y == 19) {
    return 25;
  } else if (y == 9 || y == 17) {
    return 27;
  } else if (y == 10 || y == 11 || y == 15 || y == 16) {
    return 29;
  } else if (y == 12 || y == 13 || y == 14) {
    return 31;
  }
}

int getIndex(int y, int x) {
  if (y == 0) { return x; }
  else if (y == 1) { return x + 17; }
  else if (y == 2) { return x + 34; }
  else if (y == 3) { return x + 53; }
  else if (y == 4) { return x + 74; }
  else if (y == 5) { return x + 95; }
  else if (y == 6) { return x + 118; }
  else if (y == 7) { return x + 141; }
  else if (y == 8) { return x + 166; }
  else if (y == 9) { return x + 191; }
  else if (y == 10) { return x + 218; }
  else if (y == 11) { return x + 247; }
  else if (y == 12) { return x + 276; }
  else if (y == 13) { return x + 307; }
  else if (y == 14) { return x + 338; }
  else if (y == 15) { return x + 369; }
  else if (y == 16) { return x + 398; }
  else if (y == 17) { return x + 427; }
  else if (y == 18) { return x + 454; }
  else if (y == 19) { return x + 479; }
  else if (y == 20) { return x + 504; }
  else if (y == 21) { return x + 527; }
  else if (y == 22) { return x + 550; }
  else if (y == 23) { return x + 571; }
  else if (y == 24) { return x + 592; }
  else if (y == 25) { return x + 611; }
  else if (y == 26) { return x + 628; }
}

int ctox(int y, int c) {
  if (y == 0 || y == 1 || y == 25 || y == 26) {
    return c - 7;
  } else if (y == 2 || y == 24) {
    return c - 6;
  } else if (y == 3 || y == 4 || y == 22 || y == 23) {
    return c - 5;
  } else if (y == 5 || y == 6 || y == 20 || y == 21) {
    return c - 4;
  } else if (y == 7 || y == 8 || y == 18 || y == 19) {
    return c - 3;
  } else if (y == 9 || y == 17) {
    return c - 2;
  } else if (y == 10 || y == 11 || y == 15 || y == 16) {
    return c - 1;
  } else if (y == 12 || y == 13 || y == 14) {
    return c;
  }
}

int itox(int index) {
  if (index < 17) { return index; }
  else if (index < 34) { return index - 17; }
  else if (index < 53) { return index - 34; }
  else if (index < 74) { return index - 53; }
  else if (index < 95) { return index - 74; }
  else if (index < 118) { return index - 95; }
  else if (index < 141) { return index - 118; }
  else if (index < 166) { return index - 141; }
  else if (index < 191) { return index - 166; }
  else if (index < 218) { return index - 191; }
  else if (index < 247) { return index - 218; }
  else if (index < 276) { return index - 247; }
  else if (index < 307) { return index - 276; }
  else if (index < 338) { return index - 307; }
  else if (index < 369) { return index - 338; }
  else if (index < 398) { return index - 369; }
  else if (index < 427) { return index - 398; }
  else if (index < 454) { return index - 427; }
  else if (index < 479) { return index - 454; }
  else if (index < 504) { return index - 479; }
  else if (index < 527) { return index - 504; }
  else if (index < 550) { return index - 527; }
  else if (index < 571) { return index - 550; }
  else if (index < 592) { return index - 571; }
  else if (index < 611) { return index - 592; }
  else if (index < 628) { return index - 611; }
  else { return index - 628; }
}

int itoy(int index) {
  if (index < 17) { return 0; }
  else if (index < 34) { return 1; }
  else if (index < 53) { return 2; }
  else if (index < 74) { return 3; }
  else if (index < 95) { return 4; }
  else if (index < 118) { return 5; }
  else if (index < 141) { return 6; }
  else if (index < 166) { return 7; }
  else if (index < 191) { return 8; }
  else if (index < 218) { return 9; }
  else if (index < 247) { return 10; }
  else if (index < 276) { return 11; }
  else if (index < 307) { return 12; }
  else if (index < 338) { return 13; }
  else if (index < 369) { return 14; }
  else if (index < 398) { return 15; }
  else if (index < 427) { return 16; }
  else if (index < 454) { return 17; }
  else if (index < 479) { return 18; }
  else if (index < 504) { return 19; }
  else if (index < 527) { return 20; }
  else if (index < 550) { return 21; }
  else if (index < 571) { return 22; }
  else if (index < 592) { return 23; }
  else if (index < 611) { return 24; }
  else if (index < 628) { return 25; }
  else { return 26; }
}
