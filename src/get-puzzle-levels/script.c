#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  
#include <string.h>   
#include <emscripten.h>

typedef struct {
    int  levelNumber;
    int  bitWidth;
    char  *title;
    char  *subtitle;
    char *startBitstring;
    char *goalBitstring;
    char **operation_set;
    int  operationSize;
    int operationCount;
    char *description;
} PuzzleLevel;

static char *puz_ops0[] = {"NOT", "OR 0010", "AND 0110", "OR 1100"};
static char *puz_ops1[] = {"XOR 1010", "XOR 0110", "XOR 0000", "XOR 0101"};
static char *puz_ops2[] = {"AND 10010011", "OR 11011011", "XOR 00111001", "NOT"};
static char *puz_ops3[] = {"SHL 2", "SHR 1", "OR 00000011", "OR 10000000"};
static char *puz_ops4[] = {"ROL 1", "ROR 1", "XOR 11011011"};
static char *puz_ops5[] = {"ROL 2", "ROR 3", "AND 11110011", "XOR 00111100", "OR 10000000"};

static PuzzleLevel puzzle_levels[] = {
    {1, 4, "Boolean Operations", "Level 1", "0011", "1001", puz_ops0, 4, 4, "To think that many impressive things in this world came from bits and simple boolean opearations. Complexity emerging from simplicity; very beautiful! <br/><br/> Well, life is beautiful as well, until your computer explodes :)"},
    {2, 4, "That's not the OR I know?", "Level 2", "0001", "1000",  puz_ops1, 4, 6, "That's not the OR I know? Woah! I didn't think that you're still alive.  The previous bitshifts were very boring. <br/><br/> AND likes to turn things to 0; OR likes to turn things to 1; and NOT is just changing 0s to 1s and vice versa. <br/><br/>Because of that, I'm making all of these XORs. Good luck!"},
    {3, 8, "From a Nibble to a Byte", "Level 3", "00000000", "01010101", puz_ops2, 4, 10, "Working with four bits seems very simple, so I transitioned to working with eight bits instead. That way, there will be more bytes for you to consider. You know, you really have to ask the computer scientists on how they name things." },
    {4, 8, "The Assembly Line", "Level 4", "00000001", "10101100", puz_ops3, 4, 12, "Yeah, last puzzle was harsh. More bytes means hard, you know. Shifts are such a powerful powerful as they are quicker than other operations. <br/><br/>Multiplication and division by 2 is an easy example of effective use of shifts. For example, in decimal, if you multiply by 10, it just adds a 0 at the end. This is also the case when multiplting a bit by 2."},
    {5, 8, "The World Keeps Spinning Around", "Level 5", "10010001", "01001000", puz_ops4, 3, 10, "Puzzles are meant to be fun, and so I will give you a merry-go-round operation; rotation. <br/><br/>Rotation is not really represented in higher programming languages though, so we'll give them the show here."},
    {6, 8, "Last Stand", "Level 6","00010000", "00100000", puz_ops5, 6, 12, "I guess this is the final testament of your journey. Of course, the last will always be the most challenging before fixing everything in your department. Use all the knowledge you have learned from the previous levels."}
};

EMSCRIPTEN_KEEPALIVE
int getPuzzleLevelCount() {
    return sizeof(puzzle_levels) / sizeof(puzzle_levels[0]);
}

EMSCRIPTEN_KEEPALIVE
int getPuzzleLevelNumber(int index) {
    return puzzle_levels[index].levelNumber;
}

EMSCRIPTEN_KEEPALIVE
int getPuzzleLevelBitWidth(int index) {
    return puzzle_levels[index].bitWidth;
}

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelTitle(int index) {
    return puzzle_levels[index].title;
} 

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelSubtitle(int index) {
    return puzzle_levels[index].subtitle;
} 

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelStartBitstring(int index) {
    return puzzle_levels[index].startBitstring;
}

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelGoalBitstring(int index) {
    return puzzle_levels[index].goalBitstring;
}

EMSCRIPTEN_KEEPALIVE
int getPuzzleLeveloperationSize(int index) {
    return puzzle_levels[index].operationSize;
}

EMSCRIPTEN_KEEPALIVE
int getPuzzleLevelOpCount(int index) {
    return puzzle_levels[index].operationCount;
}

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelDescription(int index) {
    return puzzle_levels[index].description;
}

EMSCRIPTEN_KEEPALIVE
char* getPuzzleLevelOperations(int index) {
    PuzzleLevel *lvl = &puzzle_levels[index];
    int totalLen = 0;
    for (int i = 0; i < lvl->operationSize; i++) {
        totalLen += strlen(lvl->operation_set[i]) + 1; 
    }

    char *buffer = (char*)malloc(totalLen);
    buffer[0] = 0;

    for (int i = 0; i < lvl->operationSize; i++) {
        strcat(buffer, lvl->operation_set[i]);
        if (i < lvl->operationSize - 1) strcat(buffer, ",");
    }

    return buffer;
}

int main() {
    return 0;
}
