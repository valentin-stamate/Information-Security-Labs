#ifndef HOMEWORK_01_KEYMANAGER_H
#define HOMEWORK_01_KEYMANAGER_H


#include "../client/Client.h"
#include "../security/Crypto.h"

class KeyManager: Client {
public:
    char keyP[Crypto::BLOCK_SIZE + 1] = "hfbsgrthjqlopfhg";
    char key[Crypto::BLOCK_SIZE + 1];
};


#endif //HOMEWORK_01_KEYMANAGER_H
