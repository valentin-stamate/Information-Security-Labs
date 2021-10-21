#ifndef HOMEWORK_01_CRYPTO_H
#define HOMEWORK_01_CRYPTO_H


class Crypto {
public:
    static const short BLOCK_SIZE = 16; // 128
    const char IV[17] = "^*JDk(8dnwkd32)(";
    unsigned const char PERMUTATION[17] = {1, 3, 4, 5, 7, 9, 10, 12, 8, 15, 6, 11, 13, 2, 14, 0, '\0'};
//    char CONST_KEY[17] = generateRandomKey();


    static char* generateRandomKey(int size);
    char* xorMessages(const char* a, const char* b, int length);

    char* ECBEncryption(const char* message, int len);
    char* ECBDecryption(const char* message, int len);
    char* ECBBlockEncryption(const char* block, int blockLength);
    char* ECBBlockDecryption(const char* block, int blockLength);

    char* OFBEncryption(const char* message, int len, const char* key, const char* initVector);
    char* OFBDecryption(const char* cypherText, int len, const char* key);
    char* OFBBlockEncryption(const char* block, int blockSize, const char* key, const char* vector, char* vectorBuffer);
    char* OFBBlockDecryption(const char* block, int blockSize, const char* key, const char* vector, char* vectorBuffer);


    char* applyPermutation(const char* block, int blockLength, const unsigned char* permutation, bool reversed = false);
};


#endif //HOMEWORK_01_CRYPTO_H
