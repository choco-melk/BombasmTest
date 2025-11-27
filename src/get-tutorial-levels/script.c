#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <emscripten/html5.h>
#include <emscripten.h>

typedef struct {
    char *title;
    char *operator;
    int  bitWidth;
    char *startBitstring;
    char **operation_set;
    int opcount;
    char *description;
} TutorialLevel;

static char *ops0[] = {"AND 0", "AND 1"};
static char *ops1[] = {"OR 0", "OR 1"};
static char *ops2[] = {"NOT"};
static char *ops3[] = {"XOR 0", "XOR 1"};
static char *ops4[] = {"SHL 1", "SHR 1", "SHL 2", "SHL 2"};
static char *ops5[] = {"ROL 1", "ROR 1", "ROR 2", "ROR 2"};

static TutorialLevel tutorial_levels[] = {
    {"AND Operator", "AND", 1, "1", ops0, 2, "Given two bits. The result of the and operation is 1 only if both bits 1s. Otherwise, it results to a 0 <br/><br/>1 AND 1 = 1<br/>1 AND 0 = 0<br/>0 AND 1 = 0<br/>0 AND 0 = 0"},
    {"OR Operator",  "OR",  1, "0", ops1, 2, "Given two bits. The result of the operation is 1 if at least one bit is a 1. Otherwise, it results to a 0 <br/><br/>1 OR 1 = 1<br/>1 OR 0 = 1 <br/>0 OR 1 = 1 <br/>0 OR 0 = 0 <br/>"},
    {"NOT Operator", "NOT", 1, "0", ops2, 1, "Turns a 0 to a 1 and vice versa<br/><br/> NOT 0 = 1<br/>NOT 1 = 0<br/>"},
    {"XOR Operator", "XOR", 1, "0", ops3, 2, "Given two bits. The result of the operation is 1 only when the bits are different.<br/><br/>1 XOR 1 = 0<br/>1 XOR 0 = 1<br/>0 XOR 1 = 1<br/>0 XOR 0 = 0<br/>"},
    {"Shift Operators", "SHL, SHR", 8, "01000101", ops4, 4, "For the Shift Left Operation, SHL moves all bits to the left by a certain amount. The most significant bit (the leftmost bit) will be shifted out and the least significant bit (the rightmost bit) will be a 0 <br/> For the Shift Right Operation, SHR moves all bits to the right by a certain amount. <br/><br/> This time, the least significant bit (the rightmost bit) will be shifted out and the most significant bit (the leftmost bit) will be a 0 "},
    {"Rotate Operators", "ROL, ROR", 8, "01000101", ops5, 4, "For the Rotate Left Operation, ROL moves all bits to the left by a certain amount. The most significant bit (the leftmost bit) will be put to the place of the least significant bit (the rightmost bit). <br/><br/> For the Rotate Right Operation, SHR moves all bits to the right by a certain amount. This time, the least significant bit (the rightmost bit) will be put to the place of the most significant bit (the leftmost bit) "},
};

EMSCRIPTEN_KEEPALIVE
int getTutorialLevelCount() {
    return sizeof(tutorial_levels) / sizeof(tutorial_levels[0]);
}

EMSCRIPTEN_KEEPALIVE
char* getTutorialLevelTitle(int index) {
    return tutorial_levels[index].title;
}

EMSCRIPTEN_KEEPALIVE
char* getTutorialLevelOperator(int index) {
    return tutorial_levels[index].operator;
}

EMSCRIPTEN_KEEPALIVE
int getTutorialLevelBitWidth(int index) {
    return tutorial_levels[index].bitWidth;
}

EMSCRIPTEN_KEEPALIVE
char* getTutorialLevelStartBitstring(int index) {
    return tutorial_levels[index].startBitstring;
}

EMSCRIPTEN_KEEPALIVE
char* getTutorialLevelDescription(int index) {
    return tutorial_levels[index].description;
}

char* getTutorialLevelOperations(int index) {
    TutorialLevel *lvl = &tutorial_levels[index];

    int totalLen = 0;
    for (int i = 0; i < lvl->opcount; i++) {
        totalLen += strlen(lvl->operation_set[i]);
    }
    totalLen += lvl->opcount; 

    char *buffer = (char*)malloc(totalLen);
    buffer[0] = '\0';

    for (int i = 0; i < lvl->opcount; i++) {
        strcat(buffer, lvl->operation_set[i]);
        if (i < lvl->opcount - 1) strcat(buffer, ",");
    }

    return buffer;
}

int main() {    
    return 0;
}
