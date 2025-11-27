#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <emscripten/html5.h>
#include <emscripten.h>


// EMSCRIPTEN_KEEPALIVE
// void addNum(int a, int b, int *result) {
//   *result = a + b;
// }

// EMSCRIPTEN_KEEPALIVE
// int main() {
//   printf("hello, world!\n");
//   return 0;
// }


void stringToUpper(char *str) {
    char *ptr = str;
    while (*ptr) {
        *ptr = toupper((unsigned char)*ptr);
        ptr++;
    }
}

// convert binary string to int like "1011" → integer
uint32_t binaryStringToInt(const char *binStr) {
    uint32_t value = 0;
    while (*binStr) {
        value = (value << 1) | (*binStr - '0'); //this is basically shl and add
        binStr++;
    }
    return value;
}

// convert int to binary string with specified bitwidth
char* intToBinaryString(uint32_t value, int bitWidth) {
    char *binary = (char*)malloc(bitWidth + 1); // make array with size of bitWidth + 1 for null terminator
    for (int i = bitWidth - 1; i >= 0; i--) {
        binary[bitWidth - 1 - i] = ((value >> i) & 1) ? '1' : '0'; // shr and mask
    }
    binary[bitWidth] = '\0';
    return binary;
}

EMSCRIPTEN_KEEPALIVE
char* bitStringOperations(char *a, char *b, char *op, int bitWidth) {
  uint32_t result = 0;
  uint32_t mask;
  uint32_t A;
  uint32_t B;

  A = binaryStringToInt(a);
  B = binaryStringToInt(b);

  switch (bitWidth) {
       case 1:
          mask = 0x1;        // 0000 0001
          break;
      case 4:
          mask = 0xF;        // 0000 1111
          break;
      case 8:
          mask = 0xFF;       // 1111 1111
          break;
      case 16:
          mask = 0xFFFF;     // 16 bits
          break;
      default:
          mask = 0xFFFFFFFF; // 32 bits
          bitWidth = 32;
          break;
  }

  A &= mask;
  B &= mask;

  stringToUpper(op);

  if (strcmp(op, "AND") == 0) {
      result = A & B;
  } else if (strcmp(op, "OR") == 0) {
      result = A | B;
  } else if (strcmp(op, "XOR") == 0) {
      result = A ^ B;
  } else if (strcmp(op, "NOT") == 0) {
      result = ~A & mask; 
  } else if (strcmp(op, "SHL") == 0) {
      result = (A << B) & mask;
  } else if (strcmp(op, "SHR") == 0) {
      result = (A >> B) & mask;
  } else if (strcmp(op, "ROL") == 0) {
      uint8_t shift = B % bitWidth; 
      result = ((A << shift) | (A >> (bitWidth - shift))) & mask;
  } else if (strcmp(op, "ROR") == 0) {
      uint8_t shift = B % bitWidth;
      result = ((A >> shift) | (A << (bitWidth - shift))) & mask;
  } else {
      result = 0; 
  }
  return intToBinaryString(result, bitWidth);
}