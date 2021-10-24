#include <ESP8266WiFi.h>
#include <espnow.h>
#include "secrets.h"

int numValues = 16;
int values[16];

struct n64data {
  bool start;
  bool z;
  bool b;
  bool a;
  bool l;
  bool r;
  bool cUp;
  bool cDown;
  bool cRight;
  bool cLeft;
  bool dUp;
  bool dDown;
  bool dRight;
  bool dLeft;
  int axisX;
  int axisY;
};

n64data data;

String testStr = String(1) + "\n" +
                 String(0) + "\n" +
                 String(1) + "\n" +
                 String(0) + "\n" +
                 String(1) + "\n" +
                 String(0) + "\n" +
                 String(1) + "\n" +
                 String(0) + "\n" +
                 String(1) + "\n" +
                 String(0) + "\n" +
                 String(1) + "\n" +
                 String(0) + "\n" +
                 String(1) + "\n" +
                 String(0) + "\n" +
                 String(-12) + "\n" +
                 String(7);

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(betsy_receiverAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void send(n64data d) {
  esp_now_send(0, (uint8_t *) &d, sizeof(d));
}

void loop() {
  parse();
  printData();
  send(data);
  Serial.println("-----");
  delay(1000);
}

void parse() {
  int index = 0;
  int numChars = testStr.length();
  int tempIndex = 0;
  char temp[3];
  for (int i = 0; i < numChars; i++) {
    char c = testStr.charAt(i);
    if (c == '\n') {
      setData(index, temp);
      tempIndex = 0;
      index++;
    } else {
      temp[tempIndex] = c;
      tempIndex++;
    }
  }
}

void printData() {
  Serial.println(data.start);
  Serial.println(data.z);
  Serial.println(data.b);
  Serial.println(data.a);
  Serial.println(data.l);
  Serial.println(data.r);
  Serial.println(data.cUp);
  Serial.println(data.cDown);
  Serial.println(data.cRight);
  Serial.println(data.cLeft);
  Serial.println(data.dUp);
  Serial.println(data.dDown);
  Serial.println(data.dRight);
  Serial.println(data.dLeft);
  Serial.println(data.axisX);
  Serial.println(data.axisY);
}

int setData(int index, char temp[]) {
  if (index == 0) {
    data.start = atoi(temp);
  } else if (index == 1) {
    data.z = atoi(temp);
  } else if (index == 2) {
    data.b = atoi(temp);
  } else if (index == 3) {
    data.a = atoi(temp);
  } else if (index == 4) {
    data.l = atoi(temp);
  } else if (index == 5) {
    data.r = atoi(temp);
  } else if (index == 6) {
    data.cUp = atoi(temp);
  } else if (index == 7) {
    data.cDown = atoi(temp);
  } else if (index == 8) {
    data.cRight = atoi(temp);
  } else if (index == 9) {
    data.cLeft = atoi(temp);
  } else if (index == 10) {
    data.dUp = atoi(temp);
  } else if (index == 11) {
    data.dDown = atoi(temp);
  } else if (index == 12) {
    data.dRight = atoi(temp);
  } else if (index == 13) {
    data.dLeft = atoi(temp);
  } else if (index == 14) {
    data.axisX = atoi(temp);
  } else {
    data.axisY = atoi(temp);
  }
}
