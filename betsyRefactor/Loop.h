struct Loop { // really HourLoop
  int _activePattern = SPIRAL;
  int _activeSubPattern = 0;
  int _nextSubPattern = 0;
  int _numPatterns = 2;

  Spiral _spiral;
  Paintbrush _paintbrush;

  Timer _patternTimer = {minutes(1)};
  Timer _subPatternTimer = {seconds(15)};

  Loop start() {
    _nextSubPattern = _setSubPattern();
    _patternTimer.start();
    _subPatternTimer.start();
    return *this;
  }

  Loop play(Button button) {
    if (button.id == N64_CDOWN && button.value1 == 1) {
      _activeSubPattern = 0;
      _nextPattern();
    }

    if (button.id == N64_CRIGHT && button.value1 == 1) {
      _activeSubPattern = _nextSubPattern;
      _nextSubPattern = _setSubPattern();
      _subPatternTimer.reset();
    }

    if (_patternTimer.complete()) {
      _nextPattern();
      _patternTimer.reset();
    }

    if (_subPatternTimer.complete()) {
      _activeSubPattern = _nextSubPattern;
      _nextSubPattern = _setSubPattern();
      _subPatternTimer.reset();
    }

    switch (_activePattern) {
      case SPIRAL:
        _spiral = _spiral.play();
        break;
      case PAINTBRUSH:
        _paintbrush = _paintbrush.play();
        break;
    }

    return *this;
  }

  void _nextPattern() {
    if (_activePattern < _numPatterns) {
      _activePattern++;
    } else {
      _activePattern = 0;
    }
  }

  int _setSubPattern() {
    switch (_activePattern) {
      case SPIRAL:
        _spiral = _activeSubPattern < 6
                  ? _spiral.withDensity(_activeSubPattern % 6).directionInward().play()
                  : _spiral.withDensity(_activeSubPattern % 6).directionOutward().play();
        return _activeSubPattern < 12 ? _activeSubPattern + 1 : 0;
      case PAINTBRUSH:
        _paintbrush =
          _activeSubPattern == 0 ? _paintbrush.color(CHSV_BLUE, CHSV_BLUE) :
          _activeSubPattern == 1 ? _paintbrush.color(CHSV_YELLOW, CHSV_YELLOW) :
          _activeSubPattern == 2 ? _paintbrush.color(CHSV_GREEN).eraser() :
          _activeSubPattern == 3 ? _paintbrush.color(CHSV_RED, CHSV_YELLOW).speed(0.1) :
          _activeSubPattern == 4 ? _paintbrush.color(CHSV_RED, CHSV_YELLOW).eraser().speed(1) :
                                   _paintbrush.color(CHSV_RED, CHSV_PURPLE).rainbow().radius(4);
        _paintbrush = _paintbrush.play();
        return _activeSubPattern < 6 ? _activeSubPattern + 1 : 0;
    }
  }
};
