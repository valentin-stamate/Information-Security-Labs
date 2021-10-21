//
// Created by valentin on 10/19/21.
//

#include <cstring>
#include <cstdlib>
#include "Util.h"

char *Util::getCopyAndRound(const char *message, int len, int round, int &newLen) {
    int blocks = (len + round) / round - (len % round == 0);
    int newLength = (blocks) * round;

    char* newMessage = (char*) malloc(newLength * sizeof(char) + 1);

    strcpy(newMessage, message);

    for (int i = len; i < newLength; i++) {
        newMessage[i] = ' ';
    }

    newMessage[newLength] = '\0';
    newLen = newLength;
    return newMessage;
}

char **Util::splitIntoBlocks(const char *text, int len, int blockSize, int &blocksNumber) {
    blocksNumber = (len + blockSize) / blockSize - (len % blockSize == 0);

    char** blocks = (char**) malloc(sizeof(char*) * blocksNumber);

    for (int i = 0; i < blocksNumber; i++) {
        blocks[i] = (char*) malloc(sizeof(char) * blockSize + 1); // +1 for \0
    }

    int newLen;
    char* copyText = getCopyAndRound(text, len, blockSize, newLen);

    int j = 0;
    for (int i = 0; i < newLen; i += blockSize) {
        strncpy(blocks[j], copyText + i, blockSize);
        blocks[j][blockSize] = '\0';
        j++;
    }

    return blocks;
}

void Util::freeArray(char **array, int n) {
    for (int i = 0; i < n; i++) {
        free(array[i]);
    }
}


