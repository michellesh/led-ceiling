struct Paintbrush {
  int _hue = HUE_BLUE;  // the color of the paintbrush
  float _radius = 2;    // the width (size) of the paintbrush (in pixels)
  float _speed = 0.5;   // [0.05 - 1] how fast the paintbrush moves across canvas
  int _targetEdge = 2;  // index of target edge
  px _center = pointOnLine(EDGES[0].p1, EDGES[0].p2, 0.5);  // location of paintbrush
  px _target = pointOnLine(EDGES[_targetEdge].p1, EDGES[_targetEdge].p2, 0.1);
  px _start = _center;

  Paintbrush withHue(int hue) {
    Paintbrush p = *this;
    p._hue = hue;
    return p;
  }

  Paintbrush withSpeed(float speed) {
    Paintbrush p = *this;
    p._speed = speed;
    return p;
  }

  void play(unsigned long totalCycleTime) {
    Timer timer = {totalCycleTime};
    timer.start();

    while (!timer.complete()) {
      movePaintbrush();
      showPaintbrush();
    }
  }

  void movePaintbrush() {
    float currentDist = distance(_start, _center);
    float totalDist = distance(_start, _target);
    if (currentDist < totalDist) {
      _center = getNewCenter(currentDist, totalDist);
    } else {
      _center = _target;
      setNewDestination();
    }
  }

  px getNewCenter(float currentDist, float totalDist) {
    return {
      mapf(currentDist + _speed, 0, totalDist, _start.row, _target.row),
      mapf(currentDist + _speed, 0, totalDist, _start.col, _target.col)
    };
  }

  void setNewDestination() {
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

  float getMaxDistance() {
    px farthestPixel = {_center.row + _radius, _center.col + _radius};
    return distance(_center, farthestPixel);
  }

  void showPaintbrush() {
    for (int row = (_center.row - _radius); row <= (_center.row + _radius); row++) {
      for (int col = (_center.col - _radius); col <= (_center.col + _radius); col++) {
        px p = {row, col};
        if (p.inBounds()) {
          float brightness = mapf(distance(p, _center), 0, getMaxDistance(), 255, 0);
          leds[p.rowInt()][p.colInt()] = CHSV(_hue, 255, (uint8_t)brightness);
        }
      }
    }
    FastLED.show();
  }
};
