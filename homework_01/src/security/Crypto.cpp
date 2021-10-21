#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include "Crypto.h"
#include <openssl/rand.h>
#include <cstring>
#include <utility>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include "../util/Util.h"

char *Crypto::generateRandomKey(int size) {
    auto *key = (unsigned char*) malloc(size + 1); // for \0
    RAND_bytes(key, size);
    key[size] = '\0';
    return (char*) key;
}

char *Crypto::xorMessages(const char *a, const char *b, int length) {
    char *xorMessages = (char*) malloc(length + 1);

    for (int i = 0; i < length; i++) {
        xorMessages[i] = (char) (a[i] ^ b[i]);
    }

    xorMessages[length] = '\0';
    return xorMessages;
}

char *Crypto::ECBEncryption(const char* message, int len, const char* key) {
    int blockSize = BLOCK_SIZE;

    if (len % blockSize != 0) {
        printf("Message should be multiple of %d. Length is %d\n", blockSize, len);
        return nullptr;
    }

    char* cypherText = (char*) malloc(len + 1);
    int blocksNumber;
    char** blocks = Util::splitIntoBlocks(message, len, blockSize, blocksNumber);

    for (int i = 0; i < blocksNumber; i++) {
        char *cypherBlock = ECBBlockEncryption(blocks[i], blockSize, key);
        strcpy(cypherText + blockSize * i, cypherBlock);
        free(cypherBlock);
    }

    cypherText[len] = '\0';
    return cypherText;
}


char *Crypto::ECBDecryption(const char *message, int len, const char* key) {
    int blockSize = BLOCK_SIZE;

    if (len % blockSize != 0) {
        printf("Message should be multiple of %d. Length is %d\n", blockSize, len);
        return nullptr;
    }

    char* plaintext = (char*) malloc(len + 1);
    int blocksNumber;
    char** blocks = Util::splitIntoBlocks(message, len, blockSize, blocksNumber);

    for (int i = 0; i < blocksNumber; i++) {
        char *cypherBlock = ECBBlockDecryption(blocks[i], blockSize, key);
        strcpy(plaintext + blockSize * i, cypherBlock);
        free(cypherBlock);
    }

    plaintext[len] = '\0';
    return plaintext;
}

char *Crypto::ECBBlockEncryption(const char *block, int blockLength, const char* key) {
    char* perm = applyPermutation(block, blockLength, PERMUTATION);
    char* enc = xorMessages(perm, key, blockLength);
    free(perm);
    return enc;
}

char *Crypto::ECBBlockDecryption(const char *block, int blockLength, const char* key) {
    char* dec = xorMessages(block, key, blockLength);
    char* perm = applyPermutation(dec, blockLength, PERMUTATION, true);
    free(dec);
    return perm;
}

char *Crypto::applyPermutation(const char *block, int blockLength, const unsigned char *permutation, bool reversed) {
    char* scrambledText = (char*) malloc(blockLength + 1);
    strcpy(scrambledText, block);

    if (reversed) {
        for (int i = blockLength - 1; i >= 0; i--) {
            short j = permutation[i];
            std::swap(scrambledText[i], scrambledText[j]);
        }
    } else {
        for (int i = 0; i < blockLength; i++) {
            short j = permutation[i];
            std::swap(scrambledText[i], scrambledText[j]);
        }
    }

    scrambledText[blockLength] = '\0';
    return scrambledText;
}

char *Crypto::OFBBlockEncryption(const char *block, int blockSize, const char *key, const char *vector, char* vectorBuffer) {
    char *encryptedKey = xorMessages(key, vector, blockSize);
    strcpy(vectorBuffer, encryptedKey);
    char *cyphertext = xorMessages(encryptedKey, block, blockSize);

    free(encryptedKey);
    return cyphertext;
}

char *Crypto::OFBBlockDecryption(const char *block, int blockSize, const char *key, const char *vector, char *vectorBuffer) {
    char *encryptedKey = xorMessages(key, vector, blockSize);
    strcpy(vectorBuffer, encryptedKey);
    char *cyphertext = xorMessages(encryptedKey, block, blockSize);

    free(encryptedKey);
    return cyphertext;
}

char *Crypto::OFBEncryption(const char *message, int len ,const char* key, const char *initVector) {
    int blockSize = BLOCK_SIZE;

    if (len % blockSize != 0) {
        printf("Message should be multiple of %d. Length is %d\n", blockSize, len);
        return nullptr;
    }

    char* cypherText = (char*) malloc(blockSize + len + 1);
    strncpy(cypherText, initVector, blockSize);

    int blocksNumber;
    char** blocks = Util::splitIntoBlocks(message, len, blockSize, blocksNumber);

    int vectorLen = blockSize;
    char loopVector[vectorLen + 1];
    char newVector[vectorLen + 1];
    strcpy(loopVector, initVector);

    for (int i = 0; i < blocksNumber; i++) {
        char *cypherBlock = OFBBlockEncryption(blocks[i], blockSize, key, loopVector, newVector);
        strcpy(loopVector, newVector);
        strcpy(cypherText + blockSize * (i + 1), cypherBlock);
        free(cypherBlock);
    }

    cypherText[len] = '\0';
    return cypherText;
}

char *Crypto::OFBDecryption(const char *cypherText, int len, const char *key) {
    int blockSize = BLOCK_SIZE;

    if (len % blockSize != 0) {
        printf("Message should be multiple of %d. Length is %d\n", blockSize, len);
        return nullptr;
    }
    int plainTextLen = len + 1 - blockSize;
    char* plainText = (char*) malloc(plainTextLen + 1);
    int blocksNumber;
    char** blocks = Util::splitIntoBlocks(cypherText, len, blockSize, blocksNumber);

    int vectorLen = blockSize;
    char newVector[vectorLen + 1];

    char loopVector[vectorLen + 1];
    strcpy(loopVector, blocks[0]);

    for (int i = 1; i < blocksNumber; i++) {
        char *cypherBlock = OFBBlockDecryption(blocks[i], blockSize, key, loopVector, newVector);
        strcpy(loopVector, newVector);
        strcpy(plainText + blockSize * (i - 1), cypherBlock);
        free(cypherBlock);
    }

    plainText[plainTextLen] = '\0';
    return plainText;
}

Crypto::Crypto() {
    if (RAND == nullptr) {
        char* randKey = KEY;
        char* randKeyPerm = applyPermutation(randKey, BLOCK_SIZE, PERMUTATION);
        char* rand = xorMessages(randKeyPerm, KEY, BLOCK_SIZE);

        RAND = rand;
        free(randKeyPerm);
    }

}

char *Crypto::decryptBlock(char *block, int len) {
    char* rand = xorMessages(block, KEY, len);
    char* randKeyPerm = applyPermutation(rand, len, PERMUTATION, true);

    free(rand);
    return randKeyPerm;
}





