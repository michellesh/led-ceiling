// Receives data from the sender ESP8266
// Sends that data to the Arduino Due

// Connect RX pin (ESP) to 18/TX1 (Due)
// Connect TX pin (ESP) to 19/RX1 (Due)

void setup() {
  Serial.begin(250000);
}

void loop() {
  Serial.println("hello");
  delay(1000);
}
