int MIN_WIDTH = 2;
int DEFAULT_MAX_WIDTH = 5;
float MIN_SPEED = 0.1;
float MAX_SPEED = 0.9;

struct Caterpillar {
  int _maxWidth = DEFAULT_MAX_WIDTH;
  int _col;
  float _position;
  float _speed;
  float _width;
  CHSV _color1;
  CHSV _color2;

  Caterpillar() {
    reset();
  }

  Caterpillar reset() {
    _color1 = CHSV(random8(), 255, 255);
    _color2 = CHSV(random8(), 255, 255);
    _speed = mapf(random(10), 0, 50, MIN_SPEED, MAX_SPEED);
    _width = random(MIN_WIDTH, DEFAULT_MAX_WIDTH + _maxWidth);
    _position = random(0, NUM_ROWS);
    return *this;
  }

  Caterpillar col(int col) {
    _col = col;
    return *this;
  }

  Caterpillar maxWidth(int maxWidth) {
    _maxWidth = maxWidth;
    return *this;
  }

  Caterpillar update() {
    px position = {_position, _col};
    for (int row = 0; row < NUM_ROWS; row++) {
      px p = {row, _col};
      if (p.inBounds()) {
        float distFromPosition = distance(p, position);
        CHSV color = _getColor(distFromPosition);
        leds[row][_col] = color;
      }
    }
    _position += _speed;
    if (_position >= (NUM_ROWS + _width)) {
      reset();
      _position = -1 * _width;  // reset starting at beginning
    }
    return *this;
  }

  CHSV _getColor(float distFromPosition) {
    float percent = distFromPosition / (_width / 2);
    CHSV color = blendCHSV(_color1, _color2, percent * 100);
    return CHSV(color.h, color.s, color.v * (1 - percent));
  }
};

struct Caterpillars {
  Caterpillar _caterpillars[NUM_COLUMNS];

  Caterpillars() {
    for (int col = 0; col < NUM_COLUMNS; col++) {
      _caterpillars[col] = _caterpillars[col].col(col);
    }
  }

  Caterpillars reset() {
    for (int col = 0; col < NUM_COLUMNS; col++) {
      _caterpillars[col] = _caterpillars[col].reset();
    }
    return *this;
  }

  Caterpillars maxWidth(int maxWidth) {
    for (int col = 0; col < NUM_COLUMNS; col++) {
      _caterpillars[col] = _caterpillars[col].maxWidth(maxWidth);
    }
    return *this;
  }

  Caterpillars play() {
    _showCaterpillars();
    return *this;
  }

  void _showCaterpillars() {
    for (int col = 0; col < NUM_COLUMNS; col++) {
      _caterpillars[col] = _caterpillars[col].update();
    }
    FastLED.show();
  }
};
