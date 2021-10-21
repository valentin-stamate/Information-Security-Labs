#include <cstdio>
#include <cstring>
#include "client/Client.h"
#include "node/node/Node.h"
#include "file/File.h"

char address[] = "127.0.0.1";

int main() {
    Crypto crypto;
    Node node;
    node.connectToServer(address, 8080);

    char KEY[17];
    int mode;

    /* receiving operation mode */
    node.receiveMessage(&mode);
    printf("Operation Mode: %s\n", mode == 0 ? "ECB" : "OFB");

    /* receiving key */
    node.receiveMessage(KEY);

    char* DEC_KEY = crypto.decryptBlock(KEY, 16);
    printf("Decrypted key: %s\n", DEC_KEY);

    /* receiving the start message */
    char startMessage[6];
    node.receiveMessage(startMessage);
    printf("Start message: %s\n", startMessage);

    /* receiving the file */
    char buffer[4097];
    int len = node.receiveMessage(buffer);

    char* decrypted;
    if (mode == 0) {
        decrypted = crypto.ECBDecryption(buffer, len, DEC_KEY);
    } else {
        decrypted = crypto.OFBDecryption(buffer, len, DEC_KEY);
    }

    File::writeFile("files/rec_file", buffer, len, true);
    File::writeFile("files/file_dec", decrypted, len, true);
    return 0;
}

