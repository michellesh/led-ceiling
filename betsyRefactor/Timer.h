unsigned long minutes(unsigned long numMinutes) { return numMinutes * 60000; }

struct Timer {
  unsigned long totalCycleTime;
  unsigned long lastCycleTime;
  void reset() {
    lastCycleTime = millis();
  };
  void start() {
    reset();
  }
  bool complete() {
    return (millis() - lastCycleTime) > totalCycleTime;
  };
};
