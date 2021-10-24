// Receives data from the receiver ESP8266

//ESP8266 GND - Due GND
//ESP8266 VCC - Due 3.3V
//ESP8266 TX - Due RX3
//ESP8266 RX - Due TX3
//ESP8266 EN - Due pin 53 (always HIGH)

//always high
int EN_ESP8266 = 53;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  pinMode(EN_ESP8266, OUTPUT);
  digitalWrite(EN_ESP8266, HIGH);
}

void loop() {
  if (Serial3.available()) {
    char a = Serial3.read();
    Serial.write(a);
  }
}
/*
void loop() {
  while (Serial.available() > 0) {
    char a = Serial.read();
    Serial3.write(a);
  }
}

void serialEvent3() {
  while (Serial3.available() > 0) {
    char a = Serial3.read();
    Serial.write(a);
  }
}
*/
