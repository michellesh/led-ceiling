CHSV CHSV_BLACK = CHSV(0, 0, 0);
CHSV CHSV_WHITE = CHSV(100, 0, 255);
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

CHSV blendCHSV(CHSV color1, CHSV color2, float percent) {
  return CHSV(
    color2.h + percent * (color1.h - color2.h) / 100,
    color2.s + percent * (color1.s - color2.s) / 100,
    color2.v + percent * (color1.v - color2.v) / 100
  );
}
