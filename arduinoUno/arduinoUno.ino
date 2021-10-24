#include <SoftwareSerial.h>
#include <N64Controller.h>
#include "BetsyShared.h"

N64Controller n64(2);
SoftwareSerial espSerial(5, 6);

int lastValue[NUM_BUTTONS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
  n64.begin();
}

void loop() {
  n64.update();
  for (int buttonId = 0; buttonId < NUM_BUTTONS; buttonId++) {
    int buttonValue = getValue(buttonId);
    if (buttonValue != lastValue[buttonId]) {
      lastValue[buttonId] = buttonValue;
      String str = stringifyMsg(buttonId, buttonValue);
      Serial.println(str);
      espSerial.println(str);
    }
  }
  delay(10);
}

int getValue(int buttonId) {
  switch (buttonId) {
    case N64_START: return n64.Start();
    case N64_Z: return n64.Z();
    case N64_B: return n64.B();
    case N64_A: return n64.A();
    case N64_L: return n64.L();
    case N64_R: return n64.R();
    case N64_CUP: return n64.C_up();
    case N64_CDOWN: return n64.C_down();
    case N64_CRIGHT: return n64.C_right();
    case N64_CLEFT: return n64.C_left();
    case N64_DUP: return n64.D_up();
    case N64_DDOWN: return n64.D_down();
    case N64_DRIGHT: return n64.D_right();
    case N64_DLEFT: return n64.D_left();
    case N64_AXISX: return n64.axis_x();
    case N64_AXISY: return n64.axis_y();
    default: return 0;
  }
}
