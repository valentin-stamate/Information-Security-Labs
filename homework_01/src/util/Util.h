#ifndef HOMEWORK_01_UTIL_H
#define HOMEWORK_01_UTIL_H


class Util {
public:
    static char* getCopyAndRound(const char* message, int len, int round, int& newLen);
    static char** splitIntoBlocks(const char* text, int len, int blockSize, int& blocksNumber);
    static void freeArray(char** array, int size);
};


#endif //HOMEWORK_01_UTIL_H
