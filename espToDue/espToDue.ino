// Receives data from the sender ESP8266
// Sends that data to the Arduino Due
#include <SoftwareSerial.h>

// ESP8266 pin number -> GPIO mapping
#define D0  16
#define D1  5
#define D2  4
#define D3  0
#define D4  2
#define D5  14
#define D6  12
#define D7  13
#define D8  15

//ESP8266 TX - Due RX3
//ESP8266 RX - Due TX3

//SoftwareSerial dueSerial(D5, D6);
String str;
int i = 0;

void setup() {
  Serial.begin(115200);
  //dueSerial.begin(115200);
  delay(2000);
}

void loop() {
  str = String("from esp: ") + String(i);
  //dueSerial.println(str);
  Serial.println(str);
  i++;
  delay(1000);
}
