int BRIGHTNESS_THRESHOLD_BACKGROUND = 5;
int BRIGHTNESS_THRESHOLD_ERASER = 40;
int BRIGHTNESS_THRESHOLD_RAINBOW = 20;

CHSV DEFAULT_COLOR = CHSV(HUE_BLUE, 255, 255);
float DEFAULT_RADIUS = 2.5;
float DEFAULT_SPEED = 0.5;
int DEFAULT_MODE = 0;
int ERASER_MODE = 1;
int RAINBOW_MODE = 2;

struct Paintbrush {
  CHSV _color = DEFAULT_COLOR;        // color of the paintbrush
  CHSV _borderColor = DEFAULT_COLOR;  // color around edge of paintbrush
  float _radius = DEFAULT_RADIUS;     // the size of the paintbrush (in pixels)
  float _speed = DEFAULT_SPEED;       // [0.05 - 1] how fast the paintbrush moves 
  int _mode = DEFAULT_MODE;
  int _targetEdge = 2;                // [0-5] index of target edge

  px _center = pointOnLine(EDGES[0].p1, EDGES[0].p2, 0.5);  // location of paintbrush
  px _target = pointOnLine(EDGES[_targetEdge].p1, EDGES[_targetEdge].p2, 0.1);
  px _start = _center;

  Paintbrush color(CHSV color, CHSV borderColor = CHSV_BLACK) {
    _color = color;
    _borderColor = borderColor == CHSV_BLACK ? color : borderColor;
    return *this;
  }

  Paintbrush speed(float speed) {
    _speed = speed;
    return *this;
  }

  Paintbrush reset() {
    _color = DEFAULT_COLOR;
    _borderColor = DEFAULT_COLOR;
    _radius = DEFAULT_RADIUS;
    _speed = DEFAULT_SPEED;
    _mode = DEFAULT_MODE;
    return *this;
  }

  Paintbrush eraser() {
    _mode = ERASER_MODE;
    return *this;
  }

  Paintbrush rainbow() {
    _mode = RAINBOW_MODE;
    return *this;
  }

  Paintbrush radius(float radius) {
    _radius = radius;
    return *this;
  }

  Paintbrush play() {
    _movePaintbrush();
    _showPaintbrush();
    return *this;
  }

  void _movePaintbrush() {
    float currentDist = distance(_start, _center);
    float totalDist = distance(_start, _target);
    if (currentDist < totalDist) {
      _center = _getNewCenter(currentDist, totalDist);
    } else {
      _center = _target;
      _setNewDestination();
    }
  }

  px _getNewCenter(float currentDist, float totalDist) {
    return {
      mapf(currentDist + _speed, 0, totalDist, _start.row, _target.row),
      mapf(currentDist + _speed, 0, totalDist, _start.col, _target.col)
    };
  }

  void _setNewDestination() {
    // reflect starting point across target edge (line of intersection)
    px pxReflection = reflectPxOverLine(_start, EDGES[_targetEdge]);
    Line reflectionLine = {pxReflection, _target};

    // calculate point where each edge line intersects reflection line
    // of those points take the one closest to the origin as the next destination
    float minDistanceFromOrigin = 0;
    px minIntersection;
    int minTargetEdge;
    for (int e = 0; e < 6; e++) {
      if (e != _targetEdge && doLinesIntersect(reflectionLine, EDGES[e])) {
        // get point of intersection with this line
        px intersection = pxLinesIntersect(reflectionLine, EDGES[e]);
        float distFromOrigin = distance(intersection, ORIGIN);
        if (minDistanceFromOrigin == 0 || distFromOrigin < minDistanceFromOrigin) {
          minDistanceFromOrigin = distFromOrigin;
          minIntersection = intersection;
          minTargetEdge = e;
        }
      }
    }
    _start = _target;
    _target = minIntersection;
    _targetEdge = minTargetEdge;
  }

  void _showPaintbrush() {
    for (int row = (_center.row - _radius); row < (_center.row + _radius + 1); row++) {
      for (int col = (_center.col - _radius); col < (_center.col + _radius + 1); col++) {
        px p = {row, col};
        if (p.inBounds() && distance(p, _center) <= _radius) {
          leds[p.rowInt()][p.colInt()] = _getColor(p);
        }
      }
    }
    FastLED.show();
  }

  CHSV _getColor(px p) {
    // Find out how close this pixel is to the edge of the paintbrush
    float percent = mapf(distance(p, _center), 0, _radius, 100, 0);

    // Pixels closer to the center should be closer to _color
    // And farther away should be closer to _borderColor
    CHSV color = blendCHSV(_color, _borderColor, percent);

    // Also make pixels farther away from center of paintbrush dimmer
    color.v = color.v * percent / 100;

    // Blend dim pixels those with the previous background color
    if (percent < BRIGHTNESS_THRESHOLD_BACKGROUND) {
      color = blendCHSV(ledsCHSV[p.rowInt()][p.colInt()], color);
      ledsCHSV[p.rowInt()][p.colInt()] = color;
    }

    // Rainbow mode trails behind random color
    if (_mode == RAINBOW_MODE && percent < BRIGHTNESS_THRESHOLD_RAINBOW) {
      int index = random(0, 7);
      color = CHSV(RAINBOW[index].h, RAINBOW[index].s, color.v);
    }

    // Eraser mode sets lowest brightnesses to black
    if (_mode == ERASER_MODE && percent < BRIGHTNESS_THRESHOLD_ERASER) {
      color = CHSV_BLACK;
    }
    return color;
  }
};
