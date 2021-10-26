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
  int _numPatterns = 3;

  Spiral _spiral;
  Paintbrush _paintbrush;
  Ripples _ripples;

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
    _activePattern = incrementPattern(_activePattern, _numPatterns);
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
        _spiral =
          _activeSubPattern < 6 ? _spiral.density(_activeSubPattern % 6).directionInward() :
                                  _spiral.density(_activeSubPattern % 6).directionOutward();
        _nextSubPattern = incrementPattern(_activeSubPattern, 12);
        break;
      case PAINTBRUSH:
        _paintbrush =
          _activeSubPattern == 0 ? _paintbrush.reset().color(CHSV_BLUE, CHSV_BLUE) :
          _activeSubPattern == 1 ? _paintbrush.reset().color(CHSV_YELLOW, CHSV_YELLOW) :
          _activeSubPattern == 2 ? _paintbrush.reset().color(CHSV_GREEN).eraser() :
          _activeSubPattern == 3 ? _paintbrush.reset().color(CHSV_RED, CHSV_YELLOW).speed(0.1) :
          _activeSubPattern == 4 ? _paintbrush.reset().color(CHSV_RED, CHSV_YELLOW).eraser().speed(1) :
                                   _paintbrush.reset().color(CHSV_RED, CHSV_PURPLE).rainbow().radius(4);
        _nextSubPattern = incrementPattern(_activeSubPattern, 6);
        break;
      case RIPPLE:
        _ripples =
          _activeSubPattern == 0 ? _ripples.reset().randomColors().centered().width(5) :
          _activeSubPattern == 1 ? _ripples.reset().randomColors().centered().width(10) :
                                   _ripples.reset().randomColors().randomCenters().width(5);
        _nextSubPattern = incrementPattern(_activeSubPattern, 3);
        break;
      default:
        break;
    }
  }
};
