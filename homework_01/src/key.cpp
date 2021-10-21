#include <cstdio>
#include <cstring>
#include "client/Client.h"
#include "node/key_manager/KeyManager.h"

char address[] = "127.0.0.1";

int main() {
    Crypto crypto;

    KeyManager keyManager;
    keyManager.connectToServer(address, 8080);

    char *secretKey = crypto.RAND;
    keyManager.sendMessage(secretKey, 17);

    return 0;
}

