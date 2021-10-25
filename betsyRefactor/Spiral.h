int OUTWARD = 0;
int INWARD = 1;

struct Spiral {
  int _density = 0;          // How curly the spiral is
  int _direction = OUTWARD;  // Does the spiral explode outward or implode inward
  int _numRays = 8;          // Number of lines

  float _radius = 0;         // how big the spiral is. advances as the spiral grows
  bool _erasing = false;     // flag to alternate between drawing or erasing the spiral

  CHSV _color1 = CHSV_BLUE;
  CHSV _color2 = CHSV_WHITE;

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

  Spiral play() {
    _showRays();
    _updateRadius();
    return *this;
  }

  void _updateRadius() {
    if (_direction == OUTWARD) {
      if (_radius < RADIUS) {
        _radius += 0.25;
      } else {
        _radius = 0;
        _erasing = !_erasing;
      }
    } else {
      if (_radius >= 0) {
        _radius -= 0.25;
      } else {
        _radius = RADIUS;
        _erasing = !_erasing;
      }
    }
  }

  void _showRays() {
    for (int d = 0; d < _numRays; d++) {
      int deg = d * (360 / _numRays);
      int offset = (_radius / 0.25) * _density;
      px p = pointOnCircumference(_radius, ORIGIN, deg + offset).getRounded(deg);
      if (p.inBounds()) {
        CHSV color1 = _erasing ? CHSV_BLACK : _color1;
        CHSV color2 = _erasing ? CHSV_BLACK : _color2;
        leds[p.rowInt()][p.colInt()] = d % 2 == 0 ? color1 : color2;
      }
    }
    FastLED.show();
  }
};
