#define MAX_RIPPLES   2
#define RIPPLE_SPEED  0.5

struct Ripple {
  float _width = 5;               // Thickness of ripple
  float _radius = (_width * -2);  // How big the ripple is. starts at 0
  float _speed = RIPPLE_SPEED;
  CHSV _color = CHSV_BLUE;        // Color of the ripple
  px _center = ORIGIN;            // Point where the ripple starts
  CHSV prev[NUM_ROWS][NUM_COLUMNS];

  Ripple width(float width) {
    _width = width;
    return *this;
  }

  Ripple reset(int delay) {
    _radius = _width * -2 * delay;
    return *this;
  }

  Ripple color(CHSV color) {
    _color = color;
    return *this;
  }

  Ripple center(px center) {
    _center = center;
    return *this;
  }

  float maxRadius() {
    return max(
      max(_center.row, NUM_ROWS - _center.row),
      max(_center.col, NUM_COLUMNS - _center.col)
    ) + _width;
  }

  bool complete() {
    return _radius >= maxRadius();
  }

  Ripple updateRadius() {
    _radius = _radius < maxRadius() ? _radius + _speed : maxRadius();
    return *this;
  }

  Ripple show() {
    for (int row = 0; row < NUM_ROWS; row++) {
      for (int col = 0; col < NUM_COLUMNS; col++) {
        px p = {row, col};
        float distFromCenter = distance(p, _center);
        if (p.inBounds()) {
          CHSV color = _getColor(distFromCenter);
          CHSV prevColor = prev[p.rowInt()][p.colInt()];
          CHSV prevLED = ledsCHSV[p.rowInt()][p.colInt()];
          // If the previous LED is brighter because of a different ripple,
          // show that one instead
          color = (prevLED.v > color.v && prevLED != prevColor) ? prevLED : color;
          leds[p.rowInt()][p.colInt()] = color;
          ledsCHSV[p.rowInt()][p.colInt()] = color;
          prev[p.rowInt()][p.colInt()] = color;
        }
      }
    }
    return *this;
  }

  CHSV _getColor(float distFromCenter) {
    // Find out how close this pixel is to the current radius
    float distFromRadius = abs(_radius - distFromCenter);
    float percent = distFromRadius / _width;

    // Pixels right on the radius will be brighter and whiter
    // Pxiels farther from radius will be dimmer and colored
    return CHSV(_color.h, _color.s * percent, _color.v * (1 - percent));
  }
};

struct Ripples {
  int _numRipples = 2;
  Ripple _ripples[MAX_RIPPLES];

  Ripples reset() {
    for (int r = 0; r < _numRipples; r++) {
      _ripples[r] = _ripples[r].reset(r + 1);
    }
    return *this;
  }

  Ripples width(float width) {
    for (int r = 0; r < _numRipples; r++) {
      _ripples[r] = _ripples[r].width(width);
    }
    return *this;
  }

  Ripples centered() {
    for (int r = 0; r < _numRipples; r++) {
      _ripples[r] = _ripples[r].center(ORIGIN);
    }
    return *this;
  }

  Ripples randomColors() {
    for (int r = 0; r < _numRipples; r++) {
      _ripples[r] = _ripples[r].color(CHSV(random(0, 255), 255, 255));
    }
    return *this;
  }

  Ripples randomCenters() {
    for (int r = 0; r < _numRipples; r++) {
      _ripples[r] = _ripples[r].center({random(0, NUM_ROWS), random(0, NUM_COLUMNS)});
    }
    return *this;
  }

  Ripples play() {
    _showRipples();
    return *this;
  }

  bool complete() {
    for (int r = 0; r < _numRipples; r++) {
      if (!_ripples[r].complete()) {
        return false;
      }
    }
    return true;
  }

  void _showRipples() {
    for (int r = 0; r < _numRipples; r++) {
      _ripples[r] = _ripples[r].show().updateRadius();
    }
    FastLED.show();
  }
};
