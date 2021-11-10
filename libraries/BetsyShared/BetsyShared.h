uint8_t betsy_receiverAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define N64_START     0
#define N64_Z         1
#define N64_B         2
#define N64_A         3
#define N64_L         4
#define N64_R         5
#define N64_CUP       6
#define N64_CDOWN     7
#define N64_CRIGHT    8
#define N64_CLEFT     9
#define N64_DUP       10
#define N64_DDOWN     11
#define N64_DRIGHT    12
#define N64_DLEFT     13
#define N64_JOYSTICK  14

#define DELIM   ':'

#define SPIRAL        0
#define PAINTBRUSH    1
#define RIPPLE        2
#define WATER         3
#define CATERPILLARS  4

struct Button {
  int id;
  int value1;
  int value2;
};

String stringifyButton(Button button) {
  return String(button.id) + DELIM +
         String(button.value1) + DELIM +
         String(button.value2);
}

Button parseButton(String str) {
  int index = 0;
  String parts[3] = {"", "", ""};
  for (int i = 0; i < str.length(); i++) {
    char c = str.charAt(i);
    if (c == DELIM) {
      index++;
    } else {
      parts[index] += c;
    }
  }
  return {parts[0].toInt(), parts[1].toInt(), parts[2].toInt()};
}
