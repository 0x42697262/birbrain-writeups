#include "stdio.h"
#include <string.h>

long PIN = 0;

void action_0(void)
{
  PIN = PIN + 0x1000441;
  return;
}

void action_1(void)
{
  PIN = (PIN % 7) * 100;
  return;
}

void action_2(void)
{
  PIN = PIN + -0x539;
  return;
}
void action_3(void)
{
  long result;

  result = (PIN * 0x58 + 8) * 5000;
  PIN = result / 0xf;
  return;
}

void action_4(void)
{
  long result2;
  long result;
  
  result = (PIN * 100 + 50000) % 13;
  result2 = result + 68;
  // printf("%d\n", result);
  // printf("%d\n", result2);
  if (result2 < 76) {
    PIN = result + 146;
  }
  else {
    PIN = result2 * 10;
  }
  return;
}

void action_5(void)
{
  PIN = PIN + 10000;
  return;
}

void action_6(void)
{
  PIN = PIN + 0x11112222;
  if (0x1ea7be3f < (long)PIN) {
    PIN = PIN ^ 0xdeadc03e;
  }
  PIN = (long)PIN / 0x4d;
  return;
}

void action_7(void)
{
  long keys [8];
  int i;
  long value;
  
  keys[0] = 0x345679603;
  keys[1] = 0x77893452;
  keys[2] = 0xffea3c9b;
  keys[3] = 0xdeadface;
  keys[4] = 0xc001c0de;
  keys[5] = 0xdeadbe3f;
  keys[6] = 0xffe13cde;
  keys[7] = 0xfe1bad1e;
  value = 0x345679603;
  for (i = 0; i < 8; i = i + 1) {
    value = value ^ keys[i];
  }
  return;
}

void action_8(void)
{
  PIN = PIN + 0x14cc5;
  return;
}

void action_9(void)
{
  PIN = PIN * (PIN % 3);
  return;
}

int verify_pin(void)
{
  if (PIN == 0x1746e) {
    return 0;
  }
  else {
    return 1;
  }
  PIN = 0;
  return 1;
}

void action(char *c){
  switch(*c){
    case '0':
      action_0();
      break;
    case '1':
      action_1();
      break;
    case '2':
      action_2();
      break;
    case '3':
      action_3();
      break;
    case '4':
      action_4();
      break;
    case '5':
      action_5();
      break;
    case '6':
      action_6();
      break;
    case '7':
      action_7();
      break;
    case '8':
      action_8();
      break;
    case '9':
      action_9();
      break;
  }
  return;
}

void try_pin(char *sequence, int length) {
    PIN = 0;  // Reset PIN before each test
    for (int i = 0; i < length; i++) {
        action(&sequence[i]);
    }
}

int main() {
    int max_length = 6;  // <-- CHANGE THIS TO YOUR DESIRED X VALUE
    char seq[max_length + 1];  // +1 for null terminator

    for (int length = 1; length <= max_length; length++) {
        int digits[max_length];
        memset(digits, 0, sizeof(digits));

        while (1) {
            // Build sequence string
            for (int i = 0; i < length; i++) {
                seq[i] = '0' + digits[i];
            }
            seq[length] = '\0';

            try_pin(seq, length);

            if (verify_pin() == 0) {
                printf("PIN found: %s\n", seq);
                printf("Numerical value of PIN: %ld (0x%x)\n", PIN, PIN);
                return 0;
            }

            // Increment digits like a number
            int pos = length - 1;
            while (pos >= 0) {
                digits[pos]++;
                if (digits[pos] < 10) {
                    break;
                } else {
                    digits[pos] = 0;
                    pos--;
                }
            }

            if (pos < 0) {
                // All combinations of this length done
                break;
            }
        }
    }

    printf("No valid PIN found.\n");
    return 1;
}
