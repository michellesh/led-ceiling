struct Ripple {
  CHSV _color = CHSV_BLUE;        // Color of the ripple
  float _width = 5;               // Thickness of ripple
  float _radius = (_width * -2);  // How big the ripple is. starts at 0
  float _speed = 0.25;            // TODO
  px _center = ORIGIN;            // Point where the ripple starts

  Ripple play() {
    _showRipple();
    _updateRadius();
    return *this;
  }

  Ripple width(int width) {
    Ripple r = *this;
    r._width = width;
    return r;
  }

  Ripple randomColor() {
    Ripple r = *this;
    r._color = CHSV(random(0, 255), 255, 255);
    return r;
  }

  Ripple randomCenter() {
    Ripple r = *this;
    r._center = {random(0, NUM_ROWS), random(0, NUM_COLUMNS)};
    return r;
  }

  void _showRipple() {
    for (int row = 0; row < NUM_ROWS; row++) {
      for (int col = 0; col < NUM_COLUMNS; col++) {
        px p = {row, col};
        float distFromCenter = distance(p, _center);
        if (isBackgroundPx(distFromCenter)) {
          leds[row][col] = CHSV_BLACK;
          continue;
        }
        if (p.inBounds()) {
          leds[p.rowInt()][p.colInt()] = _getColor(distFromCenter);
        }
      }
    }
    FastLED.show();
  }

  bool isBackgroundPx(float distFromCenter) {
    return abs(_radius - distFromCenter) > _width;
  }

  void _updateRadius() {
    _radius = _radius < (RADIUS + _width * 2) ? _radius + _speed : (_width * -2);
  }

  CHSV _getColor(float distFromCenter) {
    // Find out how close this pixel is to the current radius
    float distFromRadius = abs(_radius - distFromCenter);
    float percent = 100 - distFromRadius / _width * 100;

    // Pixels right on the radius will be brighter and whiter
    // Pxiels farther from radius will be dimmer and colored
    return CHSV(_color.h, _color.s, _color.v * percent / 100);
  }
};
