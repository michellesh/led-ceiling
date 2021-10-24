uint8_t betsy_receiverAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define N64_START   0
#define N64_Z       1
#define N64_B       2
#define N64_A       3
#define N64_L       4
#define N64_R       5
#define N64_CUP     6
#define N64_CDOWN   7
#define N64_CRIGHT  8
#define N64_CLEFT   9
#define N64_DUP     10
#define N64_DDOWN   11
#define N64_DRIGHT  12
#define N64_DLEFT   13
#define N64_AXISX   14
#define N64_AXISY   15

#define DELIM   ':'

#define NUM_BUTTONS  16

struct msg {
  int buttonId;
  int buttonValue;
};

String stringifyMsg(int buttonId, int buttonValue) {
  return String(buttonId) + DELIM + String(buttonValue);
}

msg parseMsg(String str) {
  int index = 0;
  String parts[2] = {"", ""};
  for (int i = 0; i < str.length(); i++) {
    char c = str.charAt(i);
    if (c == DELIM) {
      index = 1;
    } else {
      parts[index] += c;
    }
  }
  return {parts[0].toInt(), parts[1].toInt()};
}
