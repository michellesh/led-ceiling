int incrementPattern(int activePattern, int numPatterns) {
  if (activePattern < (numPatterns - 1)) {
    return activePattern + 1;
  }
  return 0;
}


struct Loop { // really HourLoop
  int _numPatterns = 5;
  int _patterns[5] = {SPIRAL, PAINTBRUSH, WATER, RIPPLE, CATERPILLARS};
  int _activePatternIndex = 0;
  int _activePattern = _patterns[_activePatternIndex];
  int _activeSubPattern = 0;
  int _nextSubPattern = 0;

  Spiral _spiral;
  Paintbrush _paintbrush;
  Ripples _ripples;
  Water _water;
  Caterpillars _caterpillars;

  Timer _patternTimer = {minutes(1)};
  Timer _subPatternTimer = {seconds(15)};

  Loop start() {
    _setNextSubPattern();
    _patternTimer.start();
    _subPatternTimer.start();
    return *this;
  }

  Loop play(Button button) {
    if (button.id == N64_CDOWN && button.value1 == 1) {
      _setNextPattern();
    }

    if (button.id == N64_CRIGHT && button.value1 == 1) {
      _setNextSubPattern();
      _subPatternTimer.reset();
    }

    if (_patternTimer.complete()) {
      _setNextPattern();
      _patternTimer.reset();
    }

    if (_subPatternComplete()) {
      _setNextSubPattern();
      _subPatternTimer.reset();
    }

    switch (_activePattern) {
      case SPIRAL:
        _spiral = _spiral.play();
        break;
      case PAINTBRUSH:
        _paintbrush = _paintbrush.play();
        break;
      case RIPPLE:
        _ripples = _ripples.play();
        break;
      case WATER:
        _water = _water.play();
        break;
      case CATERPILLARS:
        _caterpillars = _caterpillars.play();
        break;
    }

    return *this;
  }

  bool _subPatternComplete() {
    switch (_activePattern) {
      case SPIRAL:
        return _spiral.complete();
      case RIPPLE:
        return _ripples.complete();
      default:
        return _subPatternTimer.complete();
    }
  }

  void _setNextPattern() {
    allBlack();
    _activePatternIndex = incrementPattern(_activePatternIndex, _numPatterns);
    _activePattern = _patterns[_activePatternIndex];
    _nextSubPattern = 0;
    _setNextSubPattern();
    _subPatternTimer.reset();
  }

  void _setNextSubPattern() {
    _activeSubPattern = _nextSubPattern;
    Serial.print("_activeSubPattern: ");
    Serial.println(_activeSubPattern);
    switch (_activePattern) {
      case SPIRAL:
        _spiral = getSpiral();
        _nextSubPattern = incrementPattern(_activeSubPattern, 12);
        break;
      case PAINTBRUSH:
        _paintbrush = getPaintbrush();
        _nextSubPattern = incrementPattern(_activeSubPattern, 6);
        break;
      case RIPPLE:
        _ripples = getRipples();
        _nextSubPattern = incrementPattern(_activeSubPattern, 6);
        break;
      case WATER:
        _water = getWater();
        _nextSubPattern = incrementPattern(_activeSubPattern, 6);
        //_nextSubPattern = 0; // no sub patterns for water pattern
        break;
      case CATERPILLARS:
        _caterpillars = _caterpillars.maxWidth(_activeSubPattern).reset();
        _nextSubPattern = incrementPattern(_activeSubPattern, 20);
        break;
      default:
        break;
    }
  }

  Spiral getSpiral() {
    return _activeSubPattern < 6
      ? _spiral.density(_activeSubPattern % 6).directionInward()
      : _spiral.density(_activeSubPattern % 6).directionOutward();
  }

  Paintbrush getPaintbrush() {
    switch (_activeSubPattern) {
      case 0:
        return _paintbrush.reset().color(CHSV_BLUE, CHSV_BLUE);
      case 1:
        return _paintbrush.reset().color(CHSV_YELLOW, CHSV_YELLOW);
      case 2:
        return _paintbrush.reset().color(CHSV_GREEN, CHSV_GREEN).eraser();
      case 3:
        return _paintbrush.reset().color(CHSV_RED, CHSV_YELLOW).speed(0.1);
      case 4:
        return _paintbrush.reset().color(CHSV_RED, CHSV_YELLOW).eraser().speed(1);
      case 5:
        return _paintbrush.reset().color(CHSV_RED, CHSV_PURPLE).rainbow().radius(4);
      default:
        return _paintbrush;
    }
  }

  Ripples getRipples() {
    switch (_activeSubPattern) {
      case 0:
        return _ripples.randomColors().centered().width(5).init();
      case 1:
        return _ripples.randomColors().centered().width(10).init();
      case 2:
        return _ripples.randomColors().centered().width(20).init();
      case 3:
        return _ripples.randomColors().randomCenters().width(5).init();
      case 4:
        return _ripples.randomColors().randomCenters().randomWidths().init();
      case 5:
        return _ripples.randomColors().randomCenters().randomWidths().init();
      default:
        return _ripples;
    }
  }

  Water getWater() {
    return _activeSubPattern == 0 ? _water.reset() : _water;
  }
};
