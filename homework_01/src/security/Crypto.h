#ifndef HOMEWORK_01_CRYPTO_H
#define HOMEWORK_01_CRYPTO_H


class Crypto {
public:
    const short BLOCK_SIZE = 16; // 128 bits
    const char IV[17] = "^*JDk(8dnwkd32)(";
    char KEY[17] = "3*^*%^8&hi*6$^%d";
    unsigned const char PERMUTATION[17] = {1, 0, 4, 5, 7, 9, 10, 12, 8, 15, 6, 11, 13, 2, 14, 3, '\0'};

    Crypto();

    char* xorMessages(const char* a, const char* b, int length);

    char* ECBEncryption(const char* message, int len, const char* key);
    char* ECBDecryption(const char* message, int len, const char* key);
    char* ECBBlockEncryption(const char* block, int blockLength, const char* key);
    char* ECBBlockDecryption(const char* block, int blockLength, const char* key);

    char* OFBEncryption(const char* message, int len, const char* key, const char* initVector);
    char* OFBDecryption(const char* cypherText, int len, const char* key);
    char* OFBBlockEncryption(const char* block, int blockSize, const char* key, const char* vector, char* vectorBuffer);
    char* OFBBlockDecryption(const char* block, int blockSize, const char* key, const char* vector, char* vectorBuffer);

    char* applyPermutation(const char* block, int blockLength, const unsigned char* permutation, bool reversed = false);

    static char* generateRandomKey(int size);
    char* RAND = nullptr;
    /* Dummy */
    char* decryptBlock(char* block, int len);
};


#endif //HOMEWORK_01_CRYPTO_H
