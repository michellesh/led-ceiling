#include <SoftwareSerial.h>
#include <N64Controller.h>
#include "BetsyShared.h"

N64Controller n64(2);
SoftwareSerial espSerial(5, 6);

Button start = {N64_START, 0, 0};
Button z = {N64_Z, 0, 0};
Button b = {N64_B, 0, 0};
Button a = {N64_A, 0, 0};
Button l = {N64_L, 0, 0};
Button r = {N64_R, 0, 0};
Button cUp = {N64_CUP, 0, 0};
Button cDown = {N64_CDOWN, 0, 0};
Button cRight = {N64_CRIGHT, 0, 0};
Button cLeft = {N64_CLEFT, 0, 0};
Button dUp = {N64_DUP, 0, 0};
Button dDown = {N64_DDOWN, 0, 0};
Button dRight = {N64_DRIGHT, 0, 0};
Button dLeft = {N64_DLEFT, 0, 0};
Button joystick = {N64_JOYSTICK, 0, 0};

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
  n64.begin();
}

void loop() {
  n64.update();
  updateButton(start, n64.Start(), 0);
  updateButton(z, n64.Z(), 0);
  updateButton(b, n64.B(), 0);
  updateButton(a, n64.A(), 0);
  updateButton(l, n64.L(), 0);
  updateButton(r, n64.R(), 0);
  updateButton(cUp, n64.C_up(), 0);
  updateButton(cDown, n64.C_down(), 0);
  updateButton(cRight, n64.C_right(), 0);
  updateButton(cLeft, n64.C_left(), 0);
  updateButton(dUp, n64.D_up(), 0);
  updateButton(dDown, n64.D_down(), 0);
  updateButton(dRight, n64.D_right(), 0);
  updateButton(dLeft, n64.D_left(), 0);
  updateButton(joystick, n64.axis_x(), n64.axis_y());
  delay(10);
}

void updateButton(Button &button, int newValue1, int newValue2) {
  if (button.value1 != newValue1 || button.value2 != newValue2) {
    button.value1 = newValue1;
    button.value2 = newValue2;
    String str = stringifyButton(button);
    Serial.println(str);
    espSerial.println(str);
  }
}
