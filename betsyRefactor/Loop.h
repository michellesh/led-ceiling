int MINUTES_PER_PATTERN = 3;
int SECONDS_PER_SUBPATTERN = 45;

struct Loop {
  int _numPatterns = 5;
  int _patterns[5] = {SPIRAL, PAINTBRUSH, RIPPLE, WATER, CATERPILLARS};
  int _activePatternIndex = 0;
  int _activePattern = _patterns[_activePatternIndex];
  int _activeSubPattern = 0;
  int _nextSubPattern = 0;

  Spiral _spiral;
  Paintbrush _paintbrush;
  Ripples _ripples;
  Water _water;
  Caterpillars _caterpillars;

  Timer _patternTimer = {minutes(MINUTES_PER_PATTERN)};
  Timer _subPatternTimer = {seconds(SECONDS_PER_SUBPATTERN)};

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
    _activePatternIndex = rollingInc(_activePatternIndex, _numPatterns);
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
        _nextSubPattern = rollingInc(_activeSubPattern, 12);
        break;
      case PAINTBRUSH:
        _paintbrush = getPaintbrush();
        _nextSubPattern = rollingInc(_activeSubPattern, 6);
        break;
      case RIPPLE:
        if (_activeSubPattern == 0) {
          _ripples = _ripples.randomColors().centered().width(5).init();
        } else if (_activeSubPattern == 1) {
          _ripples = _ripples.randomColors().centered().width(10).init();
        } else if (_activeSubPattern == 2) {
          _ripples = _ripples.randomColors().centered().width(20).init();
        } else if (_activeSubPattern == 3) {
          _ripples = _ripples.randomColors().randomCenters().width(5).init();
        } else {
          _ripples = _ripples.randomColors().randomCenters().randomWidths().init();
        }
        _nextSubPattern = rollingInc(_activeSubPattern, 6);
        break;
      case WATER:
        _water = getWater();
        _nextSubPattern = rollingInc(_activeSubPattern, 6);
        break;
      case CATERPILLARS:
        _caterpillars = getCaterpillars();
        _nextSubPattern = rollingInc(_activeSubPattern, 20);
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

  Caterpillars getCaterpillars() {
    return _caterpillars.maxWidth(_activeSubPattern).reset();
  }

  Water getWater() {
    return _activeSubPattern == 0 ? _water.reset() : _water;
  }
};
