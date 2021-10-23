#include <SoftwareSerial.h>
#include <N64Controller.h>

N64Controller n64(2);
SoftwareSerial espSerial(5, 6);

String str;

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
  n64.begin();
  delay(2000);
}

void loop() {
  n64.update();
  sendN64Status();
  delay(1000);
}

void sendN64Status() {
  str = String("Start:  ")   + String(n64.Start()) +
        String("\nZ:      ") + String(n64.Z()) +
        String("\nB:      ") + String(n64.B()) +
        String("\nA:      ") + String(n64.A()) +
        String("\nL:      ") + String(n64.L()) +
        String("\nR:      ") + String(n64.R()) +
        String("\nCup:    ") + String(n64.C_up()) +
        String("\nCdown:  ") + String(n64.C_down()) +
        String("\nCright: ") + String(n64.C_right()) +
        String("\nCleft:  ") + String(n64.C_left()) +
        String("\nDup:    ") + String(n64.D_up()) +
        String("\nDdown:  ") + String(n64.D_down()) +
        String("\nDright: ") + String(n64.D_right()) +
        String("\nDleft:  ") + String(n64.D_left()) +
        String("\nStick X:") + String(n64.axis_x(), DEC) +
        String("\nStick Y:") + String(n64.axis_y(), DEC);

  espSerial.println(str);
}
