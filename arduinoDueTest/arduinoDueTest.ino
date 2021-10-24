// Receives data from the receiver ESP8266

// Connect RX pin (ESP) to 18/TX1 (Due)
// Connect TX pin (ESP) to 19/RX1 (Due)

char DELIM = ';';

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

void setup() {
  Serial.begin(9600);
  Serial1.begin(250000);
}

void loop() {
  String buffer = "";
  while (Serial1.available() > 0) {
    buffer += (char)Serial1.read();
  }
  if (buffer.length() > 0) {
    parseN64str(buffer);
  }
  printN64data();
  delay(1000);
}

void parseN64str(String str) {
  int index = 0;
  String value = "";
  for (int i = 0; i < str.length(); i++) {
    char c = str.charAt(i);
    if (c == DELIM) {
      setN64value(index, value.toInt());
      value = "";
      index++;
    } else {
      value += c;
    }
  }
}

int setN64value(int index, int value) {
  if (index == 0) {
    data.start = value;
  } else if (index == 1) {
    data.z = value;
  } else if (index == 2) {
    data.b = value;
  } else if (index == 3) {
    data.a = value;
  } else if (index == 4) {
    data.l = value;
  } else if (index == 5) {
    data.r = value;
  } else if (index == 6) {
    data.cUp = value;
  } else if (index == 7) {
    data.cDown = value;
  } else if (index == 8) {
    data.cRight = value;
  } else if (index == 9) {
    data.cLeft = value;
  } else if (index == 10) {
    data.dUp = value;
  } else if (index == 11) {
    data.dDown = value;
  } else if (index == 12) {
    data.dRight = value;
  } else if (index == 13) {
    data.dLeft = value;
  } else if (index == 14) {
    data.axisX = value;
  } else {
    data.axisY = value;
  }
}

void printN64data() {
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
