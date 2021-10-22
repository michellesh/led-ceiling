struct Paintbrush {
  CHSV _color = CHSV(HUE_BLUE, 255, 255);  // color of the paintbrush
  CHSV _borderColor = _color;              // color around edge of paintbrush

  float _radius = 2;    // the width (size) of the paintbrush (in pixels)
  float _speed = 0.5;   // [0.05 - 1] how fast the paintbrush moves across canvas
  int _targetEdge = 2;  // index of target edge

  px _center = pointOnLine(EDGES[0].p1, EDGES[0].p2, 0.5);  // location of paintbrush
  px _target = pointOnLine(EDGES[_targetEdge].p1, EDGES[_targetEdge].p2, 0.1);
  px _start = _center;

  Paintbrush color(CHSV color, CHSV borderColor = CHSV(0, 0, 0)) {
    Paintbrush p = *this;
    p._color = color;
    p._borderColor = borderColor;
    return p;
  }

  Paintbrush speed(float speed) {
    Paintbrush p = *this;
    p._speed = speed;
    return p;
  }

  Paintbrush blend() {
    Paintbrush p = *this;
    // TODO
    return p;
  }

  Paintbrush erase() {
    Paintbrush p = *this;
    p._borderColor = CHSV_BLACK;
    return p;
  }

  Paintbrush rainbow() {
    Paintbrush p = *this;
    // TODO
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

  float getPercentFromCenter(px p) {
    px farthestPixel = {_center.row + _radius, _center.col + _radius};
    float maxDistance = distance(_center, farthestPixel);
    return mapf(distance(p, _center), 0, maxDistance, 100, 0);
  }

  void showPaintbrush() {
    for (int row = (_center.row - _radius); row < (_center.row + _radius + 1); row++) {
      for (int col = (_center.col - _radius); col < (_center.col + _radius + 1); col++) {
        px p = {row, col};
        if (p.inBounds()) {
          // Find out how close this pixel is to the edge of the paintbrush
          float percent = getPercentFromCenter(p);

          // Pixels closer to the center should be closer to _color
          // And farther away should be closer to _borderColor
          CHSV color = blendCHSV(_color, _borderColor, percent);

          // Also make pixels farther away from center of paintbrush to be dimmer
          color.v = color.v * percent / 100;

          // For pixels dimmer than 25%, blend those with the previous background color
          if (percent < 25) {
            color = blendCHSV(ledsPrev[p.rowInt()][p.colInt()], color);
            ledsPrev[p.rowInt()][p.colInt()] = color;
          }
          leds[p.rowInt()][p.colInt()] = color;
        }
      }
    }
    FastLED.show();
  }
};
