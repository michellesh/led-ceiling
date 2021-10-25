int incrementPattern(int activePattern, int numPatterns) {
  if (activePattern < (numPatterns - 1)) {
    return activePattern + 1;
  }
  return 0;
}

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
    }

    return *this;
  }

  bool _subPatternComplete() {
    switch (_activePattern) {
      case SPIRAL:
        return _spiral.complete();
      default:
        return _subPatternTimer.complete();
    }
  }

  void _setNextPattern() {
    allBlack();
    _activePattern = incrementPattern(_activePattern, 2);
    _nextSubPattern = 0;
    _setNextSubPattern();
    _subPatternTimer.reset();
  }

  void _setNextSubPattern() {
    _activeSubPattern = _nextSubPattern;
    switch (_activePattern) {
      case SPIRAL:
        _spiral = _activeSubPattern < 6
                  ? _spiral.withDensity(_activeSubPattern % 6).directionInward().play()
                  : _spiral.withDensity(_activeSubPattern % 6).directionOutward().play();
        _nextSubPattern = incrementPattern(_activeSubPattern, 12);
        break;
      case PAINTBRUSH:
        _paintbrush =
          _activeSubPattern == 0 ? _paintbrush.color(CHSV_BLUE, CHSV_BLUE) :
          _activeSubPattern == 1 ? _paintbrush.color(CHSV_YELLOW, CHSV_YELLOW) :
          _activeSubPattern == 2 ? _paintbrush.color(CHSV_GREEN).eraser() :
          _activeSubPattern == 3 ? _paintbrush.color(CHSV_RED, CHSV_YELLOW).speed(0.1) :
          _activeSubPattern == 4 ? _paintbrush.color(CHSV_RED, CHSV_YELLOW).eraser().speed(1) :
                                   _paintbrush.color(CHSV_RED, CHSV_PURPLE).rainbow().radius(4);
        _paintbrush = _paintbrush.play();
        _nextSubPattern = incrementPattern(_activeSubPattern, 6);
        break;
      default:
        break;
    }
  }
};
