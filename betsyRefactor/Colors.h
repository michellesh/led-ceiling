CHSV CHSV_BLACK = CHSV(0, 0, 0);
CHSV CHSV_WHITE = CHSV(255, 255, 255);
CHSV CHSV_RED = CHSV(HUE_RED, 255, 255);
CHSV CHSV_YELLOW = CHSV(HUE_YELLOW, 255, 255);
CHSV CHSV_GREEN = CHSV(HUE_GREEN, 255, 255);
CHSV CHSV_BLUE = CHSV(HUE_BLUE, 255, 255);
CHSV CHSV_LIGHTBLUE = CHSV(196, 255, 255);
CHSV CHSV_GOLD = CHSV(43, 227, 97);
CHSV CHSV_DARKGREEN = CHSV(120, 255, 99);
CHSV CHSV_FORESTGREEN = CHSV(120, 155, 87);
CHSV CHSV_DARKRED = CHSV(0, 255, 69);
CHSV CHSV_DODGERBLUE = CHSV(210, 255, 143);

CHSV blendCHSV(CHSV color1, CHSV color2, float percent = 50);
/*
CHSV blendCHSV(CHSV color1, CHSV color2, float percent) {
  return CHSV(
    (color1.h + color2.h) * (percent / 100),
    (color1.s + color2.s) * (percent / 100),
    (color1.v + color2.v) * (percent / 100)
  );
}
*/

CHSV blendCHSV(CHSV color1, CHSV color2, float percent) {
  return CHSV(
    color2.h + percent * (color1.h - color2.h) / 100,
    color2.s + percent * (color1.s - color2.s) / 100,
    color2.v + percent * (color1.v - color2.v) / 100
  );
}

/*
CRGB getColor(CRGB color1, CRGB color2, int16_t n, int16_t x) {
  uint8_t r = color1[0] + x * (color2[0] - color1[0]) / n;
  uint8_t g = color1[1] + x * (color2[1] - color1[1]) / n;
  uint8_t b = color1[2] + x * (color2[2] - color1[2]) / n;
  return CRGB(r, g, b);
};
*/
