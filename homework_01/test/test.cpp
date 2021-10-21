#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include "../src/util/Util.h"
#include "../src/security/Crypto.h"
#include "../src/file/File.h"

using namespace std;

void testString();
void testCrypto();
void testFile();

int main() {
    testCrypto();
//    testFile();
}

void testString() {
    char text[] = "ahfjshdjfrrrry";
    int newLen;
    char* newText = Util::getCopyAndRound(text, strlen(text), 2, newLen);

    printf("%s\n%d\n", newText, newLen);

    int n;
    char** buffer = Util::splitIntoBlocks(text, strlen(text), 7, n);

    for (int i = 0; i < n; i++) {
        printf("%s\n", buffer[i]);
    }

    Util::freeArray(buffer, n);
    free(newText);

    char *a = (char*) malloc(4);
    a[0] = a[1] = a[2] = a[3] = 0;
    a[2] = 1;
    int *v = (int*) a;

    printf("%d\n", *v);
}

void testCrypto() {
    Crypto crypt;
    char* key = Crypto::generateRandomKey(16);
    char plainText[] = "Ana are mere  si si inca ceva";
    int len;
    char *paddedPlainText = Util::getCopyAndRound(plainText, strlen(plainText), 16, len);

    char* encrypted = crypt.ECBEncryption(paddedPlainText, len, key);
    printf("ECB Enc: %-64s\n", encrypted);

    char* decrypted = crypt.ECBDecryption(encrypted, len, key);
    printf("ECB Dec: %-64s\n", decrypted);

    printf("\n");

    char* ofbEnc = crypt.OFBEncryption(paddedPlainText, len, key, crypt.IV);
    printf("OFB Enc: %-64s -> %ld\n", ofbEnc, strlen(ofbEnc));

    char* ofDec = crypt.OFBDecryption(ofbEnc, len, key);
    printf("OFB Dec: %-64s -> %ld\n", ofDec, strlen(ofDec));

//    free(key);
//    free(encrypted);
//    free(decrypted);
}

void testFile() {
//    File::readFile("file", [](const char *block, long len, int blockSize) {
//        printf("%s", block);
//    });
//
//    char text[] = "Ana are mere fiindca spaga cere";
//
//    File::writeFile("file_write", text, (int) strlen(text), true);
//
//    printf("\n");
}
