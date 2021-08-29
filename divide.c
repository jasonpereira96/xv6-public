#include "types.h"
#include "stat.h"
#include "user.h"
// #include "string.h"
// #include "stdio.h"

const int POSITIVE = 1;
const int NEGATIVE = 0;

typedef int bool;
enum {
  false,
  true
};

bool is_digit(char ch) {
  return 48 <= ch && ch <= 57;
}
bool is_valid_int(char s[]) {
  bool sign = s[0] == '-' ? NEGATIVE : POSITIVE;
  int start = sign ? 0 : 1;
  for (int index = start; index < strlen(s); index++) {
    if (!is_digit(s[index])) {
      return false;
    }
  }
  return true;
}

int get_value(char num) {
  return num - 48;
}

int parse_int(char s[]) {
  bool sign = s[0] == '-' ? NEGATIVE : POSITIVE;
  int result = 0;
  int start = sign ? 0 : 1;
  for (int index = start; index < strlen(s); index++) {
    int value = get_value(s[index]);
    result = result * 10 + value;
  }
  return result * (sign == POSITIVE ? 1 : -1);
}

bool validate_input(int argc, char *argv[]) {
  if (argc != 3) {
    printf(1, "%s", "Must have exactly 2 arguments \n");
    return false;
  }
  bool is_valid = is_valid_int(argv[1]) && is_valid_int(argv[2]);

  if (!is_valid) {
  printf(1, "%s", "Arguments invalid. Both must be integers \n");
    return false;
  }
  if (parse_int(argv[2]) == 0) {
    printf(1, "%s", "Cannot divide by 0 \n");
    return false;
  }
  return true;
}

int main (int argc, char *argv[]) {
  if (validate_input(argc, argv)) {
    int a = parse_int(argv[1]);
    int b = parse_int(argv[2]);
    printf(1, "%d / %d is ", a, b);

    if (a*b < 0) {
      printf(1, "%c", '-');
    }
    if (a < 0) {
      a = -a;
    }
    if (b < 0) {
      b = -b;
    }

    int Q = a / b;
    printf(1, "%d", Q);

    int R1 = a - (b * Q);
    if (Q == 0 && R1 == 0) {
      printf(1, "\n");
      exit();
    }
    if (R1 == 0) {
     printf(1, "\n");
     exit();
    }
    printf(1, "%c", '.');
    R1 = R1 * 10;
    Q = R1 / b;
    printf(1, "%d", Q);

    int R2 = R1 - (b * Q);
    if (R2 == 0) {
     printf(1, "\n");
     exit();
    }
    R2 = R2 * 10;
    Q = R2 / b;
    printf(1, "%d", Q);
    printf(1, "\n");
  }
  exit();
}