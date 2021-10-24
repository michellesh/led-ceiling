// Receives data from the sender ESP8266
// Sends that data to the Arduino Due

// Connect RX pin (ESP) to 18/TX1 (Due)
// Connect TX pin (ESP) to 19/RX1 (Due)

char DELIM = ';';

String testStr = String(1) + DELIM +
                 String(0) + DELIM +
                 String(1) + DELIM +
                 String(0) + DELIM +
                 String(1) + DELIM +
                 String(0) + DELIM +
                 String(1) + DELIM +
                 String(0) + DELIM +
                 String(1) + DELIM +
                 String(0) + DELIM +
                 String(1) + DELIM +
                 String(0) + DELIM +
                 String(1) + DELIM +
                 String(0) + DELIM +
                 String(-12) + DELIM +
                 String(7) + DELIM;

void setup() {
  Serial.begin(250000);
}

void loop() {
  Serial.println(testStr);
  delay(1000);
}
