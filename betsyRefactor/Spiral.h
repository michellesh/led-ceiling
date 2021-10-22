int OUTWARD = 0;
int INWARD = 1;

struct Spiral {
  int _density = 0;
  int _direction = INWARD;
  int _numRays = 8;

  Spiral withDensity(int density) {
    Spiral s = *this;
    s._density = density;
    return s;
  }

  Spiral directionInward() {
    Spiral s = *this;
    s._direction = INWARD;
    return s;
  }

  Spiral directionOutward() {
    Spiral s = *this;
    s._direction = OUTWARD;
    return s;
  }

  void play(int numTimes) {
    int offset;
    for (int n = 0; n < numTimes; n++) {
      playSingleSpiral(CRGB::Blue, CRGB::White);
      playSingleSpiral(CRGB::Black, CRGB::Black);
    }
  }

  void playSingleSpiral(CRGB color1, CRGB color2) {
    int offset = 0;
    if (_direction == OUTWARD) {
      for(float radius = 0; radius < RADIUS; radius += 0.25) {
        showRays(radius, offset, color1, color2);
        offset += _density;
      }
    } else {
      for(float radius = RADIUS; radius >= 0; radius -= 0.25) {
        showRays(radius, offset, color1, color2);
        offset += _density;
      }
    }
  }

  void showRays(float radius, int offset, CRGB color1, CRGB color2) {
    for (int d = 0; d < _numRays; d++) {
      int deg = d * (360 / _numRays);
      px p = pointOnCircumference(radius, ORIGIN, deg + offset).getRounded(deg);
      if (p.inBounds()) {
        leds[p.rowInt()][p.colInt()] = d % 2 == 0 ? color1 : color2;
      }
    }
    FastLED.show();
  }
};
