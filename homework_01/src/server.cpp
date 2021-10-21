#include <cstdio>
#include "server/Server.h"
#include "file/File.h"
#include "util/Util.h"

using namespace std;
int main() {
    Crypto crypto;
    Server s;

    string keyManager("KeyManager");
    string nodeB("Node");

    s.start(8080);
    s.startListening();

    char buffer[32];

    char message[32] = "ana are mere";
    char RAW_KEY[17];

    /* Key Manager */
    s.acceptClient();
    s.receiveMessageFrom(keyManager, RAW_KEY);

    char* DEC_KEY = crypto.decryptBlock(RAW_KEY, 16);
    printf("Decrypted key: %s\n", DEC_KEY);

    /* Node B */
    s.acceptClient();

    int mode;
    scanf("%d", &mode);

    printf("Operation Mode: %s\n", mode == 0 ? "ECB" : "OFB");
    /* sending operation mode */
    s.sendMessageTo(nodeB, &mode, sizeof(int));

    /* sending the key */
    s.sendMessageTo(nodeB, RAW_KEY, 17);

    /* sending the message for beginning communication */
    char startMessage[6] = "Start";
    s.sendMessageTo(nodeB, startMessage, 6);

    /* sending the file */
    char fileBuffer[4097];
    int len;
    File::readFile("files/raw_file", fileBuffer, len);

    int newLen;
    char* paddedBuffer = Util::getCopyAndRound(fileBuffer, len, crypto.BLOCK_SIZE, newLen);

    char* encryptedFileContent;
    /* ECB */
    if (mode == 0) {
        encryptedFileContent = crypto.ECBEncryption(paddedBuffer, newLen, DEC_KEY);
    } else {
        encryptedFileContent = crypto.OFBEncryption(paddedBuffer, newLen, DEC_KEY, crypto.IV);
    }

    s.sendMessageTo(nodeB, encryptedFileContent, newLen);


}
