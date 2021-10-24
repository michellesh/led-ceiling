// Receives data from the Arduino UNO
// Sends that data to the receiver ESP8266

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  if (Serial.available()) {
    Serial.write(Serial.read());
  }
}
